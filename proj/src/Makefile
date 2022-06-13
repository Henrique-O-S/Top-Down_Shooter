# name of the program (Minix service)
PROG=proj

.PATH: ${.CURDIR}/project/src
.PATH: ${.CURDIR}/libraries/graphics/src
.PATH: ${.CURDIR}/libraries/kbc/src
.PATH: ${.CURDIR}/libraries/rtc/src
.PATH: ${.CURDIR}/libraries/timer/src
.PATH: ${.CURDIR}/libraries/utils/src

# source code files to be compiled

SRCS = proj.c aux_functions.c game.c elements.c interrupts.c graphics.c kbc.c kbd.c rtc.c utils.c timer.c mouse.c
IPATHS= -I./project/include -I./libraries -I./libraries/graphics/include -I./libraries/kbc/include -I./libraries/timer/include -I./libraries/utils/include -I./media -I./media/player -I./media/enemy -I./media/font -I./media/menu  -I./libraries/rtc/include 

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic ${IPATHS}
CPPFLAGS += -D__LCOM_OPTIMIZED__

# list of library dependencies (for Lab 2, only LCF library)
DPADD += ${LIBLCF}
LDADD += -llcf


# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>