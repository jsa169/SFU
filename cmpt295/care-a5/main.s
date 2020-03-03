	.file	"main.c"
	.text
	.p2align 4,,15
	.globl	comparator
	.type	comparator, @function
comparator:
.LFB42:
	.cfi_startproc
	movss	(%rdi), %xmm1
	movss	(%rsi), %xmm0
	ucomiss	%xmm1, %xmm0
	ja	.L3
	xorl	%eax, %eax
	movl	$1, %edx
	ucomiss	%xmm0, %xmm1
	setp	%al
	cmovne	%edx, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L3:
	movl	$-1, %eax
	ret
	.cfi_endproc
.LFE42:
	.size	comparator, .-comparator
	.p2align 4,,15
	.globl	u2f
	.type	u2f, @function
u2f:
.LFB41:
	.cfi_startproc
	movl	%edi, -4(%rsp)
	movss	-4(%rsp), %xmm0
	ret
	.cfi_endproc
.LFE41:
	.size	u2f, .-u2f
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"\n%f\n"
	.text
	.p2align 4,,15
	.globl	printarray
	.type	printarray, @function
printarray:
.LFB43:
	.cfi_startproc
	testl	%esi, %esi
	jle	.L11
	leal	-1(%rsi), %eax
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	leaq	.LC0(%rip), %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %rbx
	leaq	4(%rdi,%rax,4), %r12
	.p2align 4,,10
	.p2align 3
.L8:
	pxor	%xmm0, %xmm0
	movq	%rbp, %rsi
	movl	$1, %edi
	movl	$1, %eax
	addq	$4, %rbx
	cvtss2sd	-4(%rbx), %xmm0
	call	__printf_chk@PLT
	cmpq	%r12, %rbx
	jne	.L8
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L11:
	.cfi_restore 3
	.cfi_restore 6
	.cfi_restore 12
	rep ret
	.cfi_endproc
.LFE43:
	.size	printarray, .-printarray
	.section	.rodata.str1.1
.LC3:
	.string	"Test Case 1:\n"
.LC5:
	.string	"The total before sorting: "
.LC6:
	.string	" The total after sorting: "
.LC7:
	.string	"\nTest Case 2:\n"
.LC9:
	.string	""
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB44:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	leaq	.LC3(%rip), %rdi
	subq	$320, %rsp
	.cfi_def_cfa_offset 336
	leaq	16(%rsp), %rbx
	movq	%fs:40, %rax
	movq	%rax, 312(%rsp)
	xorl	%eax, %eax
	call	puts@PLT
	movss	.LC1(%rip), %xmm0
	leaq	4(%rbx), %rax
	movss	%xmm0, 16(%rsp)
	leaq	96(%rbx), %rdx
	movss	.LC4(%rip), %xmm1
	.p2align 4,,10
	.p2align 3
.L15:
	movss	%xmm1, (%rax)
	addq	$4, %rax
	addss	%xmm1, %xmm0
	cmpq	%rax, %rdx
	jne	.L15
	leaq	.LC5(%rip), %rsi
	movl	$1, %edi
	xorl	%eax, %eax
	movss	%xmm0, 12(%rsp)
	call	__printf_chk@PLT
	movss	12(%rsp), %xmm0
	call	f_printbits@PLT
	movq	stdout(%rip), %rsi
	movl	$10, %edi
	call	_IO_putc@PLT
	leaq	.LC6(%rip), %rsi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	leaq	comparator(%rip), %rcx
	movl	$4, %edx
	movq	%rbx, %rdi
	movl	$24, %esi
	call	qsort@PLT
	movq	%rbx, %rdi
	movl	$24, %esi
	leaq	112(%rsp), %rbx
	call	sum_float@PLT
	call	f_printbits@PLT
	movq	stdout(%rip), %rsi
	movl	$10, %edi
	call	_IO_putc@PLT
	leaq	.LC7(%rip), %rdi
	call	puts@PLT
	movq	%rbx, %rsi
	xorl	%ecx, %ecx
	movl	$2, %r9d
	pxor	%xmm0, %xmm0
	movl	$613566757, %edi
	movsd	.LC8(%rip), %xmm2
	movl	$-1431655765, %r8d
	jmp	.L16
	.p2align 4,,10
	.p2align 3
.L18:
	movl	%ecx, %eax
	xorl	%r9d, %r9d
	mull	%r8d
	shrl	%edx
	leal	(%rdx,%rdx,2), %eax
	cmpl	%eax, %ecx
	sete	%r9b
	addq	$4, %rsi
	addl	$1, %r9d
.L16:
	movl	%ecx, %eax
	pxor	%xmm1, %xmm1
	mull	%edi
	movl	%ecx, %eax
	subl	%edx, %eax
	shrl	%eax
	addl	%eax, %edx
	shrl	$2, %edx
	leal	0(,%rdx,8), %eax
	subl	%edx, %eax
	cmpl	%eax, %ecx
	sete	%al
	addl	$1, %ecx
	movzbl	%al, %eax
	addl	%r9d, %eax
	cmpl	$50, %ecx
	cvtsi2sd	%eax, %xmm1
	mulsd	%xmm2, %xmm1
	cvtsd2ss	%xmm1, %xmm1
	movss	%xmm1, (%rsi)
	addss	%xmm1, %xmm0
	jne	.L18
	leaq	.LC5(%rip), %rsi
	movl	$1, %edi
	xorl	%eax, %eax
	movss	%xmm0, 12(%rsp)
	call	__printf_chk@PLT
	movss	12(%rsp), %xmm0
	call	f_printbits@PLT
	movq	stdout(%rip), %rsi
	movl	$10, %edi
	call	_IO_putc@PLT
	leaq	.LC6(%rip), %rsi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	leaq	comparator(%rip), %rcx
	movl	$4, %edx
	movl	$50, %esi
	movq	%rbx, %rdi
	call	qsort@PLT
	movl	$50, %esi
	movq	%rbx, %rdi
	call	sum_float@PLT
	call	f_printbits@PLT
	movq	stdout(%rip), %rsi
	movl	$10, %edi
	call	_IO_putc@PLT
	leaq	.LC9(%rip), %rdi
	call	puts@PLT
	movq	312(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L23
	addq	$320, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
.L23:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE44:
	.size	main, .-main
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC1:
	.long	1132462079
	.align 4
.LC4:
	.long	1133510655
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC8:
	.long	2576980378
	.long	1069128089
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
