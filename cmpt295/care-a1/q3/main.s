	.file	"main.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"The return value was:  %d.\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB23:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	xorl	%esi, %esi
	leaq	.LC0(%rip), %rbp
	movl	$1, %ebx
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	str(%rip), %rdi
	call	mystery@PLT
	leaq	.LC0(%rip), %rsi
	movl	%eax, %edx
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	.p2align 4,,10
	.p2align 3
.L2:
	movq	str(%rip), %rdi
	movl	%ebx, %esi
	addl	$1, %ebx
	call	mystery@PLT
	movq	%rbp, %rsi
	movl	%eax, %edx
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	cmpl	$18, %ebx
	jne	.L2
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE23:
	.size	main, .-main
	.globl	str
	.section	.rodata.str1.1
.LC1:
	.string	"Reference letter"
	.section	.data.rel.local,"aw",@progbits
	.align 8
	.type	str, @object
	.size	str, 8
str:
	.quad	.LC1
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
