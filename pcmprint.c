#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

#define BLKSIZE 1024 //256
#define CHLEN    32

char *intens[]={".", "0"};

static void
usage(char *cmd)
{
	dprintf(2, "usage: %s [pcmfile]", cmd);
	exit(-1);
}

static int
norm(int v){
	return (CHLEN + CHLEN * v / 0x7fff) / 2;
}

static void
drawch(int min, int max)
{
	int cc, i, Min, Max;
	char *cv;
	Min = norm(min);
	Max = norm(max);
	cv = intens[0];
	cc = strlen(cv);
	for (i = 0;   i < Min;   i++) write(1, cv, cc);
	cv = intens[1];
	cc = strlen(cv);
	for (i = Min; i < Max;   i++) write(1, cv, cc);
	cv = intens[0];
	cc = strlen(cv);
	for (i = Max; i < CHLEN; i++) write(1, cv, cc);;
}

int
main(int argc, char **argv)
{
	ulong i, n;
	int16_t *blk;
	int lmin, lmax, rmin,rmax;
	blk = malloc(BLKSIZE);
	if (argc > 1){
		usage(*argv);
	}
	while ((n = read(0, blk, BLKSIZE)) > 0){
		lmin = rmin = 0x7fff;
		lmax = rmax = -0x7fff;
		for (i=0; i<BLKSIZE/2; i+=2){
			if (blk[i]   > lmax) lmax = blk[i];
			if (blk[i]   < lmin) lmin = blk[i];
			if (blk[i+1] > rmax) rmax = blk[i+1];
			if (blk[i+1] < rmin) rmin = blk[i+1];
		}
		drawch(lmin, lmax);
		write(1, " ", 1);
		drawch(rmin, rmax);
		write(1, "\n", 1);
	}
}
