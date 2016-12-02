/*============================----beg-of-source---============================*/

#include "golem.h"



typedef struct termios TERMIOS;
TERMIOS   oldtio;
TERMIOS   newtio;



/*====================------------------------------------====================*/
/*===----                         communication                        ----===*/
/*====================------------------------------------====================*/
static void      o___COMM____________________o (void) {;}

int        /* ---- : open a communication channel to the robot ---------------*/
COMM_open          (char *a_dev)
{
   /*---(notes)--------------------------*/
   /*
    *   O_RDRW    : both read and write
    *   O_NOCTTY  : don't be the controlling terminal for the port (no sigs)
    *   O_NODELAY : don't wait for the other end of the port to be ready
    *
    */
   /*---(locals)-------------------------*/
   int       fd        = 0;       /* file descriptor                          */
   /*---(open)---------------------------*/
   fd = open(a_dev, O_RDWR | O_NOCTTY | O_NONBLOCK);
   if (fd == -1) {
      fprintf(stderr, "can not open serial port %s\n", a_dev);
   } else {
      fprintf(stderr, "port %s is successfully open at %d\n", a_dev, fd);
      fcntl (fd, F_SETFL, 0);
   }
   /*---(get current term settings)------*/
   tcgetattr(fd, &oldtio);
   /*---(prepare new one)----------------*/
   bzero(&newtio, sizeof(TERMIOS));
   /*> newtio.c_cflag = B115200 | CS8 | CLOCAL | CREAD;                               <*/
   newtio.c_cflag = B2400 | CS8 | CLOCAL | CREAD;
   cfsetispeed(&newtio, B115200);
   /*> cfsetispeed(&newtio, B2400);                                                   <*/
   cfsetospeed(&newtio, B115200);
   /*> cfsetospeed(&newtio, B2400);                                                   <*/
   /*> newtio.c_cflag |= (CLOCAL | CREAD);                                            <* 
    *> newtio.c_cflag &= ~CSIZE;                                                      <* 
    *> newtio.c_cflag &= ~PARENB;                                                     <* 
    *> newtio.c_cflag &= ~CSTOPB;                                                     <* 
    *> newtio.c_cflag |= CS8;                                                         <*/
   newtio.c_iflag  = IGNPAR  | ICRNL   ;
   newtio.c_oflag  = 0       ;
   newtio.c_lflag  = ICANON  ;
   tcflush   (fd, TCIFLUSH);
   tcsetattr (fd, TCSANOW, &newtio);
   /*---(complete)-----------------------*/
   return fd;
}

char       /* ---- : close the communcation channel to the robot -------------*/
COMM_close         (int a_port)
{
   /*---(defenses)-----------------------*/
   if (a_port < 0) return -1;
   /*---(locals)-------------------------*/
   int       rc        = 0;       /* generic return code    */
   /*---(close)--------------------------*/
   rc = close(a_port);
   if (rc == 0) {
      fprintf(stderr, "port is successfully closed\n");
   } else {
      fprintf(stderr, "could not close serial port\n");
   }
   /*---(set terminal back)--------------*/
   tcsetattr(a_port, TCSANOW, &oldtio);
   /*---(complete)-----------------------*/
   return 0;
}

char       /* ---- : transfer control statements to the robot ----------------*/
golem_write        (int a_port, char *a_text)
{
   /*---(locals)-------------------------*/
   int       rc        = 0;       /* generic return code                      */
   /*---(write)--------------------------*/
   write(a_port, a_text, strlen(a_text));
   if (rc < 0) {
      fprintf(stderr, "could not write data to %d\n", a_port);
   } else if (rc == 0) {
      fprintf(stderr, "no data was written to %d\n", a_port);
   } else {
      fprintf(stderr, "wrote %d chars <<%s>>\n", rc, a_text);
   }
   /*---(complete)-----------------------*/
   return 0;
}



/*============================----end-of-source---============================*/
