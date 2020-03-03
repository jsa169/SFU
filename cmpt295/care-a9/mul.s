	.file	"mul.c"
	.text
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"Incompatible multiplication: %d x %d times a %d x %d\n"
	.text
	.p2align 4,,15
	.globl	mul
	.type	mul, @function
mul:
.LFB41:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movl	%r9d, %r13d
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movl	%edx, %r12d
	movl	%esi, %ebx
	subq	$24, %rsp
	.cfi_def_cfa_offset 80
	cmpl	%r8d, %edx
	jne	.L25
	movq	%rdi, %rbp
	movl	%r9d, %esi
	movl	%ebx, %edi
	movq	%rcx, %r15
	call	newMatrix@PLT
	testq	%rax, %rax
	movq	%rax, %r14
	je	.L1
	movl	%r13d, %esi
	movl	%r12d, %edi
	call	newMatrix@PLT
	testl	%r12d, %r12d
	jle	.L4
	leal	-1(%r12), %edx
	leal	-1(%r13), %r9d
	xorl	%ecx, %ecx
	leaq	4(,%rdx,4), %r10
	addq	$1, %r9
	.p2align 4,,10
	.p2align 3
.L5:
	testl	%r13d, %r13d
	jle	.L8
	movq	(%r15,%rcx,2), %r8
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L6:
	movl	(%r8,%rdx,4), %edi
	movq	(%rax,%rdx,8), %rsi
	addq	$1, %rdx
	cmpq	%rdx, %r9
	movl	%edi, (%rsi,%rcx)
	jne	.L6
.L8:
	addq	$4, %rcx
	cmpq	%rcx, %r10
	jne	.L5
.L4:
	testl	%ebx, %ebx
	jle	.L1
	leal	-1(%rbx), %ecx
	leal	-1(%r13), %r15d
	movq	%r14, %rdx
	movq	%r14, 8(%rsp)
	movq	%rbp, %rdi
	leaq	8(%rbp,%rcx,8), %rsi
	leal	-1(%r12), %ecx
	addq	$1, %r15
	leaq	4(,%rcx,4), %rbx
	movq	%rsi, %r14
	.p2align 4,,10
	.p2align 3
.L9:
	testl	%r13d, %r13d
	jle	.L11
	movq	(%rdx), %rbp
	xorl	%r11d, %r11d
	.p2align 4,,10
	.p2align 3
.L14:
	xorl	%r8d, %r8d
	testl	%r12d, %r12d
	jle	.L13
	movq	(%rdi), %r10
	movq	(%rax,%r11,8), %r9
	xorl	%ecx, %ecx
	xorl	%r8d, %r8d
	.p2align 4,,10
	.p2align 3
.L10:
	movl	(%r10,%rcx), %esi
	imull	(%r9,%rcx), %esi
	addq	$4, %rcx
	addl	%esi, %r8d
	cmpq	%rcx, %rbx
	jne	.L10
.L13:
	movl	%r8d, 0(%rbp,%r11,4)
	addq	$1, %r11
	cmpq	%r11, %r15
	jne	.L14
.L11:
	addq	$8, %rdi
	addq	$8, %rdx
	cmpq	%r14, %rdi
	jne	.L9
	movq	8(%rsp), %r14
.L1:
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movq	%r14, %rax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L25:
	.cfi_restore_state
	movl	%edx, %ecx
	movl	%esi, %edx
	leaq	.LC0(%rip), %rsi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	orl	$-1, %edi
	call	exit@PLT
	.cfi_endproc
.LFE41:
	.size	mul, .-mul
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
