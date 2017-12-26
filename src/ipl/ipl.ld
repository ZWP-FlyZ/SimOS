
OUTPUT_ARCH(i386)
ENTRY(bootse)

SECTIONS
{
    . = 0;
    .boottext : { *(.boottext) }
}



