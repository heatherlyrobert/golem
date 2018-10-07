/*============================----beg-of-source---============================*/
#include "golem.h"



/*> char      debug     = '-';                                                        <* 
 *> #define   DEBUG_O   if (debug == 'y')                                             <* 
 *> char      debug     = '-';                                                        <*/


#define   DEG2PTS    10
#define   SEC2MSEC   1000.0


/*====================------------------------------------====================*/
/*===----                         initial setup                        ----===*/
/*====================------------------------------------====================*/
static void      o___SETUP___________________o (void) {;}






#define    RR     0
#define    RM     1
#define    RF     2
#define    LR     3
#define    LM     4
#define    LF     5

/*> char       leg_name[6][15] = {                                                    <* 
 *>    "right-rear",                                                                  <* 
 *>    "right-middle",                                                                <* 
 *>    "right-front",                                                                 <* 
 *>    "left-rear",                                                                   <* 
 *>    "left-middle",                                                                 <* 
 *>    "left-front"                                                                   <* 
 *> };                                                                                <*/

char
hex_move           (int a_port, int a_leg, int a_femur, int a_patella, int a_tibia, int a_msec)
{
   /*---(locals)-------------------------*/
   char      buf[1000]   = "";
   /*---(defenses)-----------------------*/
   if (a_leg < RR || a_leg > LF) {
      fprintf(stderr, "leg number %d is not known (0-5) : MUST IGNORE\n", a_leg);
      return -1;
   }
   if (a_leg >  RF) a_leg += 1;
   /*---(gross corrections)--------------*/
   if (a_femur   <  650 || a_femur   > 2350) {
      fprintf(stderr, "leg %d femur position %d is not allowed (650-2350) : ", a_leg, a_femur);
      if (a_femur <  650) a_femur =  650;
      if (a_femur > 2350) a_femur = 2350;
      fprintf(stderr, "CORRECTED to %d\n", a_femur);
   }
   if (a_patella < 1050 || a_patella > 2400) {
      fprintf(stderr, "leg %d patella position %d is not allowed (1050-2400) : ", a_leg, a_patella);
      if (a_patella < 1050) a_patella = 1050;
      if (a_patella > 2400) a_patella = 2400;
      fprintf(stderr, "CORRECTED to %d\n", a_patella);
   }
   if (a_tibia   <  750 || a_tibia > 1900) {
      fprintf(stderr, "leg %d tibia position %d is not allowed ( 750-1900) : ", a_leg, a_tibia);
      if (a_tibia <  750) a_tibia =  750;
      if (a_tibia > 1900) a_tibia = 1900;
      fprintf(stderr, "CORRECTED to %d\n", a_tibia);
   }
   /*---(update for sides)---------------*/
   if (a_leg > RF) {
      a_femur   = 1500 - (a_femur   - 1500);
      a_patella = 1500 - (a_patella - 1500);
      a_tibia   = 1500 - (a_tibia   - 1500);
   }
   /*---(send command)-------------------*/
   snprintf(buf, 1000, "#%d p%d #%d p%d #%d  p%d  T%d\r", (a_leg * 4), a_femur, (a_leg * 4) + 1, a_patella, (a_leg * 4) + 2, a_tibia, a_msec);
   printf ("%s\n", buf);
   write  (a_port, buf, strlen(buf));
   /*---(complete)-----------------------*/
   return 0;
}

char
hex_ra             (int a_port, int a_femur, int a_patella, int a_tibia, int a_msec)
{
   hex_move (a_port, 0, a_femur, a_tibia, a_patella, a_msec);
   hex_move (a_port, 1, a_femur, a_tibia, a_patella, a_msec);
   hex_move (a_port, 2, a_femur, a_tibia, a_patella, a_msec);
   return 0;
}

char
hex_la             (int a_port, int a_femur, int a_patella, int a_tibia, int a_msec)
{
   hex_move (a_port, 3, a_femur, a_tibia, a_patella, a_msec);
   hex_move (a_port, 4, a_femur, a_tibia, a_patella, a_msec);
   hex_move (a_port, 5, a_femur, a_tibia, a_patella, a_msec);
   return 0;
}

char
hex_aa             (int a_port, int a_femur, int a_patella, int a_tibia, int a_msec)
{
   hex_ra (a_port, a_femur, a_tibia, a_patella, a_msec);
   hex_la (a_port, a_femur, a_tibia, a_patella, a_msec);
   return 0;
}

char
hex_align_OLD      (int a_port)
{
   /*---(rr)-----------------------------*/
   write(a_port, "#0  PO0   \r", 12);
   /*> write(a_port, "#1  PO60  \r", 12);                                             <*/
   write(a_port, "#1  PO40  \r", 12);
   write(a_port, "#2  PO0   \r", 12);
   /*---(rm)-----------------------------*/
   write(a_port, "#4  PO0   \r", 12);
   write(a_port, "#5  PO0   \r", 12);
   write(a_port, "#6  PO0   \r", 12);
   /*---(rf)-----------------------------*/
   write(a_port, "#8  PO15  \r", 12);
   write(a_port, "#9  PO25  \r", 12);
   write(a_port, "#10 PO-30 \r", 12);
   /*---(lr)-----------------------------*/
   write(a_port, "#16 PO0   \r", 12);
   /*> write(a_port, "#17 PO0   \r", 12);                                             <*/
   write(a_port, "#17 PO15  \r", 12);
   /*> write(a_port, "#18 PO0   \r", 12);                                             <*/
   write(a_port, "#18 PO70  \r", 12);
   /*---(lm)-----------------------------*/
   write(a_port, "#20 PO0   \r", 12);
   /*> write(a_port, "#21 PO30  \r", 12);                                             <*/
   write(a_port, "#21 PO60  \r", 12);
   /*> write(a_port, "#22 PO15  \r", 12);                                             <*/
   write(a_port, "#22 PO80  \r", 12);
   /*---(lf)-----------------------------*/
   write(a_port, "#24 PO0   \r", 12);
   write(a_port, "#25 PO-35 \r", 12);
   write(a_port, "#26 PO15  \r", 12);
   return 0;
}

char
hex_align_table    (int a_port)
{
   /*---(locals)-------------------------*/
   int       i         = 0;       /* loop iterator                            */
   char      buf[1000]   = "";
   for (i = 0; i < YKINE_MAX_SERVO; ++i) {
      if (g_servo_data [i].leg <  0) continue;
      sprintf (buf, "#%-2d PO0\r", i);
      write(a_port, buf, strlen (buf));
   }
   return 0;
}

char
hex_align          (int a_port)
{
   /*---(rr)-----------------------------*/
   write(a_port, "#0  PO0   \r", 12);
   /*> write(a_port, "#1  PO60  \r", 12);                                             <*/
   write(a_port, "#1  PO0  \r", 12);
   write(a_port, "#2  PO0   \r", 12);
   /*---(rm)-----------------------------*/
   write(a_port, "#4  PO0   \r", 12);
   write(a_port, "#5  PO40    \r", 12);
   write(a_port, "#6  PO-140  \r", 12);
   /*---(rf)-----------------------------*/
   write(a_port, "#8  PO0  \r", 12);
   write(a_port, "#9  PO0  \r", 12);
   write(a_port, "#10 PO0 \r", 12);
   /*---(lr)-----------------------------*/
   write(a_port, "#16 PO0   \r", 12);
   /*> write(a_port, "#17 PO0   \r", 12);                                             <*/
   write(a_port, "#17 PO0  \r", 12);
   /*> write(a_port, "#18 PO0   \r", 12);                                             <*/
   write(a_port, "#18 PO0  \r", 12);
   /*---(lm)-----------------------------*/
   write(a_port, "#20 PO0   \r", 12);
   /*> write(a_port, "#21 PO30  \r", 12);                                             <*/
   write(a_port, "#21 PO0  \r", 12);
   /*> write(a_port, "#22 PO15  \r", 12);                                             <*/
   write(a_port, "#22 PO0  \r", 12);
   /*---(lf)-----------------------------*/
   write(a_port, "#24 PO0   \r", 12);
   write(a_port, "#25 PO200 \r", 12);
   write(a_port, "#26 PO0  \r", 12);
   return 0;
}

/*> char                                                                               <* 
 *> test_attention     (void)                                                          <* 
 *> {                                                                                  <* 
 *>    int       i         = 0;       /+ loop iterator                            +/   <* 
 *>    for (i = 0; i < 100; ++i) {                                                     <* 
 *>       hex_aa (my.port, 1500, 1500, 1500,  500);                                     <* 
 *>    }                                                                               <* 
 *>    return 0;                                                                       <* 
 *> }                                                                                  <*/

char
test_repeater      (void)
{
   int       i         = 0;       /* loop iterator                            */
   for (i = 0; i < 100; ++i) {
      hex_aa (my.port, 1000, 1500, 1000,  500);
      usleep( 500000);
      hex_aa (my.port, 1500, 1300, 1500,  500);
      usleep( 500000);
      hex_aa (my.port, 2000, 1500, 1000,  500);
      usleep( 500000);
      hex_aa (my.port, 1500, 1700, 1500,  500);
      usleep( 500000);
      hex_aa (my.port, 1500, 2400, 1800,  500);
      usleep( 500000);
      hex_aa (my.port, 1500, 2400,  800,  500);
      usleep( 500000);
      hex_move (my.port, LR, 1200, 2400,  800,  500);
      hex_move (my.port, LM,  700, 2400,  800,  500);
      hex_move (my.port, LF,   700, 1200, 1600,  500);
      hex_move (my.port, RR,  1200, 2400,  800,  500);
      hex_move (my.port, RM,  700, 2400,  800,  500);
      hex_move (my.port, RF,   700, 1200, 1600,  500);
      /*> exit(0);                                                                    <*/
      usleep( 500000);
      hex_move (my.port, RM, 1500, 1500,  800,  500);
      hex_move (my.port, LM, 1500, 1500,  800,  500);
      usleep( 500000);
      hex_move (my.port, RM, 1200, 1500,  800,  250);
      hex_move (my.port, LM, 1200, 1500,  800,  250);
      usleep( 250000);
      hex_move (my.port, RM, 1800, 1500,  800,  500);
      hex_move (my.port, LM, 1800, 1500,  800,  500);
      usleep( 500000);
      hex_move (my.port, RM, 1200, 1500,  800,  500);
      hex_move (my.port, LM, 1200, 1500,  800,  500);
      usleep( 500000);
      hex_move (my.port, RM, 1500, 1500,  800,  250);
      hex_move (my.port, LM, 1500, 1500,  800,  250);
      usleep( 250000);
   }
   return 0;
}

char
test_original      (void)
{
   int       i         = 0;       /* loop iterator                            */
   hex_aa (my.port, 1000, 1500, 1000,  500);
   usleep( 500000);
   hex_aa (my.port, 1500, 1300, 1500,  500);
   usleep( 500000);
   hex_aa (my.port, 2000, 1500, 1000,  500);
   usleep( 500000);
   hex_aa (my.port, 1500, 1700, 1500,  500);
   usleep( 500000);
   hex_aa (my.port, 1500, 2400, 1800,  500);
   usleep( 500000);
   hex_aa (my.port, 1500, 2400,  800,  500);
   usleep( 500000);
   hex_move (my.port, LR, 1200, 2400,  800,  500);
   hex_move (my.port, LM,  700, 2400,  800,  500);
   hex_move (my.port, LF,   700, 1200, 1600,  500);
   hex_move (my.port, RR,  1200, 2400,  800,  500);
   hex_move (my.port, RM,  700, 2400,  800,  500);
   hex_move (my.port, RF,   700, 1200, 1600,  500);
   usleep( 500000);
   hex_move (my.port, RM, 1500, 1500,  800,  500);
   hex_move (my.port, LM, 1500, 1500,  800,  500);
   usleep( 500000);
   hex_move (my.port, RM, 1200, 1500,  800,  250);
   hex_move (my.port, LM, 1200, 1500,  800,  250);
   usleep( 250000);
   for (i = 0; i < 5; ++i) {
      hex_move (my.port, RM, 1800, 1500,  800,  500);
      hex_move (my.port, LM, 1800, 1500,  800,  500);
      usleep( 500000);
      hex_move (my.port, RM, 1200, 1500,  800,  500);
      hex_move (my.port, LM, 1200, 1500,  800,  500);
      usleep( 500000);
   }
   hex_move (my.port, RM, 1500, 1500,  800,  250);
   hex_move (my.port, LM, 1500, 1500,  800,  250);
   usleep( 250000);
   return 0;
}

char
test_trig          (void)
{
   int       i         = 0;       /* loop iterator                            */
   int       hip       = 0;
   hex_aa (my.port, 1500, 1500, 1500,  500);
   usleep( 500000);
   hex_move (my.port, RM, 2100, 1500,  800,  250);
   hex_move (my.port, LM, 2100, 1500,  800,  250);
   usleep( 500000);
   i = 0;
   while (1) {
      i += 30;
      hip = 1500 + cos((double) (i) / 360.0 * 3.14159) * 700;
      printf("%3d so hip at %4d\n", i, hip);
      /*> hex_move (my.port, RM, hip , 1500,  800,   35);                              <*/
      hex_move (my.port, LM, hip , 1500,  800,   80);
      usleep(  80000);
   }
   return 0;
}

char
manta_ray          (void)
{
   /* femu    650  to   2350       */
   /* pate   1050  to   2400       */
   /* tibi    750  to   1900       */
   /*-------------- leg  femu  pate  tibi  time ---*/
   hex_move (my.port, LR, 1200, 1500,  750,  500);
   hex_move (my.port, RR, 1200, 1500,  750,  500);
   hex_move (my.port, LM,  700, 1500,  750,  500);
   hex_move (my.port, RM,  700, 1500,  750,  500);
   hex_move (my.port, LF,  650, 1500,  750,  500);
   hex_move (my.port, RF,  650, 1500,  750,  500);
   return 0;
}

char
bulldog_OLD        (int a_time)
{
   /* femu    650  to   2350       */
   /* pate   1050  to   2400       */
   /* tibi    750  to   1900       */
   /*-------------- leg  femu  pate  tibi  time ---*/
   hex_move (my.port, LR, 2000, 1050,  750,  a_time);
   hex_move (my.port, RR, 2000, 1050,  750,  a_time);
   hex_move (my.port, LM, 1500, 1050,  750,  a_time);
   hex_move (my.port, RM, 1500, 1050,  750,  a_time);
   hex_move (my.port, LF, 1000, 1050,  750,  a_time);
   hex_move (my.port, RF, 1000, 1050,  750,  a_time);
   return 0;
}

char
bulldog_low_OLD    (int a_time)
{
   /* femu    650  to   2350       */
   /* pate   1050  to   2400       */
   /* tibi    750  to   1900       */
   /*-------------- leg  femu  pate  tibi  time ---*/
   hex_move (my.port, LR, 2000, 2100, 1900,  a_time);
   hex_move (my.port, RR, 2000, 2100, 1900,  a_time);
   hex_move (my.port, LM, 1500, 2100, 1900,  a_time);
   hex_move (my.port, RM, 1500, 2100, 1900,  a_time);
   hex_move (my.port, LF, 1000, 2100, 1900,  a_time);
   hex_move (my.port, RF, 1000, 2100, 1900,  a_time);
   return 0;
}

char
test_all_joints    (void)
{
   int       i = 0;
   hex_aa   (my.port, 1500, 1500, 1500,  500);
   /*---(move femur)------------------*/
   hex_aa   (my.port,  900, 1500, 1500,  500);
   usleep( 500000);
   hex_aa   (my.port, 2100, 1500, 1500,  500);
   usleep( 500000);
   /*---(move patella)----------------*/
   hex_aa   (my.port, 1500, 1050, 1500,  500);
   usleep( 500000);
   hex_aa   (my.port, 1500, 2300, 1500,  500);
   usleep( 500000);
   /*---(move tibia)------------------*/
   hex_aa   (my.port, 1500, 1500,  750,  500);
   usleep( 500000);
   hex_aa   (my.port, 1500, 1500, 1900,  500);
   usleep( 500000);
   hex_aa   (my.port, 1500, 1500,  750,  500);
   usleep( 500000);
   /*---(move patella)----------------*/
   hex_aa   (my.port, 1500, 2300, 1500,  500);
   usleep( 500000);
   hex_aa   (my.port, 1500, 1050, 1500,  500);
   usleep( 500000);
   /*---(move femur)------------------*/
   hex_aa   (my.port, 2100, 1500, 1500,  500);
   usleep( 500000);
   hex_aa   (my.port,  900, 1500, 1500,  500);
   usleep( 500000);
   /*---(done)--------------*/
   hex_aa   (my.port, 1500, 1500, 1500,  500);
   return 0;
}

char
test_joints        (void)
{
   int       i = 0;
   hex_aa( my.port, 1500, 1500, 1500, 500);
   for (i = 0; i < 6; ++i) {
      /*---(move femur)------------------*/
      hex_move (my.port, i,  650, 1500, 1500,  500);
      usleep( 500000);
      hex_move (my.port, i, 2350, 1500, 1500,  500);
      usleep( 500000);
      /*---(move patella)----------------*/
      hex_move (my.port, i, 1500, 1050, 1500,  500);
      usleep( 500000);
      hex_move (my.port, i, 1500, 2300, 1500,  500);
      usleep( 500000);
      /*---(move tibia)------------------*/
      hex_move (my.port, i, 1500, 1500,  750,  500);
      usleep( 500000);
      hex_move (my.port, i, 1500, 1500, 1900,  500);
      usleep( 500000);
   }
   return 0;
}

char
test_doreme        (void)
{
   hex_move (my.port, 2,  650, 1500, 1500,  500);
   usleep( 500000);
   hex_move (my.port, 2,  650, 2200, 1500,  500);
   usleep( 500000);
   hex_move (my.port, 2, 1600, 2200, 1500,  500);
   usleep( 500000);
   hex_move (my.port, 2, 1450, 1740, 1500,  300);
   usleep( 300000);
   hex_move (my.port, 2, 1600, 2200, 1500,  300);
   usleep( 300000);
   hex_move (my.port, 2, 1600, 1735, 1500,  300);
   usleep( 300000);
   hex_move (my.port, 2, 1600, 2200, 1500,  300);
   usleep( 300000);
   hex_move (my.port, 2, 1730, 1740, 1500,  300);
   usleep( 300000);
   hex_move (my.port, 2, 1600, 2200, 1500,  300);
   usleep( 300000);
   hex_move (my.port, 2, 1730, 1740, 1500,  300);
   usleep( 300000);
   hex_move (my.port, 2, 1600, 2200, 1500,  300);
   usleep( 300000);
   return 0;
}

char
test_box           (void)
{
   hex_move (my.port, 2,  650, 1500, 1500,  500);
   usleep( 500000);
   hex_move (my.port, 2,  650, 2200, 1500,  500);
   usleep( 500000);
   hex_move (my.port, 2, 1600, 2200, 1500,  500);
   usleep( 500000);
   hex_move (my.port, 2, 1450, 1740, 1500,  300);
   usleep( 300000);
   hex_move (my.port, 2, 1600, 2200, 1500,  300);
   usleep( 300000);
   hex_move (my.port, 2, 1600, 1735, 1500,  300);
   usleep( 300000);
   hex_move (my.port, 2, 1600, 2200, 1500,  300);
   usleep( 300000);
   hex_move (my.port, 2, 1730, 1740, 1500,  300);
   usleep( 300000);
   hex_move (my.port, 2, 1600, 2200, 1500,  300);
   usleep( 300000);
   hex_move (my.port, 2, 1730, 1740, 1500,  300);
   usleep( 300000);
   hex_move (my.port, 2, 1600, 2200, 1500,  300);
   usleep( 300000);
   return 0;
}

char     /* ---- : read scripting commands from stdin and interpret ----------*/
scripter           (void)
{
   /*---(local variables)------------------*/
   char      x_line[500] = "";
   int       lines     = 0;
   char     *p;
   int       leg       = 0;
   double    femu      = 0.0;
   double    pate      = 0.0;
   double    tibi      = 0.0;
   double    pace      = 0.0;
   int       test      = 0;
   char      xleg      = 0;
   /*---(set stdin to non-blocking)--------*/
   int flags = fcntl(0, F_GETFL, 0);
   fcntl(0, F_SETFL, flags | O_NONBLOCK);
   /*---(test stdin for input)-------------*/
   printf("testing for script input...");
   char  x_ch = getc(stdin);
   if (x_ch == -1) {
      printf(" no input presently available\n");
      return -1;
   }
   printf(" found input, now read line\n");
   ungetc(x_ch, stdin);
   fcntl(0, F_SETFL, flags);
   /*---(continue with input)--------------*/
   while (1) {
      fgets(x_line, 500, stdin);
      if (feof(stdin)) {
         printf("   eof character, assumed end of stdin\n");
         break;
      }
      x_line[strlen(x_line) - 1] = '\0';
      if (x_line[0] == '\0') continue;
      if (x_line[0] == '#' ) continue;
      ++lines;
      /*> if (strlen(x_line) <= 60) printf("   read <<%s>>\n",       x_line);         <* 
       *> else                      printf("   read <<%.60s...>>\n", x_line);         <*/
      p = strtok (x_line, " ");
      if (p == NULL) continue;
      if (strcmp (p, "STEP") == 0) {
         usleep(  35000);
         printf ("\n\n");
         continue;
      }
      leg  = atoi (p);
      p = strtok (NULL  , " ");
      if (p == NULL) continue;
      /*> printf ("p = <<%s>>", p);                                                   <*/
      femu = atof (p);
      /*> printf (", so %8.3f, and %d, and int %d\n", femu, (int) femu, test);        <*/
      if (leg >= 3) femu = -femu;
      p = strtok (NULL  , " ");
      if (p == NULL) continue;
      pate = atof (p);
      p = strtok (NULL  , " ");
      if (p == NULL) continue;
      tibi = atof (p);
      p = strtok (NULL  , " ");
      if (p == NULL) continue;
      pace = atof (p);
      printf ("%1d, %5.1f, %5.1f, %5.1f, %5.1f\n", leg, femu, pate, tibi, pace);
      printf (  "   %5.0d, %5.0d, %5.0d, %5.0d\n", (int) (femu * DEG2PTS) + 1500, (int) (pate * DEG2PTS) + 1500, 600 - (int) (tibi * DEG2PTS), (int) (pace * SEC2MSEC));
      xleg = leg;
      /*> switch (leg) {                                                              <* 
       *> case 3: xleg = 5;  break;                                                   <* 
       *> case 5: xleg = 3;  break;                                                   <* 
       *> }                                                                           <*/
      /*> hex_move (my.port, xleg, (int) (femu * DEG2PTS) + 1500, (int) (pate * DEG2PTS) + 1500, 600 - (int) (tibi * DEG2PTS), (int) (pace * SEC2MSEC));   <*/
      hex_move (my.port, xleg, (int) (femu * DEG2PTS) + 1500, (int) (pate * DEG2PTS) + 1500, 600 - (int) (tibi * DEG2PTS),  50);
      /*> hex_move (my.port, leg, (femu * DEG2PTS) + 1500, (pate * DEG2PTS) + 1500, 600 - (tibi * DEG2PTS), pace * SEC2MSEC);   <*/
      /*> printf ("\n");                                                              <*/
   }
   printf("   done\n");
   /*---(complete)-------------------------*/
   return 0;
}

char
pos_joint          (int a_port, int a_joint, int a_angle)
{
   /*---(locals)-------------------------*/
   char      buf[1000]   = "";
   int       x_angle     =  0;
   int       x_flip      =  0;
   int       x_new       =  0;
   int       i           =  0;
   int       x_zero      =  0;
   int       x_adjust    =  0;
   /*---(title)--------------------------*/
   if (a_joint == -1) printf ("---leg-------------  ---part--------  --  --  -req  -min  -max  -ang  flip  -adj  -fin\n");
   if (a_joint <  0        )      return -1;
   if (a_joint >= YKINE_MAX_SERVO)      return -2;
   if (g_servo_data[a_joint].leg == -1)  return -3;
   /*---(filter and limit)---------------*/
   i        = a_joint;
   x_angle  = a_angle;
   if (x_angle  < g_servo_data [i].min)  x_angle = g_servo_data [i].min;
   if (x_angle  > g_servo_data [i].max)  x_angle = g_servo_data [i].max;
   x_adjust = DATA_adjust (a_joint, a_angle);
   x_flip  = (1500 + (x_angle - 1500) * g_servo_data [i].flip);
   x_new   = x_flip + x_adjust;
   /*---(send command)-------------------*/
   snprintf (buf, 1000, "#%d P%d\r"    , g_servo_data [a_joint].servo, x_new);
   write    (a_port, buf, strlen(buf));
   /*---(display debugging)--------------*/
   printf   ("#%d  %-15.15s  %-15.15s  %2d  %2d  ",
         g_servo_data [a_joint].leg     , g_servo_data [a_joint].leg_name,
         g_servo_data [a_joint].seg_name, a_joint                   ,
         g_servo_data [a_joint].servo   );
   printf   ("%4d  %4d  %4d  %4d  %4d  %4d  %4d\n",
         a_angle                   ,
         g_servo_data [a_joint].min     , g_servo_data [a_joint].max     ,
         x_angle                   , x_flip                    ,
         x_adjust                  , x_new);

   /*---(complete)-----------------------*/
   return 0;
}

char
move_joint         (int a_port, int a_joint, int a_angle, int a_msec)
{
   /*---(locals)-------------------------*/
   char      buf[1000]   = "";
   int       x_adjust    =  0;
   int       x_angle     =  0;
   int       x_flip      =  0;
   int       x_new       =  0;
   int       i           =  0;
   /*---(filter and limit)---------------*/
   i        = a_joint;
   x_angle  = a_angle;
   printf ("move_joint, joint = %1d, angle = %4d, msec = %4d\n", i, x_angle, a_msec);
   if (x_angle  < g_servo_data [i].min) {
      x_angle = g_servo_data [i].min;
      printf ("angle too small, adjusted to %4d\n", x_angle);
   }
   if (x_angle  > g_servo_data [i].max) {
      x_angle = g_servo_data [i].max;
      printf ("angle too large, adjusted to %4d\n", x_angle);
   }
   x_adjust = DATA_adjust (i, x_angle);
   printf ("ADJUSTING %d\n", x_adjust);
   x_flip  = (1500 + (x_angle - 1500) * g_servo_data [i].flip);
   /*> x_flip  = x_angle;                                                             <*/
   x_new   = x_flip + x_adjust;
   /*---(send command)-------------------*/
   snprintf (buf, 1000, "#%d P%d T%d\r", g_servo_data [i].servo, x_new, a_msec);
   printf ("%s\n\n", buf);
   write  (a_port, buf, strlen(buf));
   /*> usleep (a_msec * 1000);                                                        <*/
   /*---(complete)-----------------------*/
   return 0;
}

int
main_new           (int argc, char *argv[])
{
   int       rc        = 0;       /* generic return code                      */
   rc = COMM_open ();
   move_joint  (my.port, 0, 1500, 2000);
   move_joint  (my.port, 1, 1900, 2000);
   move_joint  (my.port, 2, 1560, 2000);
   move_joint  (my.port, 3, 1000, 2000);
   move_joint  (my.port, 4, 1570, 2000);
   move_joint  (my.port, 5, 1100, 2000);

   /*> move_joint  (my.port,  0, 1900, 2000);                                          <* 
    *> move_joint  (my.port,  1, 1900, 2000);                                          <* 
    *> move_joint  (my.port,  2, 1900, 2000);                                          <*/
   /*---(move base)----------------------*/
   /*> move_joint  (my.port, 0,  600, 1000);                                           <* 
    *> move_joint  (my.port, 0, 2400, 2000);                                           <* 
    *> move_joint  (my.port, 0, 1500, 1000);                                           <*/
   /*> move_joint  (my.port, 0, 1000,  500);                                           <* 
    *> move_joint  (my.port, 0, 1500,  500);                                           <* 
    *> move_joint  (my.port, 0, 1000,  500);                                           <* 
    *> move_joint  (my.port, 0, 1500,  500);                                           <* 
    *> move_joint  (my.port, 0, 2000,  500);                                           <* 
    *> move_joint  (my.port, 0, 1500,  500);                                           <* 
    *> move_joint  (my.port, 1, 1500,  500);                                           <* 
    *> move_joint  (my.port, 1, 1800,  500);                                           <* 
    *> move_joint  (my.port, 1, 1500,  500);                                           <* 
    *> move_joint  (my.port, 1, 1200,  500);                                           <* 
    *> move_joint  (my.port, 1, 1500,  500);                                           <*/
   COMM_close ();
}

char
pose_attn          (void)
{
   int       i         = 0;       /* loop iterator                            */
   for (i = -1; i < YKINE_MAX_SERVO; ++i) {
      pos_joint   (my.port, i, 1500);
   }
   return 0;
}

char
pose_leg           (int a_servo, int a_femu, int a_pate, int a_tibi)
{
   int       i         = 0;       /* loop iterator                            */
   for (i = a_servo; i <= a_servo + 2; ++i) {
      switch (i % 4) {
      case 0 : pos_joint   (my.port, i, a_femu);
               break;
      case 1 : pos_joint   (my.port, i, a_pate);
               break;
      case 2 : pos_joint   (my.port, i, a_tibi);
               break;
      case 3 : break;
      }
   }
   return 0;
}

char
pose_fixed         (int a_femu, int a_pate, int a_tibi)
{
   int       i         = 0;       /* loop iterator                            */
   pos_joint (my.port, -1, 0);
   for (i = -1; i < YKINE_MAX_SERVO; ++i) {
      switch (i % 4) {
      case 0 : pos_joint   (my.port, i, a_femu);
               break;
      case 1 : pos_joint   (my.port, i, a_pate);
               break;
      case 2 : pos_joint   (my.port, i, a_tibi);
               break;
      case 3 : break;
      }
   }
   return 0;
}

char
pose_fmax          (void)
{
   int       i         = 0;       /* loop iterator                            */
   for (i = -1; i < YKINE_MAX_SERVO; ++i) {
      switch (i % 4) {
      case 0 : pos_joint   (my.port, i, 1500);
               break;
      case 1 : pos_joint   (my.port, i, 1875);
               break;
      case 2 : pos_joint   (my.port, i, 1000);
               break;
      case 3 : break;
      }
   }
   return 0;
}

char
bulldog            (void)
{
   /* femu    650  to   2350       */
   /* pate   1050  to   2400       */
   /* tibi    750  to   1900       */
   /*-------------- leg  femu  pate  tibi  time ---*/
   pose_leg ( 0, 2000, 1725, 1150);
   pose_leg (16, 1000, 1700, 1150);

   pose_leg ( 4, 1500, 1700, 1150);
   pose_leg (20, 1500, 1700, 1150);

   pose_leg ( 8, 1000, 1725, 1150);
   pose_leg (24, 2000, 1775, 1150);
   return 0;
}

char
bulldog_low        (int a_time)
{
   /* femu    650  to   2350       */
   /* pate   1050  to   2400       */
   /* tibi    750  to   1900       */
   /*-------------- leg  femu  pate  tibi  time ---*/
   pose_leg ( 0, 2000,  900, 1900);
   pose_leg (16, 1000,  900, 1900);
   pose_leg ( 4, 1500,  900, 1900);
   pose_leg (20, 1500,  900, 1900);
   pose_leg ( 8, 1000,  900, 1900);
   pose_leg (24, 2000,  900, 1900);

   /*> pose_leg ( 4, 1500, 1700, 1150);                                               <* 
    *> pose_leg (20, 1500, 1700, 1150);                                               <*/

   /*> pose_leg ( 8, 1000, 1725, 1150);                                               <* 
    *> pose_leg (24, 2000, 1775, 1150);                                               <*/

   /*> hex_move (my.port, LR, 2000, 2100, 1900,  a_time);                              <* 
    *> hex_move (my.port, RR, 2000, 2100, 1900,  a_time);                              <* 
    *> hex_move (my.port, LM, 1500, 2100, 1900,  a_time);                              <* 
    *> hex_move (my.port, RM, 1500, 2100, 1900,  a_time);                              <* 
    *> hex_move (my.port, LF, 1000, 2100, 1900,  a_time);                              <* 
    *> hex_move (my.port, RF, 1000, 2100, 1900,  a_time);                              <*/
   return 0;
}


char
test_exact_table   (void)
{
   int       i         = 0;       /* loop iterator                            */
   int       a_msec    =  500;
   /*> for (i = -1; i < YKINE_MAX_SERVO; ++i) {                                             <* 
    *>    switch (i % 4) {                                                            <* 
    *>    case 0 : pos_joint   (my.port, i, 1500);                                     <* 
    *>             break;                                                             <* 
    *>    case 1 : pos_joint   (my.port, i, 1900);                                     <* 
    *>             break;                                                             <* 
    *>    case 2 : pos_joint   (my.port, i, 1100);                                     <* 
    *>             break;                                                             <* 
    *>    case 3 : break;                                                             <* 
    *>    }                                                                           <* 
    *> }                                                                              <*/
   /*> usleep (a_msec * 1000);                                                        <*/
}

char
test_exact         (void)
{
   int       i         = 0;       /* loop iterator                            */
   /*---(#0)-----------------------------*/
   pos_joint   (my.port, 0, 1500);
   pos_joint   (my.port, 1, 1500);
   pos_joint   (my.port, 2, 1300);
   /*---(#1)-----------------------------*/
   pos_joint   (my.port, 4, 1500);
   pos_joint   (my.port, 5, 1525);
   pos_joint   (my.port, 6, 1425);
   /*---(#2)-----------------------------*/
   pos_joint   (my.port, 8, 1500);
   pos_joint   (my.port, 9, 1550);
   pos_joint   (my.port,10, 1550);
   /*---(#5)-----------------------------*/
   pos_joint   (my.port,16, 1500);
   pos_joint   (my.port,17, 1500);
   pos_joint   (my.port,18, 1300);
   /*---(#4)-----------------------------*/
   pos_joint   (my.port,20, 1500);
   pos_joint   (my.port,21, 1725);
   pos_joint   (my.port,22, 1750);
   /*---(#3)-----------------------------*/
   pos_joint   (my.port,24, 1500);
   pos_joint   (my.port,25, 1625);
   pos_joint   (my.port,26, 1500);
   /*---(complete)-----------------------*/
   return 0;
}

/*> int                                                                                                                                                                                                <* 
 *> main_OLD     (int argc, char *argv[])                                                                                                                                                              <* 
 *> {                                                                                                                                                                                                  <* 
 *>    char        rc          = 0;       /+ generic return code                      +/                                                                                                               <* 
 *>    char        rc2         = 0;       /+ generic return code                      +/                                                                                                               <* 
 *>    int         i           = 0;                                                                                                                                                                    <* 
 *>    int         j           = 0;                                                                                                                                                                    <* 
 *>    char        buf[500]    = "";                                                                                                                                                                   <* 
 *>    char       *a           = NULL;                                                                                                                                                                 <* 
 *>    tTSPEC      timer;                                                                                                                                                                              <* 
 *>    double      x_len       = 0.00;                                                                                                                                                                 <* 
 *>    double      x_sec       = 0.00;                                                                                                                                                                 <* 
 *>    double      x_secb      = 0.00;                                                                                                                                                                 <* 
 *>    double      x_sece      = 0.00;                                                                                                                                                                 <* 
 *>    double      x_dur       = 0.00;                                                                                                                                                                 <* 
 *>    double      x_degb      = 0.00;                                                                                                                                                                 <* 
 *>    double      x_dege      = 0.00;                                                                                                                                                                 <* 
 *>    double      x_zero      = 0.00;                                                                                                                                                                 <* 
 *>    int         x_seq       = -1;                                                                                                                                                                   <* 
 *>    int         x_line      = -1;                                                                                                                                                                   <* 
 *>    int         x_index     = -1;                                                                                                                                                                   <* 
 *>    int         x_servo     = -1;                                                                                                                                                                   <* 
 *>    char        x_label     [LEN_LABEL];                                                                                                                                                            <* 
 *>    char        x_leg       [LEN_LABEL];                                                                                                                                                            <* 
 *>    char        x_seg       [LEN_LABEL];                                                                                                                                                            <* 
 *>    char        x_rc        = '-';                                                                                                                                                                  <* 
 *>    char        x_rc2       = '-';                                                                                                                                                                  <* 
 *>    int         c           = 0;                                                                                                                                                                    <* 
 *>    /+---(initialize)---------------------+/                                                                                                                                                        <* 
 *>    if (rc == 0)  rc = yURG_logger  (argc, argv);                                                                                                                                                   <* 
 *>    if (rc == 0)  rc = PROG_init    ();                                                                                                                                                             <* 
 *>    if (rc == 0)  rc = yURG_urgs    (argc, argv);                                                                                                                                                   <* 
 *>    if (rc == 0)  rc = PROG_args    (argc, argv);                                                                                                                                                   <* 
 *>    if (rc == 0)  rc = PROG_begin   ();                                                                                                                                                             <* 
 *>    if (rc != 0)  {                                                                                                                                                                                 <* 
 *>       PROG_end     ();                                                                                                                                                                             <* 
 *>       exit (-1);                                                                                                                                                                                   <* 
 *>    }                                                                                                                                                                                               <* 
 *>    /+> yKINE_init      (0);                                                           <+/                                                                                                          <* 
 *>    /+> yKINE_center    (0.0, 0.0, 0.0);                                               <+/                                                                                                          <* 
 *>    /+> yKINE_script    (&x_len);                                                      <+/                                                                                                          <* 
 *>    /+> yKINE_moves_rpt ();                                                            <+/                                                                                                          <* 
 *>    DATA_list       ();                                                                                                                                                                             <* 
 *>    DATA_adj_table  ();                                                                                                                                                                             <* 
 *>    /+> printf ("script length %8.3lf\n", x_len);                                      <*                                                                                                           <* 
 *>     *> if (x_len <= 0.0) {                                                            <*                                                                                                           <* 
 *>     *>    PROG_end     ();                                                            <*                                                                                                           <* 
 *>     *>    exit (-2);                                                                  <*                                                                                                           <* 
 *>     *> }                                                                              <+/                                                                                                          <* 
 *>                                                                                                                                                                                                    <* 
 *>                                                                                                                                                                                                    <* 
 *>    /+> return 0;                                                                      <+/                                                                                                          <* 
 *>                                                                                                                                                                                                    <* 
 *>    /+---(show)-----------------------------------------+/                                                                                                                                          <* 
 *>    /+> for (i = YKINE_RR; i <= YKINE_LR; ++i) {                                                                                                                  <*                                <* 
 *>     *>    /+> printf ("leg %d\n", i);                                                     <+/                                                                    <*                                <* 
 *>     *>    for (j = YKINE_FEMU; j <= YKINE_TIBI; ++j) {                                                                                                           <*                                <* 
 *>     *>       /+> printf ("seg %d\n", j);                                                  <+/                                                                    <*                                <* 
 *>     *>       c = 0;                                                                                                                                              <*                                <* 
 *>     *>       for (x_sec = 0.00; x_sec < x_len; x_sec += 0.01) {                                                                                                  <*                                <* 
 *>     *>          x_index = DATA_find  (i, j);                                                                                                                     <*                                <* 
 *>     *>          if (x_index < 0)  continue;                                                                                                                      <*                                <* 
 *>     *>          x_servo = g_servo_data [x_index].ykine;                                                                                                          <*                                <* 
 *>     *>          if (x_servo < 0)  continue;                                                                                                                      <*                                <* 
 *>     *>          rc = yKINE_move_curone (x_servo, x_sec);                                                                                                         <*                                <* 
 *>     *>          if      (rc  < 0)  x_rc  = '?';                                                                                                                  <*                                <* 
 *>     *>          else if (rc  > 0)  x_rc  = 'y';                                                                                                                  <*                                <* 
 *>     *>          else               x_rc  = '-';                                                                                                                  <*                                <* 
 *>     *>          strlcpy (x_leg, g_servo_data [x_index].leg_name, LEN_LABEL);                                                                                     <*                                <* 
 *>     *>          strlcpy (x_seg, g_servo_data [x_index].seg_name, LEN_LABEL);                                                                                     <*                                <* 
 *>     *>          rc2     = yKINE_servo_move   (i, j, x_label, &x_secb, &x_sece, &x_dur , &x_degb, &x_dege, &x_seq, &x_line);                                      <*                                <* 
 *>     *>          if      (rc2 < 0)  x_rc2 = '?';                                                                                                                  <*                                <* 
 *>     *>          else if (rc2 > 0)  x_rc2 = 'y';                                                                                                                  <*                                <* 
 *>     *>          else               x_rc2 = '-';                                                                                                                  <*                                <* 
 *>     *>          /+> printf ("x_servo = %d, leg=%-12.12s, seg=%-10.10s, rc=%2d, rc2=%2d\n", x_servo, x_leg, x_seg, rc, rc2);   <+/                                <*                                <* 
 *>     *>          if (rc2 > 0) {                                                                                                                                   <*                                <* 
 *>     *>             if ( c      == 0) {                                                                                                                           <*                                <* 
 *>     *>                if (j == YKINE_FEMU)  printf ("%-12.12s ====================================================================================\n", x_leg);   <*                                <* 
 *>     *>                printf ("   %-10.10s - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n", x_seg);                       <*                                <* 
 *>     *>             }                                                                                                                                             <*                                <* 
 *>     *>             if ((c % 5) == 0)  printf ("   --secs-- - -    ----beg- ----end- ----dur-    ---label----    --degb-- --dege--    -seq- -rec-\n");            <*                                <* 
 *>     *>             printf ("   ");                                                                                                                               <*                                <* 
 *>     *>             printf ("%8.3lf %c %c    %8.3lf %8.3lf %8.3lf", x_sec, x_rc, x_rc2, x_secb, x_sece, x_dur);                                                   <*                                <* 
 *>     *>             printf ("    %-12.12s"                  , x_label);                                                                                           <*                                <* 
 *>     *>             printf ("    %8.1lf %8.1lf"             , x_degb, x_dege);                                                                                    <*                                <* 
 *>     *>             printf ("    %5d %5d\n"                , x_seq, x_line);                                                                                      <*                                <* 
 *>     *>             ++c;                                                                                                                                          <*                                <* 
 *>     *>          }                                                                                                                                                <*                                <* 
 *>     *>       }                                                                                                                                                   <*                                <* 
 *>     *>       printf ("\n\n");                                                                                                                                    <*                                <* 
 *>     *>    }                                                                                                                                                      <*                                <* 
 *>     *> }                                                                                                                                                         <+/                               <* 
 *>    /+> printf ("\n");                                                              <+/                                                                                                             <* 
 *>                                                                                                                                                                                                    <* 
 *>    /+> while (1) {                                                                              <*                                                                                                 <* 
 *>     *>    /+---(wait)-----------------------------------------+/                                <*                                                                                                 <* 
 *>     *>    yKINE_move_curall (x_sec);                                                            <*                                                                                                 <* 
 *>     *>    for (i = YKINE_RR; i <= YKINE_LR; ++i) {                                              <*                                                                                                 <* 
 *>     *>       for (j = YKINE_FEMU; j <= YKINE_TIBI; ++j) {                                       <*                                                                                                 <* 
 *>     *>          rc = yKINE_servo_deg (i, j, &x_deg);                                            <*                                                                                                 <* 
 *>     *>          if (rc > 0) {                                                                   <*                                                                                                 <* 
 *>     *>             printf ("%8.3lf", x_sec);                                                    <*                                                                                                 <* 
 *>     *>             printf ("  %d  %d", i, j);                                                   <*                                                                                                 <* 
 *>     *>             printf ("  %c  %8.1lf\n", (rc == 0) ? '-' : 'y', x_deg);                     <*                                                                                                 <* 
 *>     *>          }                                                                               <*                                                                                                 <* 
 *>     *>       }                                                                                  <*                                                                                                 <* 
 *>     *>    }                                                                                     <*                                                                                                 <* 
 *>     *>    /+> printf ("\n");                                                              <+/   <*                                                                                                 <* 
 *>     *>    x_sec += 0.01;                                                                        <*                                                                                                 <* 
 *>     *>    timer.tv_sec  = 0;                                                                    <*                                                                                                 <* 
 *>     *>    timer.tv_nsec = 10000000;   /+   0.01 sec  +/                                         <*                                                                                                 <* 
 *>     *>    nanosleep (&timer, NULL);                                                             <*                                                                                                 <* 
 *>     *>    if (x_sec > x_len) break;                                                             <*                                                                                                 <* 
 *>     *> }                                                                                        <+/                                                                                                <* 
 *>                                                                                                                                                                                                    <* 
 *>                                                                                                                                                                                                    <* 
 *>    /+> while (1) {                                                                    <*                                                                                                           <* 
 *>     *>    /+---(wait)-----------------------------------------+/                      <*                                                                                                           <* 
 *>     *>    yKINE_move_curall (x_sec);                                                  <*                                                                                                           <* 
 *>     *>    printf ("%8.3lf", x_sec);                                                   <*                                                                                                           <* 
 *>     *>    for (i = YKINE_RR; i <= YKINE_LR; ++i) {                                    <*                                                                                                           <* 
 *>     *>       for (j = YKINE_FEMU; j <= YKINE_TIBI; ++j) {                             <*                                                                                                           <* 
 *>     *>          rc = yKINE_servo_deg (i, j, &x_deg);                                  <*                                                                                                           <* 
 *>     *>          printf ("  %c %8.1lf", (rc == 0) ? '-' : 'y', x_deg);                 <*                                                                                                           <* 
 *>     *>       }                                                                        <*                                                                                                           <* 
 *>     *>    }                                                                           <*                                                                                                           <* 
 *>     *>    printf ("\n");                                                              <*                                                                                                           <* 
 *>     *>    x_sec += 0.01;                                                              <*                                                                                                           <* 
 *>     *>    timer.tv_sec  = 0;                                                          <*                                                                                                           <* 
 *>     *>    timer.tv_nsec = 10000000;   /+   0.01 sec  +/                               <*                                                                                                           <* 
 *>     *>    nanosleep (&timer, NULL);                                                   <*                                                                                                           <* 
 *>     *>    if (x_sec > x_len) break;                                                   <*                                                                                                           <* 
 *>     *> }                                                                              <+/                                                                                                          <* 
 *>                                                                                                                                                                                                    <* 
 *>    my.port = COMM_open ("/dev/usb/ttyUSB0");                                                                                                                                                        <* 
 *>    hex_align_table  (my.port);                                                                                                                                                                      <* 
 *>    bulldog ();                                                                                                                                                                                     <* 
 *>    /+> for (x_sec = 0.00; x_sec < x_len; x_sec += 0.01) {                                                                                                                                    <*    <* 
 *>     *>    c = 0;                                                                                                                                                                             <*    <* 
 *>     *>    /+---(cycle legs)------------------+/                                                                                                                                              <*    <* 
 *>     *>    for (i = YKINE_RR; i <= YKINE_LR; ++i) {                                                                                                                                           <*    <* 
 *>     *>       /+---(cycle segments)-----------+/                                                                                                                                              <*    <* 
 *>     *>       for (j = YKINE_FEMU; j <= YKINE_TIBI; ++j) {                                                                                                                                    <*    <* 
 *>     *>          /+---(check)-----------------+/                                                                                                                                              <*    <* 
 *>     *>          x_index = DATA_find  (i, j);                                                                                                                                                 <*    <* 
 *>     *>          if (x_index < 0)  continue;                                                                                                                                                  <*    <* 
 *>     *>          x_servo = g_servo_data [x_index].ykine;                                                                                                                                      <*    <* 
 *>     *>          x_zero  = g_servo_data [x_index].zero;                                                                                                                                       <*    <* 
 *>     *>          if (x_servo < 0)  continue;                                                                                                                                                  <*    <* 
 *>     *>          /+---(set current)-----------+/                                                                                                                                              <*    <* 
 *>     *>          /+> rc = yKINE_move_curone (x_servo, x_sec);                              <+/                                                                                                <*    <* 
 *>     *>          if      (rc  < 0)  x_rc  = '?';                                                                                                                                              <*    <* 
 *>     *>          else if (rc  > 0)  x_rc  = 'y';                                                                                                                                              <*    <* 
 *>     *>          else               x_rc  = '-';                                                                                                                                              <*    <* 
 *>     *>          strlcpy (x_leg, g_servo_data [x_index].leg_name, LEN_LABEL);                                                                                                                 <*    <* 
 *>     *>          strlcpy (x_seg, g_servo_data [x_index].seg_name, LEN_LABEL);                                                                                                                 <*    <* 
 *>     *>          /+---(get position)----------+/                                                                                                                                              <*    <* 
 *>     *>          /+> rc2     = yKINE_servo_move   (i, j, x_label, &x_secb, &x_sece, &x_dur , &x_degb, &x_dege, &x_seq, &x_line);   <+/                                                        <*    <* 
 *>     *>          if      (rc2 < 0)  x_rc2 = '?';                                                                                                                                              <*    <* 
 *>     *>          else if (rc2 > 0)  x_rc2 = 'y';                                                                                                                                              <*    <* 
 *>     *>          else               x_rc2 = '-';                                                                                                                                              <*    <* 
 *>     *>          /+> printf ("x_servo = %d, leg=%-12.12s, seg=%-10.10s, rc=%2d, rc2=%2d\n", x_servo, x_leg, x_seg, rc, rc2);   <+/                                                            <*    <* 
 *>     *>          if (rc2 > 0) {                                                                                                                                                               <*    <* 
 *>     *>             /+> if (i == 3) {                                                      <+/                                                                                                <*    <* 
 *>     *>                if ((c % 45) == 0)  printf ("\n   --secs-- - -    - ---leg------ - ---seg----    ----beg- ----end- ----dur-    ---label----    --degb-- --dege--    -seq- -rec-\n");   <*    <* 
 *>     *>                if ((c %  5) == 0)  printf ("\n");                                                                                                                                     <*    <* 
 *>     *>                printf ("   ");                                                                                                                                                        <*    <* 
 *>     *>                printf ("%8.3lf %c %c"                  , x_sec, x_rc, x_rc2);                                                                                                         <*    <* 
 *>     *>                printf ("    %1d %-12.12s %1d %-10.10s" , i, x_leg, j, x_seg);                                                                                                         <*    <* 
 *>     *>                printf ("    %8.3lf %8.3lf %8.3lf"      , x_secb, x_sece, x_dur);                                                                                                      <*    <* 
 *>     *>                printf ("    %-12.12s"                  , x_label);                                                                                                                    <*    <* 
 *>     *>                printf ("    %8.1lf %8.1lf"             , x_degb, x_dege);                                                                                                             <*    <* 
 *>     *>                printf ("    %5d %5d\n"                 , x_seq, x_line);                                                                                                              <*    <* 
 *>     *>                printf ("send #%02d P%d T%d\n", g_servo_data [x_index].servo, (int) (1500 + ((x_dege - x_zero) * 10.0)), (int) (x_dur * 1000.0));                                      <*    <* 
 *>     *>                move_joint         (my.port, x_index, (int) (1500 + ((x_dege - x_zero) * 10.0)), (int) (x_dur * 1000.0));                                                               <*    <* 
 *>     *>             /+> }                                                                  <+/                                                                                                <*    <* 
 *>     *>             ++c;                                                                                                                                                                      <*    <* 
 *>     *>          }                                                                                                                                                                            <*    <* 
 *>     *>       }                                                                                                                                                                               <*    <* 
 *>     *>    }                                                                                                                                                                                  <*    <* 
 *>     *>    /+---(sleep)-----------------------+/                                                                                                                                              <*    <* 
 *>     *>    timer.tv_sec  = 0;                                                                                                                                                                 <*    <* 
 *>     *>    /+> timer.tv_nsec = 50000000;                                                   <+/                                                                                                <*    <* 
 *>     *>    timer.tv_nsec = 10000000;                                                                                                                                                          <*    <* 
 *>     *>    nanosleep (&timer, NULL);                                                                                                                                                          <*    <* 
 *>     *>    /+---(done)------------------------+/                                                                                                                                              <*    <* 
 *>     *>    /+> if (x_sec > 4.000)  break;                                                  <+/                                                                                                <*    <* 
 *>     *> }                                                                                                                                                                                     <+/   <* 
 *>    printf ("\n\n\nDONE DONE\n\n\n");                                                                                                                                                               <* 
 *>    COMM_close (my.port);                                                                                                                                                                            <* 
 *>    return 0;                                                                                                                                                                                       <* 
 *>                                                                                                                                                                                                    <* 
 *>                                                                                                                                                                                                    <* 
 *>    my.port = COMM_open ("/dev/usb/ttyUSB0");                                                                                                                                                        <* 
 *>    hex_align_table  (my.port);                                                                                                                                                                      <* 
 *>    if (argc == 1) {                                                                                                                                                                                <* 
 *>       printf ("nothing requested, so just aligned joints\n");                                                                                                                                      <* 
 *>       return 0;                                                                                                                                                                                    <* 
 *>    }                                                                                                                                                                                               <* 
 *>    a = argv [1];                                                                                                                                                                                   <* 
 *>    if      (strcmp (a, "--attn"        ) == 0)   pose_fixed     ( 1500, 1500, 1500);                                                                                                               <* 
 *>    else if (strcmp (a, "--fmin"        ) == 0)   pose_fixed     (  700, 1500, 1500);                                                                                                               <* 
 *>    else if (strcmp (a, "--fmax"        ) == 0)   pose_fixed     ( 2300, 1500, 1500);                                                                                                               <* 
 *>    else if (strcmp (a, "--pmin"        ) == 0)   pose_fixed     ( 1500,  600, 1500);                                                                                                               <* 
 *>    else if (strcmp (a, "--pmax"        ) == 0)   pose_fixed     ( 1500, 1875, 1000);                                                                                                               <* 
 *>    else if (strcmp (a, "--tmin"        ) == 0)   pose_fixed     ( 1500, 1500,  750);                                                                                                               <* 
 *>    else if (strcmp (a, "--t10"         ) == 0)   pose_fixed     ( 1500, 1500,  900);                                                                                                               <* 
 *>    else if (strcmp (a, "--t20"         ) == 0)   pose_fixed     ( 1500, 1500, 1050);                                                                                                               <* 
 *>    else if (strcmp (a, "--t30"         ) == 0)   pose_fixed     ( 1500, 1500, 1200);                                                                                                               <* 
 *>    else if (strcmp (a, "--t40"         ) == 0)   pose_fixed     ( 1500, 1500, 1350);                                                                                                               <* 
 *>    else if (strcmp (a, "--tmax"        ) == 0)   pose_fixed     ( 1500, 1500, 1800);                                                                                                               <* 
 *>    else if (strcmp (a, "--bulldog"     ) == 0)   bulldog        ();                                                                                                                                <* 
 *>    else if (strcmp (a, "--bulldog_low" ) == 0)   bulldog_low    (my.port);                                                                                                                          <* 
 *>    /+> test_exact_table ();                                                           <+/                                                                                                          <* 
 *>    /+> test_attention ();                                                             <+/                                                                                                          <* 
 *>    /+> usleep  (1000000);                                                             <+/                                                                                                          <* 
 *>    /+> test_original ();                                                              <+/                                                                                                          <* 
 *>    /+> test_all_joints    ();                                                         <+/                                                                                                          <* 
 *>    /+> bulldog_low   (1000);                                                          <+/                                                                                                          <* 
 *>    /+> usleep  (1000000);                                                             <+/                                                                                                          <* 
 *>    /+> bulldog       ( 300);                                                          <+/                                                                                                          <* 
 *>    /+> usleep  (1000000);                                                             <+/                                                                                                          <* 
 *>    /+> manta_ray     ();                                                              <+/                                                                                                          <* 
 *>    /+> i = 16;                                                                        <*                                                                                                           <* 
 *>     *> pos_joint   (my.port, i, 1500);                                                 <*                                                                                                           <* 
 *>     *> move_joint  (my.port, i, 1200, 1000);                                           <*                                                                                                           <* 
 *>     *> move_joint  (my.port, i, 1900, 1000);                                           <*                                                                                                           <* 
 *>     *> move_joint  (my.port, i, 1500, 1000);                                           <+/                                                                                                          <* 
 *>    /+> if (scripter () != 0) {                                                                     <*                                                                                              <* 
 *>     *>    test_attention();                                                                        <*                                                                                              <* 
 *>     *>    /+> test_repeater();                                                            <+/      <*                                                                                              <* 
 *>     *>    /+> test_trig();                                                                <+/      <*                                                                                              <* 
 *>     *>    /+> test_joints();                                                              <+/      <*                                                                                              <* 
 *>     *>    /+> test_doreme();                                                                 <+/   <*                                                                                              <* 
 *>     *> }                                                                                           <+/                                                                                             <* 
 *>    COMM_close (my.port);                                                                                                                                                                            <* 
 *>    return 0;                                                                                                                                                                                       <* 
 *> }                                                                                                                                                                                                  <*/
