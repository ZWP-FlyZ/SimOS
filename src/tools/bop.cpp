#include "bop.h"
#include<stdio.h>
#include<stack>
using namespace std;

int char2int(char c) {
	int tmp = -1;
	if (c >= '0'&& c <= '9')
		tmp = c - '0';
	else if (c >= 'A'&&c <= 'Z')
		tmp = c - 'A'+10;
	else if (c >= 'a'&&c <= 'z')
		tmp = c - 'a'+10;
	return tmp;
}

long strnum2long(char * str) 
{
	if (str == NULL) return -1;
	int len = strlen(str);
	long tmp = 0;
	stack<int> s;
	int tt;
	long long mov = 0;;
	if (len > 2 && (str[1] == 'x' || str[1] == 'X'))//hex in
	{
		for (int i = 2; i < len; i++) 
		{
			if ((tt = char2int(str[i])) < 0) 
			{
				printf("err format = %s\n", str);
				exit(-1);
			}
			s.push(tt);
		}
		mov = 1;
		while (!s.empty()) 
		{
			tmp += s.top()*mov;
			mov *= 16;
			s.pop();
		}
	}
	else
		tmp = atol(str);
	return tmp;
}


