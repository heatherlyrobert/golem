/*============================----beg-of-source---============================*/
#include "golem.h"



/*--------- ----------- ----------- ----------- ------------------------------*/
typedef     struct      termios     tTERMIOS;
static      tTERMIOS    s_oldtio;
static      tTERMIOS    s_newtio;



/*====================------------------------------------====================*/
/*===----                         communication                        ----===*/
/*====================------------------------------------====================*/
static void      o___COMM____________________o (void) {;}

char
COMM_init               (void)
{
   /*---(locals)-------------------------*/
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_SIGN   yLOG_enter   (__FUNCTION__);
   my.port      = -1;
   rc = COMM_device (DEV_SPIDER);
   /*---(complete)-----------------------*/
   DEBUG_SIGN   yLOG_exit    (__FUNCTION__);
   return 0;
}

char       /* ---- : open a communication channel to the robot ---------------*/
COMM_device             (char *a_dev)
{
   /*---(locals)-------------------------*/
   char        rce         =  -10;
   char        rc          =    0;
   tSTAT       s;
   /*---(header)-------------------------*/
   DEBUG_SIGN   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_SIGN   yLOG_point   ("a_dev"     , a_dev);
   --rce;  if (a_dev == NULL) {
      DEBUG_SIGN   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_SIGN   yLOG_info    ("a_dev"     , a_dev);
   /*---(check on file)------------------*/
   rc = stat (a_dev, &s);
   DEBUG_SIGN   yLOG_value   ("stat"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_SIGN   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_SIGN   yLOG_note    ("file exists");
   /*---(check type)---------------------*/
   DEBUG_SIGN   yLOG_value   ("dir"       , S_ISDIR (s.st_mode));
   DEBUG_SIGN   yLOG_value   ("link"      , S_ISLNK (s.st_mode));
   DEBUG_SIGN   yLOG_value   ("reg"       , S_ISREG (s.st_mode));
   DEBUG_SIGN   yLOG_value   ("char"      , S_ISCHR (s.st_mode));
   DEBUG_SIGN   yLOG_value   ("block"     , S_ISBLK (s.st_mode));
   if (!S_ISCHR (s.st_mode)) {
      DEBUG_SIGN   yLOG_note    ("not a char device");
      DEBUG_SIGN   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_SIGN   yLOG_note    ("is a char device");
   /*---(save)---------------------------*/
   strlcpy (my.device, a_dev, LEN_RECD);
   /*---(complete)-----------------------*/
   DEBUG_SIGN   yLOG_exit    (__FUNCTION__);
   return 0;
}

char       /* ---- : open a communication channel to the robot ---------------*/
COMM_open               (void)
{
   /*---(notes)--------------------------*/
   /*
    *   O_RDRW    : both read and write
    *   O_NOCTTY  : don't be the controlling terminal for the port (no sigs)
    *   O_NODELAY : don't wait for the other end of the port to be ready
    *
    */
   /*---(locals)-------------------------*/
   char        rce         =  -10;
   int         fd          =    0;       /* file descriptor                          */
   /*---(header)-------------------------*/
   DEBUG_SIGN   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_SIGN   yLOG_info    ("device"    , my.device);
   /*---(open)---------------------------*/
   fd = open (my.device, O_RDWR | O_NOCTTY | O_NONBLOCK);
   DEBUG_SIGN   yLOG_value   ("fd"        , fd);
   --rce;  if (fd == -1) {
      fprintf(stderr, "can not open serial port %s\n", my.device);
      DEBUG_SIGN   yLOG_note    ("can not open serial port");
      DEBUG_SIGN   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   fcntl (fd, F_SETFL, 0);
   /*---(get current term settings)------*/
   tcgetattr(fd, &s_oldtio);
   /*---(prepare new one)----------------*/
   bzero(&s_newtio, sizeof (tTERMIOS));
   /*> s_newtio.c_cflag = B115200 | CS8 | CLOCAL | CREAD;                               <*/
   s_newtio.c_cflag = B2400 | CS8 | CLOCAL | CREAD;
   cfsetispeed(&s_newtio, B115200);
   /*> cfsetispeed(&s_newtio, B2400);                                                   <*/
   cfsetospeed(&s_newtio, B115200);
   /*> cfsetospeed(&s_newtio, B2400);                                                   <*/
   /*> s_newtio.c_cflag |= (CLOCAL | CREAD);                                            <* 
    *> s_newtio.c_cflag &= ~CSIZE;                                                      <* 
    *> s_newtio.c_cflag &= ~PARENB;                                                     <* 
    *> s_newtio.c_cflag &= ~CSTOPB;                                                     <* 
    *> s_newtio.c_cflag |= CS8;                                                         <*/
   s_newtio.c_iflag  = IGNPAR  | ICRNL   ;
   s_newtio.c_oflag  = 0       ;
   s_newtio.c_lflag  = ICANON  ;
   tcflush   (fd, TCIFLUSH);
   tcsetattr (fd, TCSANOW, &s_newtio);
   /*---(save)---------------------------*/
   my.port = fd;
   DEBUG_SIGN   yLOG_value   ("port"      , my.port);
   /*---(complete)-----------------------*/
   DEBUG_SIGN   yLOG_exit    (__FUNCTION__);
   return 0;
}

char       /* ---- : close the communcation channel to the robot -------------*/
COMM_close              (void)
{
   /*---(locals)-------------------------*/
   char        rce         =  -10;
   int         rc          =    0;       /* generic return code    */
   /*---(header)-------------------------*/
   DEBUG_SIGN   yLOG_enter   (__FUNCTION__);
   /*---(defenses)-----------------------*/
   --rce;  if (my.port < 0) {
      DEBUG_SIGN   yLOG_note    ("serial port is not open");
      DEBUG_SIGN   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(close)--------------------------*/
   rc = close (my.port);
   DEBUG_SIGN   yLOG_value   ("close"     , rc);
   if (rc <  0) {
      DEBUG_SIGN   yLOG_note    ("could not close the serial port");
      DEBUG_SIGN   yLOG_exitr   (__FUNCTION__, rce);
      return 0;
   }
   DEBUG_SIGN   yLOG_note    ("serial port successfully closed");
   /*---(set terminal back)--------------*/
   tcsetattr (my.port, TCSANOW, &s_oldtio);
   /*---(complete)-----------------------*/
   DEBUG_SIGN   yLOG_exit    (__FUNCTION__);
   return 0;
}

char       /* ---- : transfer control statements to the robot ----------------*/
COMM_write              (char *a_text)
{
   /*---(locals)-------------------------*/
   int       rc        = 0;       /* generic return code                      */
   /*---(write)--------------------------*/
   write(my.port, a_text, strlen(a_text));
   if (rc < 0) {
      fprintf(stderr, "could not write data to %d\n", my.port);
   } else if (rc == 0) {
      fprintf(stderr, "no data was written to %d\n", my.port);
   } else {
      fprintf(stderr, "wrote %d chars <<%s>>\n", rc, a_text);
   }
   /*---(complete)-----------------------*/
   return 0;
}



/*============================----end-of-source---============================*/
