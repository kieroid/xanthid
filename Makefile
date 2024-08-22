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

install: $(TARGET)
	mkdir -p $(BINDIR)
	cp $(TARGET) $(BINDIR)

uninstall:
	rm -f $(BINDIR)/$(TARGET)

.PHONY: all clean install uninstall
