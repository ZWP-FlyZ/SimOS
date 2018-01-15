#ifndef __ASMFUNC_H_
#define __ASMFUNC_H_

#define GLOBAL(name) \
    .global name; \
    name:

#define ENDPROC(name) \
    .type name,@function; \
    .size name,.-name 


#endif
