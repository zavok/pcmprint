#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

#define BLKSIZE 256
#define CHLEN    32

char *intens[]={"░", "▒", "▓", "█"};
//char   *intens[]={" ", ".", "o", "8"};

static void
usage(char *cmd)
{
	dprintf(2, "usage: %s [pcmfile]", cmd);
	exit(-1);
}

static void
chpress(unsigned int *ch, int16_t v)
{
	int n;
	n = (CHLEN + CHLEN * v / 0x7fff) / 2;
	if (n > 31) n--;
	assert(n>=0);
	assert(n<32);
	ch[n]++;
}

static void
writech(unsigned int *ch)
{
	int i;
	for (i=0;  i<CHLEN; i++){
		unsigned int c;
		c = 0;
		if (ch[i] > 0)  c = 1;
		if (ch[i] > 16) c = 2;
		if (ch[i] > 32) c = 3;
		write(1, intens[c], strlen(intens[c]));
	}
}

int
main(int argc, char **argv)
{
	ulong i, n;
	int16_t *blk;
	blk = malloc(BLKSIZE);
	if (argc > 1){
		usage(*argv);
	}
	while ((n = read(0, blk, BLKSIZE)) > 0){
		unsigned int *lch = calloc(sizeof (int), CHLEN);
		unsigned int *rch = calloc(sizeof (int), CHLEN);
		for (i=0; i<BLKSIZE/2; i+=2){
			chpress(lch, blk[i]);
			chpress(rch, blk[i+1]);
		}
		writech(lch);
		write(1, "  ", 2);
		write(1, "  ", 2);
		writech(rch);
		write(1, "\n", 1);
		free(lch);
		free(rch);
	}
}
