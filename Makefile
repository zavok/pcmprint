pcmprint: pcmprint.c
	cc pcmprint.c -o pcmprint

install: pcmprint
	cp pcmprint /usr/local/bin/pcmprint
	cp pcmprint.1 /usr/local/man/man1/pcmprint.1

