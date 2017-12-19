#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include "bop.h"
#define BUFF_LEN 1024
#define READ_TO_END_FLAG 0

int main(int argc, char *argv[])
{

	FILE *inFile, *outFile;
	unsigned long long start = 0, end = 0, tail_index = BUFF_LEN;
	unsigned char buff[BUFF_LEN];

	if (argc < 5)
	{
		printf("less arg err = %d\n", argc);
		exit(1);
	}
	start = strnum2long(argv[2]);
	end = strnum2long(argv[3]);
	if (start < 0 || end < 0 || end != 0 && start >= end)
	{
		printf("start end err  = (start = %lld,end = %lld)\n", start, end);
		exit(1);
	}
	inFile = fopen(argv[1], "rb");
	outFile = fopen(argv[4], "wb");
	if (inFile == NULL || outFile == NULL)
	{
		printf("open file err:[inputfile=%s,start=%s,end=%s,outputfile=%s]\n", argv[1], argv[2], argv[3], argv[4]);
		exit(1);
	}

	int rc = 0;
	int ch = 0, ct = 0;
	unsigned long long sta_p, end_p,cont=0;
	sta_p = start / BUFF_LEN;
	end_p = (end-1) / BUFF_LEN;
	while ((rc = fread(buff, sizeof(unsigned  char), 
							 BUFF_LEN, inFile)))
	{
		if (cont < sta_p) { cont++;continue;}
		else if (cont>sta_p) ch = 0;
		else ch = start % BUFF_LEN;//get addr offset
		ct = rc < BUFF_LEN ? rc : BUFF_LEN;
		if (end == READ_TO_END_FLAG)
			ct = ct - ch;
		else if (end_p>cont)
			ct = ct - ch;
		else if (end_p == cont) 
		{
			rc = (end - 1) % BUFF_LEN;
			if (rc >= ct - 1) ct = ct - ch;
			else ct = rc - ch + 1;
			fwrite((buff + ch), sizeof(unsigned  char), ct, outFile);
			break;
		}
		fwrite((buff + ch), sizeof(unsigned  char), ct, outFile);
		cont++;

	}// end while

	printf("split finished! outfile=%s \n", argv[4]);
	fclose(inFile);
	fclose(outFile);
	return 0;
}

