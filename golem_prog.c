/*============================----beg-of-source---============================*/

#include "golem.h"


tACCESSOR   my;




char      verstring    [500];

char*      /* ---- : return library versioning information -------------------*/
PROG_version       (void)
{
   char    t [20] = "";
#if    __TINYC__ > 0
   strncpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   strncpy (t, "[gnu gcc    ]", 15);
#elif  __CBANG__  > 0
   strncpy (t, "[cbang      ]", 15);
#else
   strncpy (t, "[unknown    ]", 15);
#endif
   snprintf (verstring, 100, "%s   %s : %s", t, VER_NUM, VER_TXT);
   return verstring;
}

char       /*----: very first setup ------------------s-----------------------*/
PROG_init          (void)
{
   /*---(header)-------------------------*/
   DEBUG_TOPS   yLOG_enter (__FUNCTION__);
   /*---(basics)-------------------------*/
   DEBUG_TOPS   yLOG_note  ("load description tables from yKINE");
   DATA_init    ();
   my.noadj     = '-';
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit  (__FUNCTION__);
   return 0;
}

char               /* PURPOSE : process the command line arguments            */
PROG_args          (int argc, char *argv[])
{
   DEBUG_ARGS   yLOG_enter   (__FUNCTION__);
   /*---(locals)-------------------------*/
   int         i           = 0;
   char       *a           = NULL;
   int         x_total     = 0;
   int         x_args      = 0;
   /*---(process)------------------------*/
   for (i = 1; i < argc; ++i) {
      a = argv[i];
      ++x_total;
      if (a[0] == '@')  continue;
      DEBUG_ARGS  yLOG_info    ("cli arg", a);
      ++x_args;
      if      (strcmp(a, "--noadj"      ) == 0)  my.noadj = 'y';
      /*> if      (strcmp(a, "--play"       ) == 0)  yVIKEYS_speed_play   (&my.p_waitns);   <* 
       *> else if (strcmp(a, "--pause"      ) == 0)  yVIKEYS_speed_stop   (&my.p_waitns);   <* 
       *> else if (strcmp(a, "--quit"       ) == 0)  my.p_quit = 'y';                       <* 
       *> else if (strcmp(a, "--RR"         ) == 0)  my.p_leg  = 0.0;                       <* 
       *> else if (strcmp(a, "--RM"         ) == 0)  my.p_leg  = 1.0;                       <* 
       *> else if (strcmp(a, "--RF"         ) == 0)  my.p_leg  = 2.0;                       <* 
       *> else if (strcmp(a, "--LF"         ) == 0)  my.p_leg  = 3.0;                       <* 
       *> else if (strcmp(a, "--LM"         ) == 0)  my.p_leg  = 4.0;                       <* 
       *> else if (strcmp(a, "--LR"         ) == 0)  my.p_leg  = 5.0;                       <* 
       *> else if (strcmp(a, "--dump"       ) == 0)  my.p_dump = 'c';                       <* 
       *> else if (strcmp(a, "--dumpall"    ) == 0)  my.p_dump = 'a';                       <* 
       *> else if (strcmp(a, "--moves_rpt"  ) == 0)  my.report = RPTG_MOVES;                <* 
       *> else if (strcmp(a, "--begsec"     ) == 0) {                                       <* 
       *>    if (i + 1 <  argc)  my.p_cursec = atof (argv[++i]);                            <* 
       *> }                                                                                 <* 
       *> else if (strcmp(a, "--endsec"     ) == 0) {                                       <* 
       *>    if (i + 1 <  argc)  my.p_endsec = atof (argv[++i]);                            <* 
       *> }                                                                                 <* 
       *> else if (strcmp(a, "--scale"      ) == 0) {                                       <* 
       *>    if (i + 1 <  argc) {                                                           <* 
       *>       yVIKEYS_scale_set    (argv[++i], &my.p_inc);                                <* 
       *>    }                                                                              <* 
       *> }                                                                                 <* 
       *> else if (strcmp(a, "--progress"   ) == 0) {                                       <* 
       *>    yVIKEYS_mode_enter  (MODE_PROGRESS);                                           <* 
       *> }                                                                                 <* 
       *> else if (a[0] != '-'                     ) {                                      <* 
       *>    DEBUG_ARGS  yLOG_note   ("found a file name");                                 <* 
       *>    strncpy (my.f_base , a        , LEN_STR);                                      <* 
       *> }                                                                                 <*/
   }
   DEBUG_ARGS  yLOG_value  ("entries"   , x_total);
   DEBUG_ARGS  yLOG_value  ("arguments" , x_args);
   if (x_args == 0) {
      DEBUG_ARGS  yLOG_note   ("no arguments identified");
   }
   /*---(complete)-----------------------*/
   DEBUG_ARGS  yLOG_exit  (__FUNCTION__);
   return 0;
}


char       /*----: drive program setup activities ----------------------------*/
PROG_begin         (void)
{
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return 0;
}


char       /*----: drive the program closure activities ----------------------*/
PROG_end           (void)
{
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   DEBUG_TOPS   yLOG_end     ();
   return 0;
}




/*============================----end-of-source---============================*/
