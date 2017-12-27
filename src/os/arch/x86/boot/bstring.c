
#include "ctypes.h"
#include "bstring.h"

// 将char 转换成一个字符串
s8 num2str(u8 num,s8 *str){
    s8 len=0,tmp=0,i=0,k=100;
    if(str == NULL) return -1;
    for(i=0;i<=2;i++,k/=10){
        if(!(tmp = num/k))
            str[len++] = tmp+'0';
        num=num%k;
    }
    if(len==0)  str[len++] = '0';
    str[len]='\0';
    return len;
}



