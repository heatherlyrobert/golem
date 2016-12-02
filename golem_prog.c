/*============================----beg-of-source---============================*/

#include "golem.h"


/*> tDEBUG      debug;                                                                <* 
 *> tACCESSOR   my;                                                                   <*/




/*> char      verstring    [500];                                                     <*/

/*> char*      /+ ---- : return library versioning information -------------------+/   <* 
 *> PROG_version       (void)                                                          <* 
 *> {                                                                                  <* 
 *>    char    t [20] = "";                                                            <* 
 *> #if    __TINYC__ > 0                                                               <* 
 *>    strncpy (t, "[tcc built  ]", 15);                                               <* 
 *> #elif  __GNUC__  > 0                                                               <* 
 *>    strncpy (t, "[gnu gcc    ]", 15);                                               <* 
 *> #elif  __CBANG__  > 0                                                              <* 
 *>    strncpy (t, "[cbang      ]", 15);                                               <* 
 *> #else                                                                              <* 
 *>    strncpy (t, "[unknown    ]", 15);                                               <* 
 *> #endif                                                                             <* 
 *>    snprintf (verstring, 100, "%s   %s : %s", t, VER_NUM, VER_TXT);                 <* 
 *>    return verstring;                                                               <* 
 *> }                                                                                  <*/




/*============================----end-of-source---============================*/
