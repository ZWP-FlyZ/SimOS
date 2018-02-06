#include "boot.h"

void __stack_chk_fail(){
    println("stack_chk_fail ERROR!!!");
    die();
}

void error_die(){
    println("system error!! go to die ");
    die();
}

