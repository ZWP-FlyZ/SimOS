#include "boot.h"

void __stack_chk_fail(){
    _puts("stack_chk_fail ERROR!!!");
    die();
}