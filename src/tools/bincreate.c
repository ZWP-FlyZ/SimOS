#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include "bop.h"
#define BUFF_LEN 1024

#define MAX_BLOCKSIZE 4096
#define MAX_BLOCKNUM 1048576
#define MAX_SILE 4294967296
/*
	input arg=[outputfile,blocksize,blocknum]
	blocksize unit Btye (1-4096)
	blocknum (1-1M)=(1-1048576)
	max size 4G 
*/
int main(int argc, char *argv[])
{

	FILE *outFile;
	ulong blocksize = 0, blocknum = 0;
	uchar buff[BUFF_LEN] = {0};

	if (argc != 4)
	{
		printf("bad arg size = %d\n", argc);
		exit(1);
	}
	blocksize = decstr2long(argv[2]);
	blocknum = decstr2long(argv[3]);
	if ((outFile = fopen(argv[1], "wb")) == NULL)
	{
		printf("open file err:[outputfile=%s]\n", argv[1]);
		exit(1);
	}
	if(blocksize<1|| blocksize>MAX_BLOCKSIZE)
	{
		printf("blocksize err not in range (1-4096):[blocksize=%ld]\n", blocksize);
		exit(1);
	}
	if (blocknum<1 || blocknum>MAX_BLOCKNUM)
	{
		printf("blocknum err not in range (1-1048576):[blocknum=%ld]\n", blocknum);
		exit(1);
	}
	ulonglong all = blocksize * blocknum;
	ulonglong repeat = all / BUFF_LEN;
	uint offset = all % BUFF_LEN;
	
	for (int i = 0; i < repeat;i++)
		fwrite(buff , sizeof(uchar), BUFF_LEN, outFile);
	if(offset>0)
		fwrite(buff, sizeof(uchar), offset, outFile);
	fclose(outFile);
	return 0;
}
