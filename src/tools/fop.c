#include "fop.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

long file_size(FILE * fp)
{
	long cur_pos = 0;
	long size = 0;
	if (fp == NULL) return -1;
	cur_pos = ftell(fp);
	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);
	fseek(fp, cur_pos, SEEK_SET);
	return size;
}

