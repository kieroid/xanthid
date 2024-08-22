CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wno-deprecated-declarations -Os -I/usr/X11R6/include -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_XOPEN_SOURCE=700L -DVERSION=\\"6.5\\"
LDFLAGS = -L/usr/X11R6/lib -lX11
TARGET = xanthid
OBJ = xanthid.o
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

$(OBJ): xanthid.c
	$(CC) $(CFLAGS) -c xanthid.c -o $(OBJ)

clean:
	rm -f $(TARGET) $(OBJ)

install: $(TARGET)
	mkdir -p $(BINDIR)
	cp $(TARGET) $(BINDIR)

uninstall:
	rm -f $(BINDIR)/$(TARGET)

.PHONY: all clean install uninstall
