
#include "boot.h"

void __attribute__((section(".inittext")))io_hlt(){
    __asm__ ("hlt"); 
}

void __attribute__((section(".inittext")))io_cli(){
    __asm__ ("cli"); 
}

void __attribute__((section(".inittext")))io_sti(){
    __asm__ ("sti"); 
}


