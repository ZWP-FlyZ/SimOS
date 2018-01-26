
#include "asmfunc.h"

    .code16gcc
    
GLOBAL(protect_model_jump)
    movl %ecx,%eax # 转移code32_start地址
    
    # 计算切换32位后指令地址
    xorl %ebx,%ebx  
    movw %cs,%bx
    shll $4,%ebx
    




