/*============================----beg-of-source---============================*/

#include "golem.h"



int       x_port    = 0;       /* port file descriptor                     */

#define   DEBUG_O   if (debug == 'y')
char      debug     = '-';


#define   DEG2PTS    10
#define   SEC2MSEC   1000.0


typedef  struct cARM tARM;
struct  cARM {
   int         center;
} arm [10] = { 1500, 1520, 1560, 1460, 1570, 1100 };


#define     MAX_SERVO   32
#define     LEN_NAME    20
typedef     struct cSERVO   tSERVO;
struct cSERVO {
   /*---(key info)----------*/
   char        leg;
   char        seg;
   char        servo;
   /*---(descriptive)-------*/
   char        leg_name    [LEN_NAME];
   char        leg_short   [LEN_NAME];
   char        seg_name    [LEN_NAME];
   char        seg_short   [LEN_NAME];
   /*---(setup data)--------*/
   int         adjust;
   int         min;
   int         attn;
   int         max;
   char        flip;
   int         adj_min;
   int         adj_attn;
   int         adj_max;
   char        min_dir    [LEN_NAME];
};
tSERVO      s_servo   [MAX_SERVO] = {
   /* --leg---  ---seg---- servo  ---legname------  abbr   ---segname-------  -abbr-                                                          */
   {  YKINE_RR, YKINE_FEMU,  15 , "right_rear"    , "rr" , "femur"          , ""    ,    0,  700, 1500, 2300,   1,  -50,    0,   25, "cclock" },
   {  YKINE_RR, YKINE_PATE,   1 , "right_rear"    , "rr" , "patella"        , ""    ,  -25,  600, 1500, 1900,  -1,  -25,  -25,  -25, "up"     },
   {  YKINE_RR, YKINE_FEMU,   2 , "right_rear"    , "rr" , "tibia"          , ""    , -225,  750, 1500, 1800,   1, -225, -225, -225, "out"    },
   {  -1      , -1        ,  -1 , ""              , ""   , ""               , ""    ,    0,    0,    0,    0,   1,    0,    0,    0, ""       },
   {  YKINE_RM, YKINE_FEMU,   4 , "right_middle"  , "rm" , "femur"          , ""    ,    0,  700, 1500, 2300,   1,  -25,    0,   75, "cclock" },
   {  YKINE_RM, YKINE_PATE,   5 , "right_middle"  , "rm" , "patella"        , ""    ,   50,  600, 1500, 1900,  -1,   75,   75,   35, "up"     },
   {  YKINE_RM, YKINE_FEMU,   6 , "right_middle"  , "rm" , "tibia"          , ""    , -150,  750, 1500, 1800,   1, -125, -150, -150, "out"    },
   {   -1      , -1        , -1 , ""              , ""   , ""               , ""    ,    0,    0,    0,    0,   1,    0,    0,    0, ""       },
   {  YKINE_RF, YKINE_FEMU,   8 , "right_front"   , "rf" , "femur"          , ""    ,   25,  700, 1500, 2300,   1,   25,   25,  100, "cclock" },
   {  YKINE_RF, YKINE_PATE,   9 , "right_front"   , "rf" , "patella"        , ""    ,   40,  600, 1500, 1900,  -1,   50,   50,   25, "up"     },
   {  YKINE_RF, YKINE_FEMU,  10 , "right_front"   , "rf" , "tibia"          , ""    ,   75,  750, 1500, 1800,   1,   50,   50,   75, "out"    },
   {  -1      , -1        ,  -1 , ""              , ""   , ""               , ""    ,    0,    0,    0,    0,   1,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 , ""              , ""   , ""               , ""    ,    0,    0,    0,    0,   1,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 , ""              , ""   , ""               , ""    ,    0,    0,    0,    0,   1,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 , ""              , ""   , ""               , ""    ,    0,    0,    0,    0,   1,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 , ""              , ""   , ""               , ""    ,    0,    0,    0,    0,   1,    0,    0,    0, ""       },
   {  YKINE_LR, YKINE_FEMU,  16 , "left_rear"     , "lr" , "femur"          , ""    ,   50,  700, 1500, 2300,   1,   25,   50,   50, "cclock" },
   {  YKINE_LR, YKINE_PATE,  17 , "left_rear"     , "lr" , "patella"        , ""    ,    0,  600, 1500, 1900,   1,   50,  -25,  -25, "up"     },
   {  YKINE_LR, YKINE_FEMU,  18 , "left_rear"     , "lr" , "tibia"          , ""    , -175,  750, 1500, 1800,  -1, -225, -175, -175, "out"    },
   {  -1      , -1        ,  -1 , ""              , ""   , ""               , ""    ,    0,    0,    0,    0,   1,    0,    0,    0, ""       },
   {  YKINE_LM, YKINE_FEMU,  20 , "left_middle"   , "lm" , "femur"          , ""    ,  -50,  700, 1500, 2300,   1,    0,  -50,  -50, "cclock" },
   {  YKINE_LM, YKINE_PATE,  21 , "left_middle"   , "lm" , "patella"        , ""    ,  225,  600, 1500, 1900,   1,  250,  200,  250, "up"     },
   {  YKINE_LM, YKINE_FEMU,  22 , "left_middle"   , "lm" , "tibia"          , ""    ,  225,  750, 1500, 1800,  -1,  225,  250,  225, "out"    },
   {  -1      , -1        ,  -1 , ""              , ""   , ""               , ""    ,    0,    0,    0,    0,   1,    0,    0,    0, ""       },
   {  YKINE_RF, YKINE_FEMU,  24 , "left_front"    , "lf" , "femur"          , ""    ,    0,  700, 1500, 2300,   1,  -50,    0,    0, "cclock" },
   {  YKINE_RF, YKINE_PATE,  25 , "left_front"    , "lf" , "patella"        , ""    ,  250,  600, 1500, 1900,   1,  250,  250,  250, "up"     },
   {  YKINE_RF, YKINE_FEMU,  26 , "left_front"    , "lf" , "tibia"          , ""    ,    0,  750, 1500, 1800,  -1,  -25,   25,    0, "out"    },
   {  -1      , -1        ,  -1 , ""              , ""   , ""               , ""    ,    0,    0,    0,    0,   1,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 , ""              , ""   , ""               , ""    ,    0,    0,    0,    0,   1,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 , ""              , ""   , ""               , ""    ,    0,    0,    0,    0,   1,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 , ""              , ""   , ""               , ""    ,    0,    0,    0,    0,   1,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 , ""              , ""   , ""               , ""    ,    0,    0,    0,    0,   1,    0,    0,    0, ""       },
};

#define   MAX_POSES     100
struct cPOSES {
   char        title       [LEN_NAME];
   char        abbr        [10];
   int         pos         [18];
} s_poses [MAX_POSES] = {
   /*---name----------*/ /*-short-*/ /*--RR--#0------*//*--RM--#1------*//*--RF--#2------*//*--LF--#3------*//*--LM--#4------*//*--LR--#5------*/
   { "attention"       , "attn"    , 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500 },
   { "bulldog"         , ""        , 2000, 1725, 1150, 1500, 1700, 1150, 1000, 1725, 1150, 2000, 1775, 1150, 1500, 1700, 1150, 1000, 1700, 1150 },
};


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

char       leg_name[6][15] = {
   "right-rear",
   "right-middle",
   "right-front",
   "left-rear",
   "left-middle",
   "left-front"
};

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
   for (i = 0; i < MAX_SERVO; ++i) {
      if (s_servo [i].leg <  0) continue;
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
 *>       hex_aa (x_port, 1500, 1500, 1500,  500);                                     <* 
 *>    }                                                                               <* 
 *>    return 0;                                                                       <* 
 *> }                                                                                  <*/

char
test_repeater      (void)
{
   int       i         = 0;       /* loop iterator                            */
   for (i = 0; i < 100; ++i) {
      hex_aa (x_port, 1000, 1500, 1000,  500);
      usleep( 500000);
      hex_aa (x_port, 1500, 1300, 1500,  500);
      usleep( 500000);
      hex_aa (x_port, 2000, 1500, 1000,  500);
      usleep( 500000);
      hex_aa (x_port, 1500, 1700, 1500,  500);
      usleep( 500000);
      hex_aa (x_port, 1500, 2400, 1800,  500);
      usleep( 500000);
      hex_aa (x_port, 1500, 2400,  800,  500);
      usleep( 500000);
      hex_move (x_port, LR, 1200, 2400,  800,  500);
      hex_move (x_port, LM,  700, 2400,  800,  500);
      hex_move (x_port, LF,   700, 1200, 1600,  500);
      hex_move (x_port, RR,  1200, 2400,  800,  500);
      hex_move (x_port, RM,  700, 2400,  800,  500);
      hex_move (x_port, RF,   700, 1200, 1600,  500);
      /*> exit(0);                                                                    <*/
      usleep( 500000);
      hex_move (x_port, RM, 1500, 1500,  800,  500);
      hex_move (x_port, LM, 1500, 1500,  800,  500);
      usleep( 500000);
      hex_move (x_port, RM, 1200, 1500,  800,  250);
      hex_move (x_port, LM, 1200, 1500,  800,  250);
      usleep( 250000);
      hex_move (x_port, RM, 1800, 1500,  800,  500);
      hex_move (x_port, LM, 1800, 1500,  800,  500);
      usleep( 500000);
      hex_move (x_port, RM, 1200, 1500,  800,  500);
      hex_move (x_port, LM, 1200, 1500,  800,  500);
      usleep( 500000);
      hex_move (x_port, RM, 1500, 1500,  800,  250);
      hex_move (x_port, LM, 1500, 1500,  800,  250);
      usleep( 250000);
   }
   return 0;
}

char
test_original      (void)
{
   int       i         = 0;       /* loop iterator                            */
   hex_aa (x_port, 1000, 1500, 1000,  500);
   usleep( 500000);
   hex_aa (x_port, 1500, 1300, 1500,  500);
   usleep( 500000);
   hex_aa (x_port, 2000, 1500, 1000,  500);
   usleep( 500000);
   hex_aa (x_port, 1500, 1700, 1500,  500);
   usleep( 500000);
   hex_aa (x_port, 1500, 2400, 1800,  500);
   usleep( 500000);
   hex_aa (x_port, 1500, 2400,  800,  500);
   usleep( 500000);
   hex_move (x_port, LR, 1200, 2400,  800,  500);
   hex_move (x_port, LM,  700, 2400,  800,  500);
   hex_move (x_port, LF,   700, 1200, 1600,  500);
   hex_move (x_port, RR,  1200, 2400,  800,  500);
   hex_move (x_port, RM,  700, 2400,  800,  500);
   hex_move (x_port, RF,   700, 1200, 1600,  500);
   usleep( 500000);
   hex_move (x_port, RM, 1500, 1500,  800,  500);
   hex_move (x_port, LM, 1500, 1500,  800,  500);
   usleep( 500000);
   hex_move (x_port, RM, 1200, 1500,  800,  250);
   hex_move (x_port, LM, 1200, 1500,  800,  250);
   usleep( 250000);
   for (i = 0; i < 5; ++i) {
      hex_move (x_port, RM, 1800, 1500,  800,  500);
      hex_move (x_port, LM, 1800, 1500,  800,  500);
      usleep( 500000);
      hex_move (x_port, RM, 1200, 1500,  800,  500);
      hex_move (x_port, LM, 1200, 1500,  800,  500);
      usleep( 500000);
   }
   hex_move (x_port, RM, 1500, 1500,  800,  250);
   hex_move (x_port, LM, 1500, 1500,  800,  250);
   usleep( 250000);
   return 0;
}

char
test_trig          (void)
{
   int       i         = 0;       /* loop iterator                            */
   int       hip       = 0;
   hex_aa (x_port, 1500, 1500, 1500,  500);
   usleep( 500000);
   hex_move (x_port, RM, 2100, 1500,  800,  250);
   hex_move (x_port, LM, 2100, 1500,  800,  250);
   usleep( 500000);
   i = 0;
   while (1) {
      i += 30;
      hip = 1500 + cos((double) (i) / 360.0 * 3.14159) * 700;
      printf("%3d so hip at %4d\n", i, hip);
      /*> hex_move (x_port, RM, hip , 1500,  800,   35);                              <*/
      hex_move (x_port, LM, hip , 1500,  800,   80);
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
   hex_move (x_port, LR, 1200, 1500,  750,  500);
   hex_move (x_port, RR, 1200, 1500,  750,  500);
   hex_move (x_port, LM,  700, 1500,  750,  500);
   hex_move (x_port, RM,  700, 1500,  750,  500);
   hex_move (x_port, LF,  650, 1500,  750,  500);
   hex_move (x_port, RF,  650, 1500,  750,  500);
   return 0;
}

char
bulldog_OLD        (int a_time)
{
   /* femu    650  to   2350       */
   /* pate   1050  to   2400       */
   /* tibi    750  to   1900       */
   /*-------------- leg  femu  pate  tibi  time ---*/
   hex_move (x_port, LR, 2000, 1050,  750,  a_time);
   hex_move (x_port, RR, 2000, 1050,  750,  a_time);
   hex_move (x_port, LM, 1500, 1050,  750,  a_time);
   hex_move (x_port, RM, 1500, 1050,  750,  a_time);
   hex_move (x_port, LF, 1000, 1050,  750,  a_time);
   hex_move (x_port, RF, 1000, 1050,  750,  a_time);
   return 0;
}

char
bulldog_low_OLD    (int a_time)
{
   /* femu    650  to   2350       */
   /* pate   1050  to   2400       */
   /* tibi    750  to   1900       */
   /*-------------- leg  femu  pate  tibi  time ---*/
   hex_move (x_port, LR, 2000, 2100, 1900,  a_time);
   hex_move (x_port, RR, 2000, 2100, 1900,  a_time);
   hex_move (x_port, LM, 1500, 2100, 1900,  a_time);
   hex_move (x_port, RM, 1500, 2100, 1900,  a_time);
   hex_move (x_port, LF, 1000, 2100, 1900,  a_time);
   hex_move (x_port, RF, 1000, 2100, 1900,  a_time);
   return 0;
}

char
test_all_joints    (void)
{
   int       i = 0;
   hex_aa   (x_port, 1500, 1500, 1500,  500);
   /*---(move femur)------------------*/
   hex_aa   (x_port,  900, 1500, 1500,  500);
   usleep( 500000);
   hex_aa   (x_port, 2100, 1500, 1500,  500);
   usleep( 500000);
   /*---(move patella)----------------*/
   hex_aa   (x_port, 1500, 1050, 1500,  500);
   usleep( 500000);
   hex_aa   (x_port, 1500, 2300, 1500,  500);
   usleep( 500000);
   /*---(move tibia)------------------*/
   hex_aa   (x_port, 1500, 1500,  750,  500);
   usleep( 500000);
   hex_aa   (x_port, 1500, 1500, 1900,  500);
   usleep( 500000);
   hex_aa   (x_port, 1500, 1500,  750,  500);
   usleep( 500000);
   /*---(move patella)----------------*/
   hex_aa   (x_port, 1500, 2300, 1500,  500);
   usleep( 500000);
   hex_aa   (x_port, 1500, 1050, 1500,  500);
   usleep( 500000);
   /*---(move femur)------------------*/
   hex_aa   (x_port, 2100, 1500, 1500,  500);
   usleep( 500000);
   hex_aa   (x_port,  900, 1500, 1500,  500);
   usleep( 500000);
   /*---(done)--------------*/
   hex_aa   (x_port, 1500, 1500, 1500,  500);
   return 0;
}

char
test_joints        (void)
{
   int       i = 0;
   hex_aa( x_port, 1500, 1500, 1500, 500);
   for (i = 0; i < 6; ++i) {
      /*---(move femur)------------------*/
      hex_move (x_port, i,  650, 1500, 1500,  500);
      usleep( 500000);
      hex_move (x_port, i, 2350, 1500, 1500,  500);
      usleep( 500000);
      /*---(move patella)----------------*/
      hex_move (x_port, i, 1500, 1050, 1500,  500);
      usleep( 500000);
      hex_move (x_port, i, 1500, 2300, 1500,  500);
      usleep( 500000);
      /*---(move tibia)------------------*/
      hex_move (x_port, i, 1500, 1500,  750,  500);
      usleep( 500000);
      hex_move (x_port, i, 1500, 1500, 1900,  500);
      usleep( 500000);
   }
   return 0;
}

char
test_doreme        (void)
{
   hex_move (x_port, 2,  650, 1500, 1500,  500);
   usleep( 500000);
   hex_move (x_port, 2,  650, 2200, 1500,  500);
   usleep( 500000);
   hex_move (x_port, 2, 1600, 2200, 1500,  500);
   usleep( 500000);
   hex_move (x_port, 2, 1450, 1740, 1500,  300);
   usleep( 300000);
   hex_move (x_port, 2, 1600, 2200, 1500,  300);
   usleep( 300000);
   hex_move (x_port, 2, 1600, 1735, 1500,  300);
   usleep( 300000);
   hex_move (x_port, 2, 1600, 2200, 1500,  300);
   usleep( 300000);
   hex_move (x_port, 2, 1730, 1740, 1500,  300);
   usleep( 300000);
   hex_move (x_port, 2, 1600, 2200, 1500,  300);
   usleep( 300000);
   hex_move (x_port, 2, 1730, 1740, 1500,  300);
   usleep( 300000);
   hex_move (x_port, 2, 1600, 2200, 1500,  300);
   usleep( 300000);
   return 0;
}

char
test_box           (void)
{
   hex_move (x_port, 2,  650, 1500, 1500,  500);
   usleep( 500000);
   hex_move (x_port, 2,  650, 2200, 1500,  500);
   usleep( 500000);
   hex_move (x_port, 2, 1600, 2200, 1500,  500);
   usleep( 500000);
   hex_move (x_port, 2, 1450, 1740, 1500,  300);
   usleep( 300000);
   hex_move (x_port, 2, 1600, 2200, 1500,  300);
   usleep( 300000);
   hex_move (x_port, 2, 1600, 1735, 1500,  300);
   usleep( 300000);
   hex_move (x_port, 2, 1600, 2200, 1500,  300);
   usleep( 300000);
   hex_move (x_port, 2, 1730, 1740, 1500,  300);
   usleep( 300000);
   hex_move (x_port, 2, 1600, 2200, 1500,  300);
   usleep( 300000);
   hex_move (x_port, 2, 1730, 1740, 1500,  300);
   usleep( 300000);
   hex_move (x_port, 2, 1600, 2200, 1500,  300);
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
      /*> hex_move (x_port, xleg, (int) (femu * DEG2PTS) + 1500, (int) (pate * DEG2PTS) + 1500, 600 - (int) (tibi * DEG2PTS), (int) (pace * SEC2MSEC));   <*/
      hex_move (x_port, xleg, (int) (femu * DEG2PTS) + 1500, (int) (pate * DEG2PTS) + 1500, 600 - (int) (tibi * DEG2PTS),  50);
      /*> hex_move (x_port, leg, (femu * DEG2PTS) + 1500, (pate * DEG2PTS) + 1500, 600 - (tibi * DEG2PTS), pace * SEC2MSEC);   <*/
      /*> printf ("\n");                                                              <*/
   }
   printf("   done\n");
   /*---(complete)-------------------------*/
   return 0;
}

int
adjust             (int a_joint, int a_angle)
{
   /*---(locals)-------------------------*/
   int       i           =  0;
   int       x_min       =  0;
   int       x_attn      =  0;
   int       x_max       =  0;
   int       x_range     =  0;
   int       x_qtr       =  0;
   int       x_diff      =  0;
   int       x_start     =  0;
   float     x_pct       =  0;
   /*---(prepare)------------------------*/
   printf ("\n");
   printf ("focu   = %4d, angle  = %4d\n", i, a_angle);
   i      = a_joint;
   x_min  = s_servo [i].min;
   x_attn = s_servo [i].attn;
   x_max  = s_servo [i].max;
   printf ("x_min  = %4d, x_attn = %4d, x_max  = %4d\n", x_min, x_attn, x_max);
   printf ("adj_m  = %4d, adj_a  = %4d, adj_x  = %4d\n", s_servo[i].adj_min, s_servo[i].adj_attn, s_servo[i].adj_max);
   /*---(figure)-------------------------*/
   if (a_angle == x_attn) {
      printf ("EQUAL to attention\n");
      printf ("middle,                      so attn = %4d\n", s_servo [i].adj_attn);
      return s_servo [i].adj_attn;
   }
   if (a_angle <= x_attn) {
      printf ("LESSER than attention\n");
      x_range = (x_attn - x_min);
      x_qtr   = x_range / 4.0;
      if (a_angle <= x_min  + x_qtr) {
         printf ("smallest qtr of bottom (1/8), so min  = %4d\n", s_servo [i].adj_min);
         return s_servo [i].adj_min;
      }
      if (a_angle >= x_attn - x_qtr) {
         printf ("largest qtr of bottom (4/8),  so attn = %4d\n", s_servo [i].adj_attn);
         return s_servo [i].adj_attn;
      }
      x_diff  = s_servo [i].adj_attn - s_servo [i].adj_min;
      x_start = a_angle - x_min - x_qtr;
      x_pct   = x_start / (2.0 * x_qtr);
      printf ("x_range= %4d, x_qtr  = %4d, x_diff = %4d, x_start= %4d, x_pct  = %5.3f\n", x_range, x_qtr, x_diff, x_start, x_pct);
      printf ("middle half of bottom (2-3/8), so = %4d\n", s_servo [i].adj_min  + (int) (x_pct * x_diff));
      return s_servo [i].adj_min + (int) (x_pct * x_diff);
   } else {
      printf ("GREATER than attention\n");
      x_range = (x_max  - x_attn);
      x_qtr   = x_range / 4.0;
      if (a_angle >= x_max  - x_qtr) {
         printf ("largest qtr of top    (8/8), so max  = %4d\n", s_servo [i].adj_max);
         return s_servo [i].adj_max;
      }
      if (a_angle <= x_attn + x_qtr) {
         printf ("smallest qtr of top   (5/8), so attn = %4d\n", s_servo [i].adj_attn);
         return s_servo [i].adj_attn;
      }
      x_diff  = s_servo [i].adj_max  - s_servo [i].adj_attn;
      x_start = a_angle - x_attn + x_qtr;
      x_pct   = x_start / (2.0 * x_qtr);
      printf ("x_range= %4d, x_qtr  = %4d, x_diff = %4d, x_start= %4d, x_pct  = %5.3f\n", x_range, x_qtr, x_diff, x_start, x_pct);
      printf ("middle half of top    (6-7/8), so = %4d\n", s_servo [i].adj_attn + (int) (x_pct * x_diff));
      return s_servo [i].adj_min + (int) (x_pct * x_diff);
   }
   /*---(complete)-----------------------*/
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
   if (a_joint >= MAX_SERVO)      return -2;
   if (s_servo[a_joint].leg == -1)  return -3;
   /*---(filter and limit)---------------*/
   x_adjust = adjust (a_joint, a_angle);
   i        = a_joint;
   x_angle  = a_angle;
   if (x_angle  < s_servo [i].min)  x_angle = s_servo [i].min;
   if (x_angle  > s_servo [i].max)  x_angle = s_servo [i].max;
   x_flip  = (1500 + (x_angle - 1500) * s_servo [i].flip);
   x_new   = x_flip + x_adjust;
   /*---(send command)-------------------*/
   snprintf (buf, 1000, "#%d P%d\r"    , s_servo [a_joint].servo, x_new);
   write    (a_port, buf, strlen(buf));
   /*---(display debugging)--------------*/
   printf   ("#%d  %-15.15s  %-15.15s  %2d  %2d  ",
         s_servo [a_joint].leg     , s_servo [a_joint].leg_name,
         s_servo [a_joint].seg_name, a_joint                   ,
         s_servo [a_joint].servo   );
   printf   ("%4d  %4d  %4d  %4d  %4d  %4d  %4d\n",
         a_angle                   ,
         s_servo [a_joint].min     , s_servo [a_joint].max     ,
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
   /*---(send command)-------------------*/
   snprintf (buf, 1000, "#%d P%d T%d\r", a_joint, a_angle, a_msec);
   printf ("%s\n", buf);
   write  (a_port, buf, strlen(buf));
   usleep (a_msec * 1000);
   /*---(complete)-----------------------*/
   return 0;
}

int
main_new           (int argc, char *argv[])
{
   int       rc        = 0;       /* generic return code                      */
   x_port = COMM_open ("/dev/ttyUSB0");
   /*> move_joint  (x_port, 0, 1500, 2000);                                           <* 
    *> move_joint  (x_port, 1, 1900, 2000);                                           <* 
    *> move_joint  (x_port, 2, 1560, 2000);                                           <* 
    *> move_joint  (x_port, 3, 1000, 2000);                                           <* 
    *> move_joint  (x_port, 4, 1570, 2000);                                           <* 
    *> move_joint  (x_port, 5, 1100, 2000);                                           <*/

   move_joint  (x_port,  0, 1900, 2000);
   move_joint  (x_port,  1, 1900, 2000);
   move_joint  (x_port,  2, 1900, 2000);
   /*---(move base)----------------------*/
   /*> move_joint  (x_port, 0,  600, 1000);                                           <* 
    *> move_joint  (x_port, 0, 2400, 2000);                                           <* 
    *> move_joint  (x_port, 0, 1500, 1000);                                           <*/
   /*> move_joint  (x_port, 0, 1000,  500);                                           <* 
    *> move_joint  (x_port, 0, 1500,  500);                                           <* 
    *> move_joint  (x_port, 0, 1000,  500);                                           <* 
    *> move_joint  (x_port, 0, 1500,  500);                                           <* 
    *> move_joint  (x_port, 0, 2000,  500);                                           <* 
    *> move_joint  (x_port, 0, 1500,  500);                                           <* 
    *> move_joint  (x_port, 1, 1500,  500);                                           <* 
    *> move_joint  (x_port, 1, 1800,  500);                                           <* 
    *> move_joint  (x_port, 1, 1500,  500);                                           <* 
    *> move_joint  (x_port, 1, 1200,  500);                                           <* 
    *> move_joint  (x_port, 1, 1500,  500);                                           <*/
   COMM_close (x_port);
}

char
pose_attn          (void)
{
   int       i         = 0;       /* loop iterator                            */
   for (i = -1; i < MAX_SERVO; ++i) {
      pos_joint   (x_port, i, 1500);
   }
   return 0;
}

char
pose_leg           (int a_servo, int a_femu, int a_pate, int a_tibi)
{
   int       i         = 0;       /* loop iterator                            */
   for (i = a_servo; i <= a_servo + 2; ++i) {
      switch (i % 4) {
      case 0 : pos_joint   (x_port, i, a_femu);
               break;
      case 1 : pos_joint   (x_port, i, a_pate);
               break;
      case 2 : pos_joint   (x_port, i, a_tibi);
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
   pos_joint (x_port, -1, 0);
   for (i = -1; i < MAX_SERVO; ++i) {
      switch (i % 4) {
      case 0 : pos_joint   (x_port, i, a_femu);
               break;
      case 1 : pos_joint   (x_port, i, a_pate);
               break;
      case 2 : pos_joint   (x_port, i, a_tibi);
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
   for (i = -1; i < MAX_SERVO; ++i) {
      switch (i % 4) {
      case 0 : pos_joint   (x_port, i, 1500);
               break;
      case 1 : pos_joint   (x_port, i, 1875);
               break;
      case 2 : pos_joint   (x_port, i, 1000);
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

   /*> hex_move (x_port, LR, 2000, 2100, 1900,  a_time);                              <* 
    *> hex_move (x_port, RR, 2000, 2100, 1900,  a_time);                              <* 
    *> hex_move (x_port, LM, 1500, 2100, 1900,  a_time);                              <* 
    *> hex_move (x_port, RM, 1500, 2100, 1900,  a_time);                              <* 
    *> hex_move (x_port, LF, 1000, 2100, 1900,  a_time);                              <* 
    *> hex_move (x_port, RF, 1000, 2100, 1900,  a_time);                              <*/
   return 0;
}


char
test_exact_table   (void)
{
   int       i         = 0;       /* loop iterator                            */
   int       a_msec    =  500;
   /*> for (i = -1; i < MAX_SERVO; ++i) {                                             <* 
    *>    switch (i % 4) {                                                            <* 
    *>    case 0 : pos_joint   (x_port, i, 1500);                                     <* 
    *>             break;                                                             <* 
    *>    case 1 : pos_joint   (x_port, i, 1900);                                     <* 
    *>             break;                                                             <* 
    *>    case 2 : pos_joint   (x_port, i, 1100);                                     <* 
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
   pos_joint   (x_port, 0, 1500);
   pos_joint   (x_port, 1, 1500);
   pos_joint   (x_port, 2, 1300);
   /*---(#1)-----------------------------*/
   pos_joint   (x_port, 4, 1500);
   pos_joint   (x_port, 5, 1525);
   pos_joint   (x_port, 6, 1425);
   /*---(#2)-----------------------------*/
   pos_joint   (x_port, 8, 1500);
   pos_joint   (x_port, 9, 1550);
   pos_joint   (x_port,10, 1550);
   /*---(#5)-----------------------------*/
   pos_joint   (x_port,16, 1500);
   pos_joint   (x_port,17, 1500);
   pos_joint   (x_port,18, 1300);
   /*---(#4)-----------------------------*/
   pos_joint   (x_port,20, 1500);
   pos_joint   (x_port,21, 1725);
   pos_joint   (x_port,22, 1750);
   /*---(#3)-----------------------------*/
   pos_joint   (x_port,24, 1500);
   pos_joint   (x_port,25, 1625);
   pos_joint   (x_port,26, 1500);
   /*---(complete)-----------------------*/
   return 0;
}

int
main     (int argc, char *argv[])
{
   int       rc        = 0;       /* generic return code                      */
   int       i         = 0;
   char      buf[500]  = "";
   char     *a         = NULL;
   x_port = COMM_open ("/dev/usb/ttyUSB0");
   hex_align_table  (x_port);
   if (argc == 1) {
      printf ("nothing requested, so just aligned joints\n");
      return 0;
   }
   a = argv [1];
   if      (strcmp (a, "--attn"        ) == 0)   pose_fixed     ( 1500, 1500, 1500);
   else if (strcmp (a, "--fmin"        ) == 0)   pose_fixed     (  700, 1500, 1500);
   else if (strcmp (a, "--fmax"        ) == 0)   pose_fixed     ( 2300, 1500, 1500);
   else if (strcmp (a, "--pmin"        ) == 0)   pose_fixed     ( 1500,  600, 1500);
   else if (strcmp (a, "--pmax"        ) == 0)   pose_fixed     ( 1500, 1875, 1000);
   else if (strcmp (a, "--tmin"        ) == 0)   pose_fixed     ( 1500, 1500,  750);
   else if (strcmp (a, "--t10"         ) == 0)   pose_fixed     ( 1500, 1500,  900);
   else if (strcmp (a, "--t20"         ) == 0)   pose_fixed     ( 1500, 1500, 1050);
   else if (strcmp (a, "--t30"         ) == 0)   pose_fixed     ( 1500, 1500, 1200);
   else if (strcmp (a, "--t40"         ) == 0)   pose_fixed     ( 1500, 1500, 1350);
   else if (strcmp (a, "--tmax"        ) == 0)   pose_fixed     ( 1500, 1500, 1800);
   else if (strcmp (a, "--bulldog"     ) == 0)   bulldog        ();
   else if (strcmp (a, "--bulldog_low" ) == 0)   bulldog_low    (x_port);
   /*> test_exact_table ();                                                           <*/
   /*> test_attention ();                                                             <*/
   /*> usleep  (1000000);                                                             <*/
   /*> test_original ();                                                              <*/
   /*> test_all_joints    ();                                                         <*/
   /*> bulldog_low   (1000);                                                          <*/
   /*> usleep  (1000000);                                                             <*/
   /*> bulldog       ( 300);                                                          <*/
   /*> usleep  (1000000);                                                             <*/
   /*> manta_ray     ();                                                              <*/
   /*> i = 16;                                                                        <* 
    *> pos_joint   (x_port, i, 1500);                                                 <* 
    *> move_joint  (x_port, i, 1200, 1000);                                           <* 
    *> move_joint  (x_port, i, 1900, 1000);                                           <* 
    *> move_joint  (x_port, i, 1500, 1000);                                           <*/
   /*> if (scripter () != 0) {                                                                     <* 
    *>    test_attention();                                                                        <* 
    *>    /+> test_repeater();                                                            <+/      <* 
    *>    /+> test_trig();                                                                <+/      <* 
    *>    /+> test_joints();                                                              <+/      <* 
    *>    /+> test_doreme();                                                                 <+/   <* 
    *> }                                                                                           <*/
   COMM_close (x_port);
   return 0;
}







/*============================----end-of-source---============================*/
