#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include "bop.h"
#include "fop.h"
#define BUFF_LEN 1024

/*
use merfile cover the orifile from start,
the sizeof(merfile) + start  must <= sizeof(orifile)
input arg=[orifile,merfile,start,outputfile]
start is hex number
*/
int main(int argc, char *argv[])
{

	FILE *oriFile, *merFile,*outFile;
	ulong start;
	uchar buff[BUFF_LEN] = { 0 };

	if (argc != 5)
	{
		printf("bad arg size = %d\n", argc);
		printf("input arg=[orifile,merfile,start(hex number),outputfile]\n");
		exit(1);
	}
	start = strnum2long(argv[3]);

	if ((oriFile = fopen(argv[1], "rb")) == NULL)
	{
		printf("open file err:[oriFile=%s]\n", argv[1]);
		exit(1);
	}

	if ((merFile = fopen(argv[2], "rb")) == NULL)
	{
		printf("open file err:[merFile=%s]\n", argv[2]);
		exit(1);
	}

	if (file_size(oriFile) < (file_size(merFile) + start)) 
	{
		printf("file size err: oriFile < merFile + start \n");
		fclose(oriFile);
		fclose(merFile);
		exit(1);
	}
	if ((outFile = fopen(argv[4], "wb")) == NULL)
	{
		printf("open file err:[outFile=%s]\n", argv[4]);
		exit(1);
	}

	ulong start_index = start / BUFF_LEN;
	uint offset = start % BUFF_LEN;
	int rc;
	//before merge
	rc = fread(buff, sizeof(uchar), BUFF_LEN, oriFile);
	for (int i = 0; i < start_index; i++) 
	{
		fwrite(buff, sizeof(uchar), rc, outFile);
		rc = fread(buff, sizeof(uchar), BUFF_LEN, oriFile);
	}
	if (offset>0)
		fwrite(buff, sizeof(uchar), offset, outFile);

	//merge 
	while ((rc = fread(buff, sizeof(uchar), BUFF_LEN, merFile))) 
		fwrite(buff, sizeof(uchar), rc, outFile);
	start_index = ftell(outFile);
	fseek(oriFile,start_index,SEEK_SET);

	//after merge 
	while ((rc = fread(buff, sizeof(uchar), BUFF_LEN, oriFile)))
		fwrite(buff, sizeof(uchar), rc, outFile);

	fclose(oriFile);
	fclose(merFile);
	fclose(outFile);
	return 0;
}



