#include "bop.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char inNum(char c) {
	int tmp = -1;
	if (c >= '0'&& c <= '9')
		tmp = c - '0';
	return tmp;
}

char char2num(char c) {
	int tmp = -1;
	if (c >= '0'&& c <= '9')
		tmp = c - '0';
	else if (c >= 'A'&&c <= 'Z')
		tmp = c - 'A'+10;
	else if (c >= 'a'&&c <= 'z')
		tmp = c - 'a'+10;
	return tmp;
}

ulonglong strnum2long(char * str) 
{
	if (str == NULL) return -1;
	char len = strlen(str);
	ulonglong tmp = 0;
	char saves[20];
	char tt = 0;
	saves[19] = 0;//count
	saves[18] = 0;//zero flag
	if (len > 18) 
	{
		printf("err format = %s len >18\n", str);
		return  0x0;
	}

	if (len > 2 && (str[1] == 'x' || str[1] == 'X'))
		tt = 2;

	for (int i = tt; i < len; i++)
	{
		if (saves[18] == 0 && str[i] != '0')
			saves[18] = 1;
		if(saves[18] == 0)
			continue;
				
		if ((tt = char2num(str[i])) < 0)
		{
			printf("err format = %s\n", str);
			exit(-1);
		}
		saves[saves[19]] = tt;
		saves[19]++;
	}
	ulonglong mov = 1;
	while (saves[19]--)
	{
		tmp += saves[saves[19]] * mov;
		mov = mov << 4;
	}
	return tmp;
}


ulong decstr2long(char * str)
{
	if (str == NULL) return -1;
	char len = strlen(str);
	ulonglong tmp = 0;
	char saves[20];
	char tt = 0;
	saves[19] = 0;//count
	saves[18] = 0;//zero flag

	if (len > 10) 
	{
		printf("err format = %s len >10\n", str);
		return  0x0;
	}
	for (int i = 0; i < len; i++)
	{
		if (saves[18] == 0 && str[i] != '0') saves[18] = 1;
		if (saves[18] == 0) continue;
		if ((tt = inNum(str[i])) < 0) break;
		saves[saves[19]] = tt;
		saves[19]++;
		
	}
	ulonglong mov = 1;
	while (saves[19]--)
	{
		tmp += saves[saves[19]] * mov;
		mov = mov * 10;
	}
	return tmp;
}



