# xanthid

include config.mk

TARGET = xanthid
SRC = xanthid.c
OBJ = ${SRC:.c=.o}

all: xanthid

${OBJ}: config.mk

xanthid: $(OBJ)
	${CC} ${CFLAGS} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f $(TARGET) $(OBJ)

xephyr: all
	Xephyr -br -ac -noreset -screen 1024x768 :1 &
	sleep 2
	DISPLAY=:1 ./xanthid &
	DISPLAY=:1 xterm

install: $(TARGET)
	mkdir -p $(BINDIR)
	cp $(TARGET) $(BINDIR)

uninstall:
	rm -f $(BINDIR)/$(TARGET)

.PHONY: all clean install uninstall xephyr
