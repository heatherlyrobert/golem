#*============================----beg-of-source---============================*#

BASE    = golem


#*---(standard variables)-------------*#
#COMP    = gcc -c -ansi -g -pg -Wall -Wextra
INCS    = -I/usr/local/include
#LINK    = gcc 
LIBS    = -lm
#LIBS    = -lyXINIT -lyFONT -lX11 -lGL -lm
#LIBS_S  = -Wl,-Bstatic  -lyXINIT -lyFONT -Wl,-Bdynamic -lX11 -lGL -lm
COPY    = cp -f
CLEAN   = rm -f
ECHO    = @echo


${BASE}            : ${BASE}.c
	gcc    -o ${BASE}      ${BASE}.c   ${LIBS}

bigclean           :
	${CLEAN} .*.swp

clean              :
	${ECHO}  cleaning out object, backup, and temp files
	${CLEAN} *.o
	${CLEAN} *~
	${CLEAN} temp*
	${CLEAN} ${BASE}

install            : ${BASE}
	${ECHO}  installing in /usr/local/bin
	${COPY}  ${BASE}  /usr/local/bin
	chmod  0755  /usr/local/bin/${BASE}


#*============================----end-of-source---============================*#
