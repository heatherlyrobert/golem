/*============================----beg-of-source---============================*/

#include "golem.h"
/*> tSERVO      g_servo_data  [YKINE_MAX_SERVO] = {                                                                       <* 
 *>    /+ --leg---  ---seg---- servo  ----desc------  --adj --min -attn --max flip --min -attn --max -min-dir- +/   <* 
 *>    {  YKINE_RR, YKINE_FEMU,  15 , "", "", "", "",     0,  700, 1500, 2300,   1,  -50,    0,   25, "cclock" },   <* 
 *>    {  YKINE_RR, YKINE_PATE,   1 , "", "", "", "",   -25,  600, 1500, 1900,  -1,  -25,  -25,  -25, "up"     },   <* 
 *>    {  YKINE_RR, YKINE_TIBI,   2 , "", "", "", "",  -225,  750, 1500, 1800,   1, -225, -225, -225, "out"    },   <* 
 *>    {  -1      , -1        ,  -1 , "", "", "", "",     0,    0,    0,    0,   1,    0,    0,    0, ""       },   <* 
 *>    {  YKINE_RM, YKINE_FEMU,   4 , "", "", "", "",     0,  700, 1500, 2300,   1,  -25,    0,   75, "cclock" },   <* 
 *>    {  YKINE_RM, YKINE_PATE,   5 , "", "", "", "",    50,  600, 1500, 1900,  -1,   75,   75,   35, "up"     },   <* 
 *>    {  YKINE_RM, YKINE_TIBI,   6 , "", "", "", "",  -150,  750, 1500, 1800,   1, -125, -150, -150, "out"    },   <* 
 *>    {   -1      , -1        , -1 , "", "", "", "",     0,    0,    0,    0,   1,    0,    0,    0, ""       },   <* 
 *>    {  YKINE_RF, YKINE_FEMU,   8 , "", "", "", "",    25,  700, 1500, 2300,   1,   25,   25,  100, "cclock" },   <* 
 *>    {  YKINE_RF, YKINE_PATE,   9 , "", "", "", "",    40,  600, 1500, 1900,  -1,   50,   50,   25, "up"     },   <* 
 *>    {  YKINE_RF, YKINE_TIBI,  10 , "", "", "", "",    75,  750, 1500, 1800,   1,   50,   50,   75, "out"    },   <* 
 *>    {  -1      , -1        ,  -1 , "", "", "", "",     0,    0,    0,    0,   1,    0,    0,    0, ""       },   <* 
 *>    {  -1      , -1        ,  -1 , "", "", "", "",     0,    0,    0,    0,   1,    0,    0,    0, ""       },   <* 
 *>    {  -1      , -1        ,  -1 , "", "", "", "",     0,    0,    0,    0,   1,    0,    0,    0, ""       },   <* 
 *>    {  -1      , -1        ,  -1 , "", "", "", "",     0,    0,    0,    0,   1,    0,    0,    0, ""       },   <* 
 *>    {  -1      , -1        ,  -1 , "", "", "", "",     0,    0,    0,    0,   1,    0,    0,    0, ""       },   <* 
 *>    {  YKINE_LR, YKINE_FEMU,  16 , "", "", "", "",    50,  700, 1500, 2300,   1,   25,   50,   50, "cclock" },   <* 
 *>    {  YKINE_LR, YKINE_PATE,  17 , "", "", "", "",     0,  600, 1500, 1900,   1,   50,  -25,  -25, "up"     },   <* 
 *>    {  YKINE_LR, YKINE_TIBI,  18 , "", "", "", "",  -175,  750, 1500, 1800,  -1, -225, -175, -175, "out"    },   <* 
 *>    {  -1      , -1        ,  -1 , "", "", "", "",     0,    0,    0,    0,   1,    0,    0,    0, ""       },   <* 
 *>    {  YKINE_LM, YKINE_FEMU,  20 , "", "", "", "",   -50,  700, 1500, 2300,   1,    0,  -50,  -50, "cclock" },   <* 
 *>    {  YKINE_LM, YKINE_PATE,  21 , "", "", "", "",   225,  600, 1500, 1900,   1,  250,  200,  250, "up"     },   <* 
 *>    {  YKINE_LM, YKINE_TIBI,  22 , "", "", "", "",   225,  750, 1500, 1800,  -1,  225,  250,  225, "out"    },   <* 
 *>    {  -1      , -1        ,  -1 , "", "", "", "",     0,    0,    0,    0,   1,    0,    0,    0, ""       },   <* 
 *>    {  YKINE_LF, YKINE_FEMU,  24 , "", "", "", "",     0,  700, 1500, 2300,   1,  -50,    0,    0, "cclock" },   <* 
 *>    {  YKINE_LF, YKINE_PATE,  25 , "", "", "", "",   250,  600, 1500, 1900,   1,  250,  250,  250, "up"     },   <* 
 *>    {  YKINE_LF, YKINE_TIBI,  26 , "", "", "", "",     0,  750, 1500, 1800,  -1,  -25,   25,    0, "out"    },   <* 
 *>    {  -1      , -1        ,  -1 , "", "", "", "",     0,    0,    0,    0,   1,    0,    0,    0, ""       },   <* 
 *>    {  -1      , -1        ,  -1 , "", "", "", "",     0,    0,    0,    0,   1,    0,    0,    0, ""       },   <* 
 *>    {  -1      , -1        ,  -1 , "", "", "", "",     0,    0,    0,    0,   1,    0,    0,    0, ""       },   <* 
 *>    {  -1      , -1        ,  -1 , "", "", "", "",     0,    0,    0,    0,   1,    0,    0,    0, ""       },   <* 
 *>    {  -1      , -1        ,  -1 , "", "", "", "",     0,    0,    0,    0,   1,    0,    0,    0, ""       },   <* 
 *>    /+ --leg---  ---seg---- servo  ----desc------  --adj --min -attn --max flip --min -attn --max -min-dir- +/   <* 
 *> };                                                                                                              <*/

tSERVO      g_servo_data  [YKINE_MAX_SERVO] = {
   /* --leg---  ---seg---- servo  ----desc------ -limits- flip --min -attn --max -min-dir- */
   {  YKINE_RR, YKINE_FEMU,  15 , "", "", "", "", 0, 0, 0,   1,  -50,    0,   25, "cclock" },
   {  YKINE_RR, YKINE_PATE,   1 , "", "", "", "", 0, 0, 0,  -1,  -25,  -25,  -25, "up"     },
   {  YKINE_RR, YKINE_TIBI,   2 , "", "", "", "", 0, 0, 0,   1, -225, -225, -225, "out"    },
   {  -1      , -1        ,  -1 , "", "", "", "", 0, 0, 0,   1,    0,    0,    0, ""       },
   {  YKINE_RM, YKINE_FEMU,   4 , "", "", "", "", 0, 0, 0,   1,  -25,    0,   75, "cclock" },
   {  YKINE_RM, YKINE_PATE,   5 , "", "", "", "", 0, 0, 0,  -1,   75,   75,   35, "up"     },
   {  YKINE_RM, YKINE_TIBI,   6 , "", "", "", "", 0, 0, 0,   1, -125, -150, -150, "out"    },
   {   -1      , -1        , -1 , "", "", "", "", 0, 0, 0,   1,    0,    0,    0, ""       },
   {  YKINE_RF, YKINE_FEMU,   8 , "", "", "", "", 0, 0, 0,   1,   25,   25,  100, "cclock" },
   {  YKINE_RF, YKINE_PATE,   9 , "", "", "", "", 0, 0, 0,  -1,   50,   50,   25, "up"     },
   {  YKINE_RF, YKINE_TIBI,  10 , "", "", "", "", 0, 0, 0,   1,   50,   50,   75, "out"    },
   {  -1      , -1        ,  -1 , "", "", "", "", 0, 0, 0,   1,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 , "", "", "", "", 0, 0, 0,   1,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 , "", "", "", "", 0, 0, 0,   1,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 , "", "", "", "", 0, 0, 0,   1,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 , "", "", "", "", 0, 0, 0,   1,    0,    0,    0, ""       },
   {  YKINE_LR, YKINE_FEMU,  16 , "", "", "", "", 0, 0, 0,   1,   25,   50,   50, "cclock" },
   {  YKINE_LR, YKINE_PATE,  17 , "", "", "", "", 0, 0, 0,   1,   50,  -25,  -25, "up"     },
   {  YKINE_LR, YKINE_TIBI,  18 , "", "", "", "", 0, 0, 0,  -1, -225, -175, -175, "out"    },
   {  -1      , -1        ,  -1 , "", "", "", "", 0, 0, 0,   1,    0,    0,    0, ""       },
   {  YKINE_LM, YKINE_FEMU,  20 , "", "", "", "", 0, 0, 0,   1,    0,  -50,  -50, "cclock" },
   {  YKINE_LM, YKINE_PATE,  21 , "", "", "", "", 0, 0, 0,   1,  250,  200,  250, "up"     },
   {  YKINE_LM, YKINE_TIBI,  22 , "", "", "", "", 0, 0, 0,  -1,  225,  250,  225, "out"    },
   {  -1      , -1        ,  -1 , "", "", "", "", 0, 0, 0,   1,    0,    0,    0, ""       },
   {  YKINE_LF, YKINE_FEMU,  24 , "", "", "", "", 0, 0, 0,   1,  -50,    0,    0, "cclock" },
   {  YKINE_LF, YKINE_PATE,  25 , "", "", "", "", 0, 0, 0,   1,  250,  250,  250, "up"     },
   {  YKINE_LF, YKINE_TIBI,  26 , "", "", "", "", 0, 0, 0,  -1,  -25,   25,    0, "out"    },
   {  -1      , -1        ,  -1 , "", "", "", "", 0, 0, 0,   1,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 , "", "", "", "", 0, 0, 0,   1,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 , "", "", "", "", 0, 0, 0,   1,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 , "", "", "", "", 0, 0, 0,   1,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 , "", "", "", "", 0, 0, 0,   1,    0,    0,    0, ""       },
   /* --leg---  ---seg---- servo  ----desc------ -limits- flip --min -attn --max -min-dir- */
};


char
DATA_init          (void)
{
   int         i           = 0;
   double      x_attn      = 0.0;
   double      x_value     = 0.0;
   for (i = 0; i < YKINE_MAX_SERVO; ++i) {
      if (g_servo_data [i].leg >= 0) {
         strlcpy (g_servo_data [i].leg_name , yKINE_legfull (g_servo_data [i].leg), LEN_LABEL);
         strlcpy (g_servo_data [i].leg_short, yKINE_legcaps (g_servo_data [i].leg), LEN_LABEL);
      }
      if (g_servo_data [i].seg >= 0) {
         strlcpy (g_servo_data [i].seg_name , yKINE_segfull (g_servo_data [i].seg), LEN_LABEL);
         strlcpy (g_servo_data [i].seg_short, yKINE_segfour (g_servo_data [i].seg), LEN_LABEL);
         x_attn                  = yKINE_segattn (g_servo_data [i].seg);
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
      }
   }
   return 0;
}

char
DATA_list          (void)
{
   int         i           = 0;
   printf ("    ----------leg----------  ---------segment---------  -----servo-data-----  -----adjustments------                 \n");
   printf ("##  no  ---desc--------  ab  no  ---desc--------  abbr  sv  min-  attn  max-  flip  min-  attn  max-  ---min-dir-----\n");
   for (i = 0; i < YKINE_MAX_SERVO; ++i) {
      if (g_servo_data [i].leg < 0)  continue;
      printf ("%02d  %02d  %-15s  %-2s  %02d  %-15s  %-4s  %02d  %4d  %4d  %4d  %4d  %4d  %4d  %4d  %-15s\n", i,
            g_servo_data [i].leg      , g_servo_data [i].leg_name , g_servo_data [i].leg_short, 
            g_servo_data [i].seg      , g_servo_data [i].seg_name , g_servo_data [i].seg_short, 
            g_servo_data [i].servo    ,
            g_servo_data [i].min      , g_servo_data [i].attn     , g_servo_data [i].max      ,
            g_servo_data [i].flip     , g_servo_data [i].adj_min  , g_servo_data [i].adj_attn , g_servo_data [i].adj_max  ,
            g_servo_data [i].min_dir  );
   }
   return 0;
}



/*============================----end-of-source---============================*/
