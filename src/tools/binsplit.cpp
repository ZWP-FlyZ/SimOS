#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include "bop.h"
#define BUFF_LEN 1024
#define READ_END_FLAG 0

int main(int argc, char *argv[])
{
/*
	char *cs[] = {
		"ttt",
		"E:/FlyzOS/test/gcctest/myasm.img",
		"0",
		"0x200",
		"E:/FlyzOS/test/gcctest/myasm.to"
	};
	argv = cs;
	argc = 5;
*/
	FILE *inFile, *outFile;
	unsigned long start = 0, end = 0, tail_index = BUFF_LEN;
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
		printf("start end err  = (start = %d,end = %d)\n", start, end);
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
	while (end == READ_END_FLAG ||
		end >= tail_index - BUFF_LEN) {//read next
		rc = fread(buff, sizeof(unsigned  char), BUFF_LEN, inFile);

		if (rc == 0) break;//end read
		if (start >= tail_index) {
			tail_index += BUFF_LEN;
			continue;//
		}
		ch = start - tail_index - BUFF_LEN;
		ch = ch < 0 ? 0 : ch;
		if (end == READ_END_FLAG)
		{
			ct = rc - ch;
		}
		else
		{
			ct = end - tail_index;
			ct = ct < 0 ? ct : 0;
			if (rc < BUFF_LEN)
				ct = rc - ch;
			else
				ct += BUFF_LEN - ch;
		}

		fwrite((buff + ch), sizeof(unsigned  char), ct, outFile);
		tail_index += BUFF_LEN;
	}
	printf("split finished! outfile=%s \n", argv[4]);
	fclose(inFile);
	fclose(outFile);
}














