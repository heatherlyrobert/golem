/*============================----beg-of-source---============================*/
#include "golem.h"



tSERVO      g_servo_data  [YKINE_MAX_SERVO] = {
   /* --leg---  ---seg---- servo ykine  ----desc------ --limits--- flip --min -attn --max type --06- --07- --08- --09- --10- --11- --12- --13- --14- --15- --16- --17- --18- --19- --20- --21- --22- --23- --24- -min-dir- */
   {  YKINE_RR, YKINE_FEMU,  15 ,  -1 , "", "", "", "", 0, 0, 0, 0,   1,  -50,    0,   25, '3',  -45,  -40,  -35,  -30,  -25,  -20,  -15,  -10,   -5,    0,    2,    5,    7,   10,   12,   15,   18,   20,   22, "cclock" },
   {  YKINE_RR, YKINE_PATE,   1 ,  -1 , "", "", "", "", 0, 0, 0, 0,  -1,  -25,  -25,  -25, '3',    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, "up"     },
   {  YKINE_RR, YKINE_TIBI,   2 ,  -1 , "", "", "", "", 0, 0, 0, 0,   1, -225, -225, -225, '3',    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, "out"    },
   {  -1      , -1        ,  -1 ,  -1 , "", "", "", "", 0, 0, 0, 0,   1,    0,    0,    0, '3',    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, ""       },
   {  YKINE_RM, YKINE_FEMU,   4 ,  -1 , "", "", "", "", 0, 0, 0, 0,   1,  -25,    0,   75, '3',    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, "cclock" },
   {  YKINE_RM, YKINE_PATE,   5 ,  -1 , "", "", "", "", 0, 0, 0, 0,  -1,   75,   75,   35, '3',    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, "up"     },
   {  YKINE_RM, YKINE_TIBI,   6 ,  -1 , "", "", "", "", 0, 0, 0, 0,   1, -125, -150, -150, '3',    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, "out"    },
   {   -1      , -1        , -1 ,  -1 , "", "", "", "", 0, 0, 0, 0,   1,    0,    0,    0, '3',    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, ""       },
   {  YKINE_RF, YKINE_FEMU,   8 ,  -1 , "", "", "", "", 0, 0, 0, 0,   1,   25,   25,  100, '3',    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, "cclock" },
   {  YKINE_RF, YKINE_PATE,   9 ,  -1 , "", "", "", "", 0, 0, 0, 0,  -1,   50,   50,   25, '3',    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, "up"     },
   {  YKINE_RF, YKINE_TIBI,  10 ,  -1 , "", "", "", "", 0, 0, 0, 0,   1,   50,   50,   75, '3',    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, "out"    },
   {  -1      , -1        ,  -1 ,  -1 , "", "", "", "", 0, 0, 0, 0,   1,    0,    0,    0, '3',    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 ,  -1 , "", "", "", "", 0, 0, 0, 0,   1,    0,    0,    0, '3',    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 ,  -1 , "", "", "", "", 0, 0, 0, 0,   1,    0,    0,    0, '3',    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 ,  -1 , "", "", "", "", 0, 0, 0, 0,   1,    0,    0,    0, '3',    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 ,  -1 , "", "", "", "", 0, 0, 0, 0,   1,    0,    0,    0, '3',    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, ""       },
   {  YKINE_LR, YKINE_FEMU,  16 ,  -1 , "", "", "", "", 0, 0, 0, 0,   1,   25,   50,   50, '3',    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, "cclock" },
   {  YKINE_LR, YKINE_PATE,  17 ,  -1 , "", "", "", "", 0, 0, 0, 0,   1,   50,  -25,  -25, '3',    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, "up"     },
   {  YKINE_LR, YKINE_TIBI,  18 ,  -1 , "", "", "", "", 0, 0, 0, 0,  -1, -225, -175, -175, '3',    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, "out"    },
   {  -1      , -1        ,  -1 ,  -1 , "", "", "", "", 0, 0, 0, 0,   1,    0,    0,    0, '3',    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, ""       },
   {  YKINE_LM, YKINE_FEMU,  20 ,  -1 , "", "", "", "", 0, 0, 0, 0,   1,    0,  -50,  -50, '3',    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, "cclock" },
   {  YKINE_LM, YKINE_PATE,  21 ,  -1 , "", "", "", "", 0, 0, 0, 0,   1,  250,  200,  250, '3',    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, "up"     },
   {  YKINE_LM, YKINE_TIBI,  22 ,  -1 , "", "", "", "", 0, 0, 0, 0,  -1,  225,  250,  225, '3',    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, "out"    },
   {  -1      , -1        ,  -1 ,  -1 , "", "", "", "", 0, 0, 0, 0,   1,    0,    0,    0, '3',    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, ""       },
   {  YKINE_LF, YKINE_FEMU,  24 ,  -1 , "", "", "", "", 0, 0, 0, 0,   1,  -50,    0,    0, '3',    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, "cclock" },
   {  YKINE_LF, YKINE_PATE,  25 ,  -1 , "", "", "", "", 0, 0, 0, 0,   1,  250,  250,  250, '3',    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, "up"     },
   {  YKINE_LF, YKINE_TIBI,  26 ,  -1 , "", "", "", "", 0, 0, 0, 0,  -1,  -25,   25,    0, '3',    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, "out"    },
   {  -1      , -1        ,  -1 ,  -1 , "", "", "", "", 0, 0, 0, 0,   1,    0,    0,    0, '3',    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 ,  -1 , "", "", "", "", 0, 0, 0, 0,   1,    0,    0,    0, '3',    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 ,  -1 , "", "", "", "", 0, 0, 0, 0,   1,    0,    0,    0, '3',    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 ,  -1 , "", "", "", "", 0, 0, 0, 0,   1,    0,    0,    0, '3',    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 ,  -1 , "", "", "", "", 0, 0, 0, 0,   1,    0,    0,    0, '3',    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, ""       },
   /* --leg---  ---seg---- servo ykine  ----desc------ --limits--- flip --min -attn --max type --06- --07- --08- --09- --10- --11- --12- --13- --14- --15- --16- --17- --18- --19- --20- --21- --22- --23- --24- -min-dir- */
};


char
DATA_init          (void)
{
   int         i           = 0;
   double      x_attn      = 0.0;
   double      x_value     = 0.0;
   char        x_name      [LEN_LABEL];
   for (i = 0; i < YKINE_MAX_SERVO; ++i) {
      if (g_servo_data [i].leg >= 0) {
         strlcpy (g_servo_data [i].leg_name , yKINE_legfull (g_servo_data [i].leg), LEN_LABEL);
         strlcpy (g_servo_data [i].leg_short, yKINE_legcaps (g_servo_data [i].leg), LEN_LABEL);
      }
      if (g_servo_data [i].seg >= 0) {
         strlcpy (g_servo_data [i].seg_name , yKINE_segfull (g_servo_data [i].seg), LEN_LABEL);
         strlcpy (g_servo_data [i].seg_short, yKINE_segfour (g_servo_data [i].seg), LEN_LABEL);
         x_attn                  = yKINE_segattn (g_servo_data [i].seg);
         g_servo_data [i].zero   = x_attn;
         g_servo_data [i].attn   = 1500;
         x_value                 = x_attn - yKINE_segmin  (g_servo_data [i].seg);
         x_value                *= 10.0;
         g_servo_data [i].min    = 1500 - x_value;
         /*> printf ("x_attn=%8.1lf, min=%8.1lf, x_attn-min=%8.1lf, x10=%8.1lf, MIN=%4d\n",                       <* 
          *>       x_attn, yKINE_segmin  (g_servo_data [i].seg), x_attn - yKINE_segmin  (g_servo_data [i].seg),   <* 
          *>       x_value, g_servo_data [i].min);                                                                <*/
         x_value                 = yKINE_segmax  (g_servo_data [i].seg) - x_attn;
         x_value                *= 10.0;
         g_servo_data [i].max    = 1500 + x_value;
         /*> printf ("x_attn=%8.1lf, max=%8.1lf, max-x_attn=%8.1lf, x10=%8.1lf, MAX=%4d\n",                       <* 
          *>       x_attn, yKINE_segmax  (g_servo_data [i].seg), yKINE_segmax  (g_servo_data [i].seg) - x_attn,   <* 
          *>       x_value, g_servo_data [i].max);                                                                <*/
         sprintf (x_name, "%s.%s", g_servo_data [i].leg_short, g_servo_data [i].seg_short);
         /*> printf  ("%2d %s\n", i, x_name);                                         <*/
         g_servo_data [i].ykine = yKINE_servo (x_name);
      }
   }
   return 0;
}

char
DATA_list          (void)
{
   int         i           = 0;
   printf ("    ----------leg----------  ---------segment---------  ----------servo-data----------  -----adjustments------                 \n");
   printf ("##  no  ---desc--------  ab  no  ---desc--------  abbr  sv  yk  zero  min-  attn  max-  flip  min-  attn  max-  ---min-dir-----\n");
   for (i = 0; i < YKINE_MAX_SERVO; ++i) {
      if (g_servo_data [i].leg < 0)  continue;
      printf ("%02d  %02d  %-15s  %-2s  %02d  %-15s  %-4s  %02d  %02d  %4.1lf  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %-15s\n", i,
            g_servo_data [i].leg      , g_servo_data [i].leg_name , g_servo_data [i].leg_short, 
            g_servo_data [i].seg      , g_servo_data [i].seg_name , g_servo_data [i].seg_short, 
            g_servo_data [i].servo    , g_servo_data [i].ykine    , g_servo_data [i].zero     ,
            g_servo_data [i].min      , g_servo_data [i].attn     , g_servo_data [i].max      ,
            g_servo_data [i].flip     , g_servo_data [i].adj_min  , g_servo_data [i].adj_attn , g_servo_data [i].adj_max  ,
            g_servo_data [i].min_dir  );
   }
   return 0;
}

char
DATA_find          (int a_leg, int a_seg)
{
   int         i           = 0;
   for (i = 0; i < YKINE_MAX_SERVO; ++i) {
      if (g_servo_data [i].leg < 0)       continue;
      if (g_servo_data [i].leg != a_leg)  continue;
      if (g_servo_data [i].seg != a_seg)  continue;
      return i;
   }
   return -1;
}

int
DATA_adjust_OLD    (int a_servo, int a_angle)
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
   /*---(defenses)-----------------------*/
   if (my.noadj == 'y') {
      return 0;
   }
   DEBUG_TOPS   yLOG_enter (__FUNCTION__);
   /*---(prepare)------------------------*/
   DEBUG_ADJS   yLOG_value   ("a_servo"    , a_servo);
   DEBUG_ADJS   yLOG_value   ("a_angle"    , a_angle);
   i      = a_servo;
   DEBUG_ADJS   yLOG_info    ("leg"        , g_servo_data [i].leg_name);
   DEBUG_ADJS   yLOG_info    ("segment"    , g_servo_data [i].seg_name);
   x_min  = g_servo_data [i].min;
   x_attn = g_servo_data [i].attn;
   x_max  = g_servo_data [i].max;
   DEBUG_ADJS   yLOG_value   ("x_min"      , x_min);
   DEBUG_ADJS   yLOG_value   ("x_attn"     , x_attn);
   DEBUG_ADJS   yLOG_value   ("x_max"      , x_max);
   /*> printf ("adj_m  = %4d, adj_a  = %4d, adj_x  = %4d\n", g_servo_data[i].adj_min, g_servo_data[i].adj_attn, g_servo_data[i].adj_max);   <*/
   /*---(figure)-------------------------*/
   if (a_angle == x_attn) {
      /*> printf ("EQUAL to attention\n");                                            <*/
      /*> printf ("middle,                      so attn = %4d\n", g_servo_data [i].adj_attn);   <*/
      return g_servo_data [i].adj_attn;
   }
   if (a_angle <= x_attn) {
      /*> printf ("LESSER than attention\n");                                         <*/
      x_range = (x_attn - x_min);
      x_qtr   = x_range / 4.0;
      if (a_angle <= x_min  + x_qtr) {
         /*> printf ("smallest qtr of bottom (1/8), so min  = %4d\n", g_servo_data [i].adj_min);   <*/
         return g_servo_data [i].adj_min;
      }
      if (a_angle >= x_attn - x_qtr) {
         /*> printf ("largest qtr of bottom (4/8),  so attn = %4d\n", g_servo_data [i].adj_attn);   <*/
         return g_servo_data [i].adj_attn;
      }
      x_diff  = g_servo_data [i].adj_attn - g_servo_data [i].adj_min;
      x_start = a_angle - x_min - x_qtr;
      x_pct   = x_start / (2.0 * x_qtr);
      /*> printf ("x_range= %4d, x_qtr  = %4d, x_diff = %4d, x_start= %4d, x_pct  = %5.3f\n", x_range, x_qtr, x_diff, x_start, x_pct);   <*/
      /*> printf ("middle half of bottom (2-3/8), so = %4d\n", g_servo_data [i].adj_min  + (int) (x_pct * x_diff));   <*/
      return g_servo_data [i].adj_min + (int) (x_pct * x_diff);
   } else {
      /*> printf ("GREATER than attention\n");                                        <*/
      x_range = (x_max  - x_attn);
      x_qtr   = x_range / 4.0;
      if (a_angle >= x_max  - x_qtr) {
         /*> printf ("largest qtr of top    (8/8), so max  = %4d\n", g_servo_data [i].adj_max);   <*/
         return g_servo_data [i].adj_max;
      }
      if (a_angle <= x_attn + x_qtr) {
         /*> printf ("smallest qtr of top   (5/8), so attn = %4d\n", g_servo_data [i].adj_attn);   <*/
         return g_servo_data [i].adj_attn;
      }
      x_diff  = g_servo_data [i].adj_max  - g_servo_data [i].adj_attn;
      x_start = a_angle - x_attn + x_qtr;
      x_pct   = x_start / (2.0 * x_qtr);
      /*> printf ("x_range= %4d, x_qtr  = %4d, x_diff = %4d, x_start= %4d, x_pct  = %5.3f\n", x_range, x_qtr, x_diff, x_start, x_pct);   <*/
      /*> printf ("middle half of top    (6-7/8), so = %4d\n", g_servo_data [i].adj_attn + (int) (x_pct * x_diff));   <*/
      return g_servo_data [i].adj_min + (int) (x_pct * x_diff);
   }
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit  (__FUNCTION__);
   return 0;
}

int
DATA_adjust        (int a_servo, int a_angle)
{
   /*---(locals)-------------------------*/
   int       i           =  0;
   int       x_1st       =  0;
   int       x_2nd       =  0;
   int       x_min       =  0;
   int       x_max       =  0;
   int       x_range     =  0;
   float     x_pct       =  0;
   int       x_diff      =  0;
   int       x_final     =  0;
   /*---(defenses)-----------------------*/
   i      = a_servo;
   /*---(fast path)----------------------*/
   if (a_angle <= g_servo_data [i].min) {
      return g_servo_data [i].adj_min;
   }
   if (a_angle >= g_servo_data [i].max) {
      return g_servo_data [i].adj_max;
   }
   /*---(set endpoints)------------------*/
   if      (a_angle <= g_servo_data [i].attn) {
      x_1st   = g_servo_data [i].min;
      x_2nd   = g_servo_data [i].attn;
      x_min   = g_servo_data [i].adj_min;
      x_max   = g_servo_data [i].adj_attn;
   }
   else if (a_angle >  g_servo_data [i].attn) {
      x_1st   = g_servo_data [i].attn;
      x_2nd   = g_servo_data [i].max;
      x_min   = g_servo_data [i].adj_attn;
      x_max   = g_servo_data [i].adj_max;
   }
   /*---(if equal)-----------------------*/
   if (x_min == x_max) {
      return x_min;
   }
   /*---(always)-------------------------*/
   x_range = (x_2nd - x_1st);
   x_pct   = ((float) (a_angle - x_1st)) / ((float) x_range);
   /*---(slope upwards)------------------*/
   if (x_min <  x_max) {
      x_diff  = x_max - x_min;
      x_final = x_min + (x_diff * x_pct);
      return x_final;
   }
   /*---(slope downwards)----------------*/
   if (x_min >  x_max) {
      x_diff  = x_min - x_max;
      x_final = x_min - (x_diff * x_pct);
      return x_final;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char         /*--> provide audit of adjustments ----------[ ------ [ ------ ]-*/
DATA_adj_table         (void)
{
   int         i           =  0;
   int         j           =  0;
   int         x_adj       =  0;
   int         x_min       =  0;
   int         x_attn      =  0;
   int         x_max       =  0;
   printf ("\n\nSERVO ADJUSTMENT TABLE FOR MIN-ATTN-MAX METHOD\n");
   printf ("sv  --min  -attn  --max  ---6-  ---7-  ---8-  ---9-  --10-  --11-  --12-  --13-  --14-  --15-  --16-  --17-  --18-  --19-  --20-  --21-  --22-  --23-  --24-\n");
   for (i = 0; i < YKINE_MAX_SERVO; ++i) {
      if (g_servo_data [i].leg < 0)  continue;
      printf ("%2d  ", i);
      x_min  = g_servo_data [i].min;
      x_attn = g_servo_data [i].attn;
      x_max  = g_servo_data [i].max;
      printf ("%5d  %5d  %5d  ", x_min, x_attn, x_max);
      for (j = 600; j <= 2400; j += 100) {
         if (j < x_min) {
            printf ("%5d  ", g_servo_data [i].adj_min);
            continue;
         }
         if (j > x_max) {
            printf ("%5d  ", g_servo_data [i].adj_max);
            continue;
         }
         x_adj = DATA_adjust  (i, j);
         printf ("%5d  ", x_adj);
      }
      printf ("\n");
   }
   return 0;
}

char         /*--> provide audit of adjustments ----------[ ------ [ ------ ]-*/
DATA_adj_audit         (int  a_servo)
{
}



/*============================----end-of-source---============================*/
