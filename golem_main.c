/*============================----beg-of-source---============================*/
#include "golem.h"



int          /*-> tbd --------------------------------[ ------ [gn.842.232.99]*/ /*-[01.0000.000.!]-*/ /*-[--.---.---.--]-*/
main (int argc, char *argv[])
{
   /*---(locals)-----------+-----------+-*/
   char        rc          = 0;
   /*---(initialize)---------------------*/
   if (rc >= 0)  rc = yURG_logger  (argc, argv);
   if (rc >= 0)  rc = yURG_urgs    (argc, argv);
   if (rc >= 0)  rc = PROG_init    (argc, argv);
   if (rc >= 0)  rc = PROG_args    (argc, argv);
   if (rc >= 0)  rc = PROG_begin   ();
   if (rc >= 0)  rc = PROG_final   ();
   if (rc <  0) {
      rc = PROG_end ();
      return -1;
   }
   pose_leg ( 0, 2000,  900, 1900);
   pose_leg (16, 1000,  900, 1900);
   pose_leg ( 4, 1500,  900, 1900);
   pose_leg (20, 1500,  900, 1900);
   pose_leg ( 8, 1000,  900, 1900);
   pose_leg (24, 2000,  900, 1900);
   /*---(main-loop)----------------------*/
   rc = yVIKEYS_main  ("keys", "every", NULL);
   /*---(wrap-up)------------------------*/
   rc = PROG_end     ();
   /*---(complete)-----------------------*/
   return 0;
}



/*============================----end-of-source---============================*/
