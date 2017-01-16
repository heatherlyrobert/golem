#*============================----beg-of-source---============================*#



#===[[ VARABLES ]]======================================================================================================================================================#

#===(current variables)=================================================================================================================================================#
BASE    = golem
DEBUG   = ${BASE}_debug
UNIT    = ${BASE}_unit
HDIR    = /home/member/p_gvskav/golem.robotics_controller
IDIR    = /usr/local/bin
MNUM    = 1
MDIR    = /usr/share/man/man${MNUM}
MBASE   = ${BASE}.${MNUM}

#===(compilier variables)===============================================================================================================================================#
# must have "-x c" on gcc line so stripped files work with alternate extensions
COMP    = gcc -c -std=gnu89 -x c -g -pg -Wall -Wextra
INCS    = -I/usr/local/include 

#===(linker options)====================================================================================================================================================================================================================================================================================#
#------   (0)-------------- (1)-------------- (2)-------------- (3)-------------- (4)-------------- (5)-------------- (6)-------------- (7)-------------- (8)-------------- (9)-------------- (A)-------------- (B)-------------- (C)-------------- (D)-------------- (E)-------------- (F)--------------
LINK    = gcc
LIBDIR  = -L/usr/local/lib
LIBS    = ${LIBDIR}         -lyKINE           -lyVIKEYS         -lySTR            -lyURG            -lm
LIBD    = ${LIBDIR}         -lyKINE_debug     -lyVIKEYS         -lySTR            -lyURG_debug      -lm               -lyLOG
LIBU    = ${LIBDIR}         -lyKINE_debug     -lyVIKEYS         -lySTR            -lyURG_debug      -lm               -lyLOG            -lyVAR            -lyUNIT

#===(file lists)============================================================================================================================================================================#
#------   (0)-------------- (1)-------------- (2)-------------- (3)-------------- (4)-------------- (5)-------------- (6)-------------- (7)-------------- (8)-------------- (9)-------------- (A)-------------- (B)-------------- (C)-------------- (D)-------------- (5)--------------
HEADS   = ${BASE}.h
OBJS    = ${BASE}_main.os   ${BASE}_prog.os   ${BASE}_keys.os   ${BASE}_data.os   ${BASE}_comm.os   ${BASE}_trans.os
OBJD    = ${BASE}_main.o    ${BASE}_prog.o    ${BASE}_keys.o    ${BASE}_data.o    ${BASE}_comm.o    ${BASE}_trans.o 

#===(make variables)====================================================================================================================================================#
COPY    = cp -f
CLEAN   = rm -f
PRINT   = @printf
STRIP   = @grep -v -e " DEBUG_" -e " yLOG_" 



#===[[ EXECUTABLES ]]===================================================================================================================================================#

all                : ${DEBUG} ${BASE}

# BASE must check OBJD rather than OBJS to compile stripped version correctly 
${BASE}            : ${OBJD}
	${LINK}  -o ${BASE}        ${OBJS}   ${LIBS}

${DEBUG}           : ${OBJD}
	${LINK}  -o ${DEBUG}       ${OBJD}   ${LIBD}



#===[[ OBJECT FILES ]]==================================================================================================================================================#

${BASE}_main.o     : ${HEADS}       ${BASE}_main.c
	${COMP}    ${BASE}_main.c                           ${INC}
	${STRIP}   ${BASE}_main.c      > ${BASE}_main.cs
	${COMP}    ${BASE}_main.cs    -o ${BASE}_main.os    ${INC}

${BASE}_prog.o     : ${HEADS}       ${BASE}_prog.c
	${COMP}    ${BASE}_prog.c                           ${INC}
	${STRIP}   ${BASE}_prog.c      > ${BASE}_prog.cs
	${COMP}    ${BASE}_prog.cs    -o ${BASE}_prog.os    ${INC}

${BASE}_keys.o     : ${HEADS}       ${BASE}_keys.c
	${COMP}    ${BASE}_keys.c                           ${INC}
	${STRIP}   ${BASE}_keys.c      > ${BASE}_keys.cs
	${COMP}    ${BASE}_keys.cs    -o ${BASE}_keys.os    ${INC}

${BASE}_data.o     : ${HEADS}       ${BASE}_data.c
	${COMP}    ${BASE}_data.c                           ${INC}
	${STRIP}   ${BASE}_data.c      > ${BASE}_data.cs
	${COMP}    ${BASE}_data.cs    -o ${BASE}_data.os    ${INC}

${BASE}_comm.o     : ${HEADS}       ${BASE}_comm.c
	${COMP}    ${BASE}_comm.c                           ${INC}
	${STRIP}   ${BASE}_comm.c      > ${BASE}_comm.cs
	${COMP}    ${BASE}_comm.cs    -o ${BASE}_comm.os    ${INC}

${BASE}_trans.o    : ${HEADS}       ${BASE}_trans.c
	${COMP}    ${BASE}_trans.c                          ${INC}
	${STRIP}   ${BASE}_trans.c     > ${BASE}_trans.cs
	${COMP}    ${BASE}_trans.cs   -o ${BASE}_trans.os   ${INC}



#===[[ SCRIPTS ]]=======================================================================================================================================================#

clean              :
	#---(all versions)--------------------#
	${CLEAN} ${BASE}
	${CLEAN} ${DEBUG}
	${CLEAN} ${UNIT}
	#---(object and stripped files)-------#
	${CLEAN} ${BASE}*.o
	${CLEAN} ${BASE}*.cs
	${CLEAN} ${BASE}*.os
	${CLEAN} ${BASE}*.Sc
	${CLEAN} ${BASE}*.So
	#---(created unit code)---------------#
	${CLEAN} ${UNIT}.code
	${CLEAN} ${UNIT}.c
	#---(junk files)----------------------#
	${CLEAN} *~
	${CLEAN} temp*

bigclean           :
	${CLEAN} .*.swp

install            : ${BASE}
	#---(production version)--------------#
	${COPY}   ${BASE}    ${IDIR}/
	chown     root:root  ${IDIR}/${BASE}
	chmod     0755       ${IDIR}/${BASE}
	@sha1sum  ${BASE}
	#---(debug version)-------------------#
	${COPY}  ${DEBUG}    ${IDIR}/
	chown     root:root  ${IDIR}/${DEBUG}
	chmod     0755       ${IDIR}/${DEBUG}
	@sha1sum  ${DEBUG}
	#---(man page)------------------------#
	rm -f       ${MDIR}/${MBASE}.bz2
	cp -f       ${MBASE}  ${MDIR}/
	bzip2       ${MDIR}/${MBASE}
	chmod 0644  ${MDIR}/${MBASE}.bz2

remove             :
	#---(all versions)--------------------#
	${CLEAN}  ${IDIR}/${BASE}
	${CLEAN}  ${IDIR}/${DEBUG}
	#---(documentation)-------------------#
	${CLEAN}  ${MDIR}/${MBASE}.bz2



#*============================----end-of-source---============================*#
