	.file	"main.c"
	.text
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"The product of %u and %u is %u.\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB23:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$1000, %esi
	xorl	%edi, %edi
	call	times@PLT
	leaq	.LC0(%rip), %rsi
	movl	%eax, %r8d
	movl	$1000, %ecx
	xorl	%edx, %edx
	movl	$1, %edi
	xorl	%eax, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	jmp	__printf_chk@PLT
	.cfi_endproc
.LFE23:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
