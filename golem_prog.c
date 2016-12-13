/*============================----beg-of-source---============================*/

#include "golem.h"


tDEBUG      debug;
/*> tACCESSOR   my;                                                                   <*/




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

char         /*--: evaluate logger needs early -----------[ leaf   [ ------ ]-*/
PROG_logger        (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;
   char       *a           = NULL;
   char        x_prog      [LEN_STR] = "";
   char        x_log       = '-';
   /*---(default urgents)----------------*/
   PROG_urgsmass  ('-', 'y');   /* turn everything off */
   debug.logger   = -1;
   strlcpy (x_prog, a_argv [0], LEN_STR);
   /*---(test for normal version)--------*/
   if        (strcmp (a_argv[0], "golem"        ) == 0)  return 0;
   /*---(check for urgents)--------------*/
   for (i = 1; i < a_argc; ++i) {
      a = a_argv[i];
      if (a[0] != '@')  continue;
      x_log = 'y';
   }
   if (x_log != 'y')  return 0;
   /*---(startup logging)----------------*/
   debug.tops     = 'y';
   if (strcmp (a_argv [0], "golem_debug"  ) == 0)
      strlcpy (x_prog, "golem"          , LEN_STR);
   debug.logger = yLOG_begin (x_prog, yLOG_SYSTEM    , yLOG_NOISE);
   /*---(log header)------------------*/
   DEBUG_TOPS   yLOG_info     ("purpose" , "translate and transfer scripts to spider robots");
   DEBUG_TOPS   yLOG_info     ("namesake", "simple animated being magically created from inanimate matter");
   DEBUG_TOPS   yLOG_info     ("yKINE"   , yKINE_version   ());
   DEBUG_TOPS   yLOG_info     ("ySTR"    , ySTR_version    ());
   DEBUG_TOPS   yLOG_info     ("yLOG"    , yLOG_version    ());
   /*---(complete)-----------------------*/
   return 0;
}

char       /*----: very first setup ------------------s-----------------------*/
PROG_init          (void)
{
   DEBUG_TOPS   yLOG_enter (__FUNCTION__);
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit  (__FUNCTION__);
   return 0;
}

char       /*----: process the urgents/debugging -----------------------------*/
PROG_urgsmass      (char a_set, char a_extra)
{
   /*---(overall)------------------------*/
   debug.tops     = a_set;
   debug.summ     = a_set;
   /*---(startup/shutdown)---------------*/
   debug.args     = a_set;
   debug.conf     = a_set;
   debug.prog     = a_set;
   /*---(file processing)----------------*/
   debug.inpt     = a_set;
   debug.inpt_mas = a_set;
   debug.outp     = a_set;
   debug.outp_mas = a_set;
   /*---(event handling)-----------------*/
   debug.loop     = a_set;
   debug.user     = a_set;
   debug.user_mas = a_set;
   debug.apis     = a_set;
   debug.sign     = a_set;
   debug.scrp     = a_set;
   debug.hist     = a_set;
   /*---(program)------------------------*/
   debug.graf     = a_set;
   debug.graf_mas = a_set;
   debug.data     = a_set;
   debug.data_mas = a_set;
   debug.envi     = a_set;
   /*---(specific)-----------------------*/
   if (a_extra == 'y') {
      ;;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char       /*----: process the urgents/debugging -----------------------------*/
PROG_urgs          (int argc, char *argv[])
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;
   char       *a           = NULL;
   int         x_total     = 0;
   int         x_urgs      = 0;
   /*---(process)------------------------*/
   DEBUG_TOPS  yLOG_enter (__FUNCTION__);
   for (i = 1; i < argc; ++i) {
      a = argv[i];
      ++x_total;
      if (a[0] != '@')  continue;
      DEBUG_ARGS  yLOG_info  ("urgent", a);
      ++x_urgs;
      /*---(debugging)-------------------*/
      /* this is my latest standard format, vars, and urgents                 */
      /* v3.0b : added signal handling                          (2014-feb-01) */
      /*---(overall)---------------------*/
      if      (strncmp(a, "@t"      ,10) == 0)    debug.tops = 'y';
      else if (strncmp(a, "@@top"   ,10) == 0)    debug.tops = 'y';
      else if (strncmp(a, "@s"      ,10) == 0)    debug.tops = debug.summ  = 'y';
      else if (strncmp(a, "@@summ"  ,10) == 0)    debug.tops = debug.summ  = 'y';
      /*---(startup/shutdown)------------*/
      else if (strncmp(a, "@a"      ,10) == 0)    debug.tops = debug.args  = 'y';
      else if (strncmp(a, "@@args"  ,10) == 0)    debug.tops = debug.args  = 'y';
      else if (strncmp(a, "@c"      ,10) == 0)    debug.tops = debug.conf  = 'y';
      else if (strncmp(a, "@@conf"  ,10) == 0)    debug.tops = debug.conf  = 'y';
      else if (strncmp(a, "@p"      ,10) == 0)    debug.tops = debug.prog  = 'y';
      else if (strncmp(a, "@@prog"  ,10) == 0)    debug.tops = debug.prog  = 'y';
      /*---(text files)------------------*/
      else if (strncmp(a, "@i"      ,10) == 0)    debug.tops = debug.inpt  = 'y';
      else if (strncmp(a, "@@inpt"  ,10) == 0)    debug.tops = debug.inpt  = 'y';
      else if (strncmp(a, "@o"      ,10) == 0)    debug.tops = debug.outp  = 'y';
      else if (strncmp(a, "@@outp"  ,10) == 0)    debug.tops = debug.outp  = 'y';
      /*---(processing)------------------*/
      else if (strncmp(a, "@l"      ,10) == 0)    debug.tops = debug.loop  = 'y';
      else if (strncmp(a, "@@loop"  ,10) == 0)    debug.tops = debug.loop  = 'y';
      else if (strncmp(a, "@u"      ,10) == 0)    debug.tops = debug.user  = 'y';
      else if (strncmp(a, "@@user"  ,10) == 0)    debug.tops = debug.user  = 'y';
      else if (strncmp(a, "@i"      ,10) == 0)    debug.tops = debug.apis  = 'y';
      else if (strncmp(a, "@@apis"  ,10) == 0)    debug.tops = debug.apis  = 'y';
      else if (strncmp(a, "@x"      ,10) == 0)    debug.tops = debug.sign  = 'y';
      else if (strncmp(a, "@@sign"  ,10) == 0)    debug.tops = debug.sign  = 'y';
      else if (strncmp(a, "@b"      ,10) == 0)    debug.tops = debug.scrp  = 'y';
      else if (strncmp(a, "@@scrp"  ,10) == 0)    debug.tops = debug.scrp  = 'y';
      else if (strncmp(a, "@h"      ,10) == 0)    debug.tops = debug.hist  = 'y';
      else if (strncmp(a, "@@hist"  ,10) == 0)    debug.tops = debug.hist  = 'y';
      /*---(program)---------------------*/
      else if (strncmp(a, "@g"      ,10) == 0)    debug.tops = debug.graf  = 'y';
      else if (strncmp(a, "@@graf"  ,10) == 0)    debug.tops = debug.graf  = 'y';
      else if (strncmp(a, "@d"      ,10) == 0)    debug.tops = debug.data  = 'y';
      else if (strncmp(a, "@@data"  ,10) == 0)    debug.tops = debug.data  = 'y';
      else if (strncmp(a, "@e"      ,10) == 0)    debug.tops = debug.envi  = 'y';
      else if (strncmp(a, "@@envi"  ,10) == 0)    debug.tops = debug.envi  = 'y';
      /*---(big options)-----------------*/
      else if (strncmp(a, "@q"        ,10) == 0)  PROG_urgsmass ('-', 'y');
      else if (strncmp(a, "@@quiet"   ,10) == 0)  PROG_urgsmass ('-', 'y');
      else if (strncmp(a, "@f"        ,10) == 0)  PROG_urgsmass ('y', '-');
      else if (strncmp(a, "@@full"    ,10) == 0)  PROG_urgsmass ('y', '-');
      else if (strncmp(a, "@k"        ,10) == 0)  PROG_urgsmass ('y', 'y');
      else if (strncmp(a, "@@kitchen" ,10) == 0)  PROG_urgsmass ('y', 'y');
      /*---(special)---------------------*/
      /*---(done)------------------------*/
   }
   DEBUG_ARGS  yLOG_note   ("summarization of urgent processing");
   DEBUG_ARGS  yLOG_value  ("entries"    , x_total);
   DEBUG_ARGS  yLOG_value  ("urgents"    , x_urgs);
   DEBUG_ARGS  yLOG_char   ("@t,@@tops"  , debug.tops);
   DEBUG_ARGS  yLOG_char   ("@s,@@summ"  , debug.summ);
   DEBUG_ARGS  yLOG_char   ("@a,@@args"  , debug.args);
   DEBUG_ARGS  yLOG_char   ("@c,@@conf"  , debug.conf);
   DEBUG_ARGS  yLOG_char   ("@p,@@prog"  , debug.prog);
   DEBUG_ARGS  yLOG_char   ("@i,@@inpt"  , debug.inpt);
   DEBUG_ARGS  yLOG_char   ("@I,@@INPT"  , debug.inpt_mas);
   DEBUG_ARGS  yLOG_char   ("@o,@@outp"  , debug.outp);
   DEBUG_ARGS  yLOG_char   ("@O,@@OUTP"  , debug.outp_mas);
   DEBUG_ARGS  yLOG_char   ("@l,@@loop"  , debug.loop);
   DEBUG_ARGS  yLOG_char   ("@u,@@user"  , debug.user);
   DEBUG_ARGS  yLOG_char   ("@U,@@USER"  , debug.user_mas);
   DEBUG_ARGS  yLOG_char   ("@i,@@apis"  , debug.apis);
   DEBUG_ARGS  yLOG_char   ("@x,@@sign"  , debug.sign);
   DEBUG_ARGS  yLOG_char   ("@b,@@scrp"  , debug.scrp);
   DEBUG_ARGS  yLOG_char   ("@h,@@hist"  , debug.hist);
   DEBUG_ARGS  yLOG_char   ("@g,@@graf"  , debug.graf);
   DEBUG_ARGS  yLOG_char   ("@G,@@GRAF"  , debug.graf_mas);
   DEBUG_ARGS  yLOG_char   ("@d,@@data"  , debug.data);
   DEBUG_ARGS  yLOG_char   ("@D,@@DATA"  , debug.data_mas);
   DEBUG_ARGS  yLOG_char   ("@e,@@envi"  , debug.envi);
   /*---(complete)-----------------------*/
   DEBUG_TOPS  yLOG_exit  (__FUNCTION__);
   return 0;
}

char               /* PURPOSE : process the command line arguments            */
PROG_args          (int argc, char *argv[])
{
   DEBUG_ARGS  yLOG_enter   (__FUNCTION__);
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
