
start_addr = 0x8000;

OUTPUT_ARCH(i386)
ENTRY(_Fstart)


SECTIONS
{
    . = 0;
    .headertext :{ *(.headertext) }

    . = 512;
    .header : { *(.header) }
    .entrytext : { *(.entrytext) }
    .inittext : { *(.inittext) }
      /* 初始化结束位置 */    
    _end_init = .;

      /* 代码段位置 */
    .text : { *(.text) } 
      /* 32位代码段位置 */
    .text32 : { *(.text) }

    . = ALIGN(16);
    .rodata		: { *(.rodata*) }

	. = ALIGN(16);
	.data		: { *(.data*) }

    /* 验证符 */
	.signature	: {
		setup_sig = .;
		LONG(0x5a5aaa55)
	}    

	. = ALIGN(16);
	.bss		:
	{
		__bss_start = .;
		*(.bss)
		__bss_end = .;
	}

    /*整个大小*/
	. = ALIGN(16);
	_end = .;



}


