	.file	"tty.c"
	.code16gcc
	.section	.inittext,"x"
	.globl	_putchar
	.def	_putchar;	.scl	2;	.type	32;	.endef
_putchar:
LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	cmpl	$10, 8(%ebp)
	jne	L2
	movl	$13, (%esp)
	call	_putchar
L2:
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_bios_putchar
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE0:
	.globl	_puts
	.def	_puts;	.scl	2;	.type	32;	.endef
_puts:
LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	nop
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE1:
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
	.def	_bios_putchar;	.scl	2;	.type	32;	.endef
