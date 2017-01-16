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
#define     VER_NUM   "0.5j"
#define     VER_TXT   "transitioned to yURG for urgent processing"



/*===[[ library headers -- standard ]]========================================*/
#include    <stdio.h>             /* clibc standard input/output              */
#include    <stdlib.h>            /* clibc standard                           */
#include    <string.h>            /* clibc standard string handling           */
#include    <unistd.h>            /* clibc standard unix interface            */
#include    <error.h>             /* clibc standard error handling            */
#include    <fcntl.h>             /* clibc standard file control              */
#include    <termios.h>           /* clibc standard terminal control          */
#include    <math.h>              /* clibc standard math                      */
#include    <time.h>              /* CLIBC  standard time and date handling   */

/*---(heatherly made)--------------------*/
#include    <yURG.h>         /* CUSTOM  heatherly urgent processing           */
#include    <yKINE.h>        /* CUSTOM heatherly kinematics                   */
#include    <yVIKEYS.h>      /* CUSTOM heatherly vi_keys standard             */
#include    <ySTR.h>         /* CUSTOM heatherly string handling              */
#include    <ySTR.h>         /* CUSTOM heatherly string handling              */
#include    <yLOG.h>         /* CUSTOM heatherly program logging              */



/*===[[ TYPEDEFS ]]===========================================================*/
/*---(basics)--------------------------*/
typedef     unsigned    char        uchar;
typedef     const       char        cchar;
typedef     unsigned    short       ushort;
typedef     const       int         cint;
typedef     unsigned    long        ulong;
typedef     unsigned    long long   ullong;
/*---(library simplifications)---------*/
typedef     struct      FILE        tFILE;
typedef     struct      tm          tTIME;
typedef     struct      timespec    tTSPEC;
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





struct cACCESSOR {
   /*---(progress move)------------------*/
   double      p_waitns;
   /*---(flags)--------------------------*/
   char        noadj;
   /*---(done)---------------------------*/
};
extern      tACCESSOR my;




typedef     struct cSERVO   tSERVO;
struct cSERVO {
   /*---(key info)----------*/
   char        leg;
   char        seg;
   char        servo;
   char        ykine;
   /*---(descriptive)-------*/
   char        leg_name    [LEN_LABEL];
   char        leg_short   [LEN_LABEL];
   char        seg_name    [LEN_LABEL];
   char        seg_short   [LEN_LABEL];
   /*---(setup data)--------*/
   double      zero;
   int         min;
   int         attn;
   int         max;
   /*---(dynamic adj)-------*/
   char        flip;
   int         adj_min;
   int         adj_attn;
   int         adj_max;
   char        type;
   int         adjs       [19];
   /*---(descriptive)-------*/
   char        min_dir    [LEN_LABEL];
   /*---(done)--------------*/
};
extern tSERVO      g_servo_data  [YKINE_MAX_SERVO];

char        DATA_init          (void);
char        DATA_list          (void);
char        DATA_find          (int     a_leg       , int      a_seg       );
char        DATA_adj_table     (void);
int         DATA_adjust        (int     a_servo     , int      a_angle     );




/*---(arachne_main)----------------------*/
int         main               (int argc, char *argv[]);

/*---(arachne_prog)----------------------*/
char        PROG_init          (void);
char        PROG_urgsmass      (char a_set, char a_extra);
char        PROG_urgs          (int argc, char *argv[]);
char        PROG_args          (int argc, char *argv[]);
char        PROG_begin         (void);
char        PROG_end           (void);




#endif



/*============================----beg-of-source---============================*/
