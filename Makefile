pcmprint: pcmprint.c
	gcc pcmprint.c -o pcmprint

install: pcmprint
	cp pcmprint /usr/local/bin/pcmprint

