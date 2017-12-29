
#include "screen_info.h"
#include "boot.h"

void set_video()
{
    struct boot_config_info * bci = &boot_config_info;
    if(bci->screen_info.vmode == VMODE_TEXT_03H)
        println("\n---> video model in defaule text model,ready change to card model");

}
