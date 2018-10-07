/*============================----beg-of-source---============================*/
#include "golem.h"



char         /*-> tbd --------------------------------[ ------ [gn.860.371.25]*/ /*-[03.0000.014.!]-*/ /*-[--.---.---.--]-*/
DRAW_main               (void)
{
   int         x_left, x_wide;
   int         x_bott, x_tall;
   int         x, y;
   int         xpos, ypos;
   /*---(display all)--------------------*/
   yVIKEYS_view_size     (YVIKEYS_MAIN, &x_left, &x_wide, &x_bott, &x_tall, NULL);
   for (x = YKINE_FEMU; x <= YKINE_TIBI; x++) {
      xpos = x_left + 25 + (x - YKINE_FEMU) * 10;
      mvprintw (4, xpos, "%8.8s", yKINE_segfour (x));
   }
   for (y = YKINE_RR; y <= YKINE_LR; y++) {
      ypos = 4 + (y * 2);
      mvprintw (ypos, x_left + 2, "%-15.15s %-2.2s", yKINE_legfull (y), yKINE_legcaps (y));
      for (x = YKINE_FEMU; x <= YKINE_TIBI; x++) {
         xpos = x_left + 25 + (x - YKINE_FEMU) * 10;
         mvprintw (ypos, xpos, "%8.2f", 15.65);
      }
   }
   return 0;
}




