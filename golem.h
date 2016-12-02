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
#define     VER_NUM   "0.5d"
#define     VER_TXT   "moved servo data table to golem_data.c"



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
extern tSERVO      g_servo_data  [MAX_SERVO];



#endif



/*============================----beg-of-source---============================*/
