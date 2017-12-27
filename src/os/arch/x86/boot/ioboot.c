
#include "boot.h"

void io_hlt(){
    __asm__ ("hlt"); 
}

void io_cli(){
    __asm__ ("cli"); 
}

void io_sti(){
    __asm__ ("sti"); 
}


