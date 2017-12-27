	.file	"bstring.c"
	.code16gcc
	.section .rdata,"dr"
LC0:
	.ascii "0123456789ABCDEF\0"
	.section	.inittext,"x"
	.globl	_number
	.def	_number;	.scl	2;	.type	32;	.endef
_number:
LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$32, %esp
	movl	$LC0, -8(%ebp)
	movb	$0, -1(%ebp)
	movb	$0, -9(%ebp)
	cmpl	$0, 8(%ebp)
	je	L11
	cmpl	$9, 16(%ebp)
	jle	L11
	cmpl	$16, 16(%ebp)
	jg	L11
	cmpl	$0, 12(%ebp)
	jne	L7
	movzbl	-1(%ebp), %eax
	movl	%eax, %edx
	addl	$1, %edx
	movb	%dl, -1(%ebp)
	movsbl	%al, %eax
	movb	$48, -21(%ebp,%eax)
	jmp	L9
L8:
	movl	12(%ebp), %eax
	movl	16(%ebp), %ecx
	movl	$0, %edx
	divl	%ecx
	movl	%edx, %eax
	movb	%al, -9(%ebp)
	movzbl	-1(%ebp), %eax
	movl	%eax, %edx
	addl	$1, %edx
	movb	%dl, -1(%ebp)
	movsbl	%al, %eax
	movsbl	-9(%ebp), %ecx
	movl	-8(%ebp), %edx
	addl	%ecx, %edx
	movzbl	(%edx), %edx
	movb	%dl, -21(%ebp,%eax)
	movl	12(%ebp), %eax
	movl	16(%ebp), %ecx
	movl	$0, %edx
	divl	%ecx
	movl	%eax, 12(%ebp)
L7:
	cmpl	$0, 12(%ebp)
	jne	L8
	jmp	L9
L10:
	movl	8(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 8(%ebp)
	movsbl	-1(%ebp), %edx
	movzbl	-21(%ebp,%edx), %edx
	movb	%dl, (%eax)
L9:
	movzbl	-1(%ebp), %eax
	movl	%eax, %edx
	subl	$1, %edx
	movb	%dl, -1(%ebp)
	testb	%al, %al
	jg	L10
	movl	8(%ebp), %eax
	movb	$0, (%eax)
	jmp	L1
L11:
	nop
L1:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE0:
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
