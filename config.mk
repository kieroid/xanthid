# version of xanthid
VER		= 0.0.1

# compiler type
CC		= gcc

# x11
X11INC 		= /usr/X11R6/include
X11LIB 		= /usr/X11R6/lib

# xinerama
XINERAMALIBS  	= -lXinerama
XINERAMAFLAGS 	= -DXINERAMA

# libfreetype
FREETYPELIBS 	= -lfontconfig -lXft
FREETYPEINC 	= /usr/include/freetype2

INCS = -I${X11INC} -I${FREETYPEINC}
LIBS = -L${X11LIB} -lX11 ${XINERAMALIBS} ${FREETYPELIBS} -lXrender

# compiling flags
CFLAGS   	= -std=c99 -pedantic -Wall -Wno-deprecated-declarations -Os ${INCS} \
	   	-D_DEFAULT_SOURCE -D_BSD_SOURCE -D_XOPEN_SOURCE=700L -DVER=\"${VER}\" \
		${XINERAMAFLAGS}
LDFLAGS		= ${LIBS}

# installation directories
PREFIX		= /usr/local
BINDIR		= $(PREFIX)/bin
