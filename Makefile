.POSIX:

PREFIX = /usr/local
MANDIR = $(PREFIX)/share/man/man1

BIN = pcmprint
MAN = $(BIN).1
OBJ = $(BIN:=.o)

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(LIBS) -o $@

$(OBJ):

install: $(BIN)
	mkdir -p $(DESTDIR)$(PREFIX)/bin/
	cp -f $(BIN) $(DESTDIR)$(PREFIX)/bin/
	chmod 555 $(DESTDIR)$(PREFIX)/bin/$(BIN)
	mkdir -p $(DESTDIR)$(MANDIR)
	cp -f $(MAN) $(DESTDIR)$(MANDIR)

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/$(BIN)
	rm -f $(DESTDIR)$(MANDIR)/$(MAN)

clean:
	rm -f $(BIN) $(OBJ)

.c.o:
	$(CC) $(CFLAGS) -c $<
