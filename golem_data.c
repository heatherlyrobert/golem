/*============================----beg-of-source---============================*/

#include "golem.h"

tSERVO      g_servo_data  [MAX_SERVO] = {
   /* --leg---  ---seg---- servo  ---legname------  abbr   ---segname-------  -abbr-                                                          */
   {  YKINE_RR, YKINE_FEMU,  15 , "", "", "", "",    0,  700, 1500, 2300,   1,  -50,    0,   25, "cclock" },
   {  YKINE_RR, YKINE_PATE,   1 , "", "", "", "",  -25,  600, 1500, 1900,  -1,  -25,  -25,  -25, "up"     },
   {  YKINE_RR, YKINE_FEMU,   2 , "", "", "", "", -225,  750, 1500, 1800,   1, -225, -225, -225, "out"    },
   {  -1      , -1        ,  -1 , "", "", "", "",    0,    0,    0,    0,   1,    0,    0,    0, ""       },
   {  YKINE_RM, YKINE_FEMU,   4 , "", "", "", "",    0,  700, 1500, 2300,   1,  -25,    0,   75, "cclock" },
   {  YKINE_RM, YKINE_PATE,   5 , "", "", "", "",   50,  600, 1500, 1900,  -1,   75,   75,   35, "up"     },
   {  YKINE_RM, YKINE_FEMU,   6 , "", "", "", "", -150,  750, 1500, 1800,   1, -125, -150, -150, "out"    },
   {   -1      , -1        , -1 , "", "", "", "",    0,    0,    0,    0,   1,    0,    0,    0, ""       },
   {  YKINE_RF, YKINE_FEMU,   8 , "", "", "", "",   25,  700, 1500, 2300,   1,   25,   25,  100, "cclock" },
   {  YKINE_RF, YKINE_PATE,   9 , "", "", "", "",   40,  600, 1500, 1900,  -1,   50,   50,   25, "up"     },
   {  YKINE_RF, YKINE_FEMU,  10 , "", "", "", "",   75,  750, 1500, 1800,   1,   50,   50,   75, "out"    },
   {  -1      , -1        ,  -1 , "", "", "", "",    0,    0,    0,    0,   1,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 , "", "", "", "",    0,    0,    0,    0,   1,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 , "", "", "", "",    0,    0,    0,    0,   1,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 , "", "", "", "",    0,    0,    0,    0,   1,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 , "", "", "", "",    0,    0,    0,    0,   1,    0,    0,    0, ""       },
   {  YKINE_LR, YKINE_FEMU,  16 , "", "", "", "",   50,  700, 1500, 2300,   1,   25,   50,   50, "cclock" },
   {  YKINE_LR, YKINE_PATE,  17 , "", "", "", "",    0,  600, 1500, 1900,   1,   50,  -25,  -25, "up"     },
   {  YKINE_LR, YKINE_FEMU,  18 , "", "", "", "", -175,  750, 1500, 1800,  -1, -225, -175, -175, "out"    },
   {  -1      , -1        ,  -1 , "", "", "", "",    0,    0,    0,    0,   1,    0,    0,    0, ""       },
   {  YKINE_LM, YKINE_FEMU,  20 , "", "", "", "",  -50,  700, 1500, 2300,   1,    0,  -50,  -50, "cclock" },
   {  YKINE_LM, YKINE_PATE,  21 , "", "", "", "",  225,  600, 1500, 1900,   1,  250,  200,  250, "up"     },
   {  YKINE_LM, YKINE_FEMU,  22 , "", "", "", "",  225,  750, 1500, 1800,  -1,  225,  250,  225, "out"    },
   {  -1      , -1        ,  -1 , "", "", "", "",    0,    0,    0,    0,   1,    0,    0,    0, ""       },
   {  YKINE_LF, YKINE_FEMU,  24 , "", "", "", "",    0,  700, 1500, 2300,   1,  -50,    0,    0, "cclock" },
   {  YKINE_LF, YKINE_PATE,  25 , "", "", "", "",  250,  600, 1500, 1900,   1,  250,  250,  250, "up"     },
   {  YKINE_LF, YKINE_FEMU,  26 , "", "", "", "",    0,  750, 1500, 1800,  -1,  -25,   25,    0, "out"    },
   {  -1      , -1        ,  -1 , "", "", "", "",    0,    0,    0,    0,   1,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 , "", "", "", "",    0,    0,    0,    0,   1,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 , "", "", "", "",    0,    0,    0,    0,   1,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 , "", "", "", "",    0,    0,    0,    0,   1,    0,    0,    0, ""       },
   {  -1      , -1        ,  -1 , "", "", "", "",    0,    0,    0,    0,   1,    0,    0,    0, ""       },
};


char
DATA_init          (void)
{
   int         i           = 0;
   for (i = 0; i < MAX_SERVO; ++i) {
      if (g_servo_data [i].leg >= 0) {
         strlcpy (g_servo_data [i].leg_name , yKINE_legfull (g_servo_data [i].leg), LEN_LABEL);
         strlcpy (g_servo_data [i].leg_short, yKINE_legcaps (g_servo_data [i].leg), LEN_LABEL);
      }
      if (g_servo_data [i].seg >= 0) {
         strlcpy (g_servo_data [i].seg_name , yKINE_segfull (g_servo_data [i].seg), LEN_LABEL);
         strlcpy (g_servo_data [i].seg_short, yKINE_segfour (g_servo_data [i].seg), LEN_LABEL);
      }
   }
   return 0;
}

char
DATA_list          (void)
{
   int         i           = 0;
   printf ("##  lg  ---desc--------  ab  sg  ---desc--------  abbr  sv\n");
   for (i = 0; i < MAX_SERVO; ++i) {
      printf ("%02d  %02d  %-15s  %-2s  %02d  %-15s  %-4s  %02d\n", i,
            g_servo_data [i].leg      , g_servo_data [i].leg_name , g_servo_data [i].leg_short, 
            g_servo_data [i].seg      , g_servo_data [i].seg_name , g_servo_data [i].seg_short, 
            g_servo_data [i].servo    );
   }
   return 0;
}



/*============================----end-of-source---============================*/
