#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
static int BLKSIZE = 1024;
static int CHLEN   = 32;

char intens[] = {'`', '@'};

static void
usage(char *cmd)
{
	dprintf(2, "usage: %s [-w WIDTH] [-b BLOCKSIZE] [pcmfile]\n", cmd);
	exit(-1);
}

static int
norm(int v){
	return (CHLEN + CHLEN * v / 0x7fff) / 2;
}

static void
drawch(int min, int max)
{
	int i, Min, Max;
	Min = norm(min);
	Max = norm(max);
	for (i = 0; i < CHLEN; i++)
		if ((i>=Min)&&(i<=Max)) write(1, &intens[1], 1);
		else write(1, &intens[0], 1);
}

int
main(int argc, char **argv)
{
	char buf[11];
	ulong i, n, l, s;
	int16_t *blk;
	int ch, f, lmin, lmax, rmin,rmax;
	f = 0;
	while ((ch = getopt(argc, argv, "b:w:")) != -1){
		switch (ch){
		case 'b':
			BLKSIZE = atoi(optarg);
			if (BLKSIZE <= 0) BLKSIZE = 1;
			break;
		case 'w':
			CHLEN = atoi(optarg);
			if (CHLEN <= 0) CHLEN = 1;
			break;
		default:
			usage(argv[0]);
		}
	}
	if (argc-optind > 1) usage(argv[0]);
	if (argv[optind] != 0){
		f = open(argv[optind], O_RDONLY);
		if (f == -1) {
			dprintf(2, "Error: can't open %s\n", argv[optind]);
			exit(-1); 
		}
	}
	BLKSIZE = BLKSIZE * 4; /*2 channels x 2 bytes*/
	blk = malloc(BLKSIZE);
	l = 44100*4;
	s = -1;
	while ((n = read(f, blk, BLKSIZE)) > 0){
		lmin = rmin = 0x7fff;
		lmax = rmax = -0x7fff;
		for (i=0; i<BLKSIZE/2; i+=2){
			if (blk[i]   > lmax) lmax = blk[i];
			if (blk[i]   < lmin) lmin = blk[i];
			if (blk[i+1] > rmax) rmax = blk[i+1];
			if (blk[i+1] < rmin) rmin = blk[i+1];
		}
		l += n;
		drawch(lmin, lmax);
		if (l > 44100*4){
			s++;
			l -= 44100*4;
			snprintf(buf, 11,  " %02d:%02d:%02d ",
				(int)(s/3600)%99, (int)(s/60)%60, (int)s%60);
			write(1, buf, 10);
		} else  write(1, "          ", 10);
		drawch(rmin, rmax);
		write(1, "\n", 1);
	}
	return 0;
}
