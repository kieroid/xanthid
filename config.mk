# version of xanthid
VER	= 0.0.1

# compiler type
CC	= gcc

# compiling flags
CFLAGS	= -std=c99 -pedantic -Wall -Wno-deprecated-declarations \
	-Os -I/usr/X11R6/include -D_DEFAULT_SOURCE -D_BSD_SOURCE \
	-D_XOPEN_SOURCE=700L -DVER=\"${VER}\"
LDFLAGS	= -L/usr/X11R6/lib -lX11

# installation directories
PREFIX	= /usr/local
BINDIR	= $(PREFIX)/bin
