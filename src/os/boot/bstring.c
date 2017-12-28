
#include "ctypes.h"

// 将char 转换成一个字符串
void __attribute__((section(".inittext")))number(char * str, long num, int base)
{
	char * dig = "0123456789ABCDEF";
	char tmp[40];
	char len = 0,rel=0;
	if (str == NULL || base < 2|| base>16)  return ;
	if (num == 0) tmp[len++] = '0';
	else while (num!=0) 
	{
		rel = (unsigned long)num % (unsigned )base;
		tmp[len++] = dig[rel];
		num = (unsigned long)num / (unsigned )base;
	}
	while (len-- > 0)
		*str++ = tmp[len];
	*str = '\0';
}



