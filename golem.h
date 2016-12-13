/*============================----beg-of-source---============================*/

/*===[[ HEADER ]]=============================================================*

 *   focus         : (RB) robotics
 *   niche         : (co) control
 *   application   : golem       (supernatural, slow, dimwitted animated figure)
 *   purpose       : translate and transfer scripts to the robots
 *
 *   base_system   : gnu/linux   (powerful, ubiquitous, technical, and hackable)
 *   lang_name     : gnu/ansi-c  (right, just, best, universal, and everlasting)
 *   dependencies  : none
 *   size goal     : small (appoximately 1,000 slocL)
 *
 *   author        : the_heatherlys
 *   created       : 2010-10
 *   priorities    : direct, simple, brief, vigorous, and lucid (h.w. fowler)
 *   end goal      : loosely coupled, strict interface, maintainable, portable
 * 
 */
/*===[[ SUMMARY ]]============================================================*

 *   golem is our attempt to seperate robotic control from decision-making by
 *   focusing exclusively on translating stance and movements into instructions
 *   that the robot can unthinkingly execute.
 *
 */
/*===[[ PURPOSE ]]============================================================*

 *   golem is a scriptable application that takes in a stream of stances and
 *   movements while translating them into commands that the robot can
 *   understand.  initially, golem is solely focused on the lynxmotion CHR-3
 *   robotic hexapod with 18 DOF.
 *
 *   golem will focus on...
 *      - taking in script statements on stdin
 *      - translating leg angles into servo positions
 *      - communicating the servor position to the hexapod servo controller
 *
 *    golem will not...
 *       - provide a visual interface or interaction
 *       - allow any editing or changes
 *       - give any particular feedback other than errors
 *
 *
 *
 *
 *
 */
/*============================================================================*/



/*===[[ HEADER GUARD ]]===================================*/
#ifndef GOLEM
#define GOLEM  yes



/* rapidly evolving version number to aid with visual change confirmation     */
#define     VER_NUM   "0.5g"
#define     VER_TXT   "added PROG functions from arachne and stripped to compile"



/*===[[ library headers -- standard ]]========================================*/
#include   <stdio.h>              /* clibc standard input/output              */
#include   <stdlib.h>             /* clibc standard                           */
#include   <string.h>             /* clibc standard string handling           */
#include   <unistd.h>             /* clibc standard unix interface            */
#include   <error.h>              /* clibc standard error handling            */
#include   <fcntl.h>              /* clibc standard file control              */
#include   <termios.h>            /* clibc standard terminal control          */
#include   <math.h>               /* clibc standard math                      */

/*---(heatherly made)--------------------*/
#include    <yKINE.h>             /* CUSTOM heatherly kinematics              */
#include    <yVIKEYS.h>           /* CUSTOM heatherly vi_keys standard        */
#include    <ySTR.h>              /* CUSTOM heatherly string handling         */
#include    <ySTR.h>              /* CUSTOM heatherly string handling         */
#include    <yLOG.h>              /* CUSTOM heatherly program logging         */



/*===[[ TYPEDEFS ]]===========================================================*/
/*---(basics)--------------------------*/
/*---(data structures)-----------------*/
typedef     struct      cDEBUG      tDEBUG;
typedef     struct      cACCESSOR   tACCESSOR;



/*===[[ RATIONAL LIMITS ]]====================================================*/
/*   LEN_ is a length or size of something
 *   MIN_ is a minimum count
 *   DEF_ is a default count
 *   MAX_ is a maximum count
 *
 */
/*---(string length)------------------*/
#define     LEN_RECD    2000
#define     LEN_STR     200
#define     LEN_LABEL   20


/*===[[ DEBUGGING SETUP ]]====================================================*/
/* this is my latest standard format, vars, and urgents                       */
/* v3.0c : added more/mas versions                              (2014-feb-01) */
struct cDEBUG
{
   /*---(handle)-------------------------*/
   int         logger;                 /* log file so that we don't close it  */
   /*---(overall)------------------------*/  /* abcdefghi_kl__opq_stu__x__    */
   /* f = full urgents turns on all standard urgents                          */
   /* k = kitchen sink and turns everything, i mean everything on             */
   /* q = quiet turns all urgents off including the log itself                */
   char        tops;                   /* t) broad structure and context      */
   char        summ;                   /* s) statistics and analytical output */
   /*---(startup/shutdown)---------------*/
   char        args;                   /* a) command line args and urgents    */
   char        conf;                   /* c) configuration handling           */
   char        prog;                   /* p) program setup and teardown       */
   /*---(file processing)----------------*/
   char        inpt;                   /* i) text and data file input         */
   char        inpt_mas;               /* I) text and data file input (more)  */
   char        outp;                   /* o) text and data file output        */
   char        outp_mas;               /* O) text and data file output (more) */
   /*---(event handling)-----------------*/
   char        loop;                   /* l) main program event loop          */
   char        user;                   /* u) user input and handling          */
   char        user_mas;               /* U) user input and handling (more)   */
   char        apis;                   /* i) interprocess communication       */
   char        sign;                   /* x) os signal handling               */
   char        scrp;                   /* b) scripts and batch operations     */
   char        hist;                   /* h) history, undo, redo              */
   /*---(program)------------------------*/
   char        graf;                   /* g) grahpics, drawing, and display   */
   char        graf_mas;               /* G) grahpics, drawing (more)         */
   char        data;                   /* d) complex data structure handling  */
   char        data_mas;               /* D) complex data structure (more)    */
   char        envi;                   /* e) environment processing           */
   /*---(specific)-----------------------*/
   /*---(done)---------------------------*/
};
extern tDEBUG      debug;

/*---(normal)-------------------------*/
#define     DEBUG_TOPS          if (debug.tops      == 'y')
#define     DEBUG_SUMM          if (debug.summ      == 'y')
#define     DEBUG_ARGS          if (debug.args      == 'y')
#define     DEBUG_CONF          if (debug.conf      == 'y')
#define     DEBUG_PROG          if (debug.prog      == 'y')
#define     DEBUG_INPT          if (debug.inpt      == 'y')
#define     DEBUG_OUTP          if (debug.outp      == 'y')
#define     DEBUG_LOOP          if (debug.loop      == 'y')
#define     DEBUG_USER          if (debug.user      == 'y')
#define     DEBUG_APIS          if (debug.apis      == 'y')
#define     DEBUG_SIGN          if (debug.sign      == 'y')
#define     DEBUG_SCRP          if (debug.scrp      == 'y')
#define     DEBUG_HIST          if (debug.hist      == 'y')
#define     DEBUG_GRAF          if (debug.graf      == 'y')
#define     DEBUG_DATA          if (debug.data      == 'y')
#define     DEBUG_ENVI          if (debug.envi      == 'y')
/*---(detailed)-----------------------*/
#define     DEBUG_INPTM         if (debug.inpt_mas  == 'y')
#define     DEBUG_OUTPM         if (debug.outp_mas  == 'y')
#define     DEBUG_USERM         if (debug.user_mas  == 'y')
#define     DEBUG_GRAFM         if (debug.graf_mas  == 'y')
#define     DEBUG_DATAM         if (debug.data_mas  == 'y')





typedef     struct cSERVO   tSERVO;
struct cSERVO {
   /*---(key info)----------*/
   char        leg;
   char        seg;
   char        servo;
   /*---(descriptive)-------*/
   char        leg_name    [LEN_LABEL];
   char        leg_short   [LEN_LABEL];
   char        seg_name    [LEN_LABEL];
   char        seg_short   [LEN_LABEL];
   /*---(setup data)--------*/
   int         min;
   int         attn;
   int         max;
   /*---(dynamic adj)-------*/
   char        flip;
   int         adj_min;
   int         adj_attn;
   int         adj_max;
   /*---(descriptive)-------*/
   char        min_dir    [LEN_LABEL];
   /*---(done)--------------*/
};
extern tSERVO      g_servo_data  [YKINE_MAX_SERVO];

char        DATA_init (void);
char        DATA_list (void);




/*---(arachne_main)----------------------*/
int         main               (int argc, char *argv[]);

/*---(arachne_prog)----------------------*/
char        PROG_logger        (int argc, char *argv[]);
char        PROG_init          (void);
char        PROG_urgsmass      (char a_set, char a_extra);
char        PROG_urgs          (int argc, char *argv[]);
char        PROG_args          (int argc, char *argv[]);
char        PROG_begin         (void);
char        PROG_end           (void);




#endif



/*============================----beg-of-source---============================*/
