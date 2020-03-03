	.file	"matrix.c"
	.text
	.p2align 4,,15
	.globl	newMatrix
	.type	newMatrix, @function
newMatrix:
.LFB41:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movslq	%edi, %rdi
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %rbp
	salq	$3, %rdi
	movl	%esi, %ebx
	call	malloc@PLT
	testq	%rax, %rax
	movq	%rax, %r12
	je	.L1
	movl	%ebp, %edi
	imull	%ebx, %edi
	movslq	%edi, %rdi
	salq	$2, %rdi
	call	malloc@PLT
	testq	%rax, %rax
	je	.L3
	testl	%ebp, %ebp
	jle	.L1
	leal	-1(%rbp), %ecx
	movslq	%ebx, %rsi
	movq	%r12, %rdx
	salq	$2, %rsi
	leaq	8(%r12,%rcx,8), %rcx
	.p2align 4,,10
	.p2align 3
.L5:
	movq	%rax, (%rdx)
	addq	$8, %rdx
	addq	%rsi, %rax
	cmpq	%rcx, %rdx
	jne	.L5
.L1:
	movq	%r12, %rax
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L3:
	.cfi_restore_state
	movq	%r12, %rdi
	xorl	%r12d, %r12d
	call	free@PLT
	jmp	.L1
	.cfi_endproc
.LFE41:
	.size	newMatrix, .-newMatrix
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	" %3d"
	.text
	.p2align 4,,15
	.globl	printMatrix
	.type	printMatrix, @function
printMatrix:
.LFB42:
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
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$8, %rsp
	.cfi_def_cfa_offset 64
	testl	%esi, %esi
	jle	.L13
	leal	-1(%rsi), %eax
	leaq	.LC0(%rip), %rbp
	movl	%edx, %r13d
	movq	%rdi, %r15
	leaq	8(%rdi,%rax,8), %r14
	leal	-1(%rdx), %eax
	leaq	4(,%rax,4), %r12
	.p2align 4,,10
	.p2align 3
.L14:
	xorl	%ebx, %ebx
	testl	%r13d, %r13d
	jle	.L16
	.p2align 4,,10
	.p2align 3
.L15:
	movq	(%r15), %rax
	movq	%rbp, %rsi
	movl	$1, %edi
	movl	(%rax,%rbx), %edx
	xorl	%eax, %eax
	addq	$4, %rbx
	call	__printf_chk@PLT
	cmpq	%rbx, %r12
	jne	.L15
.L16:
	movq	stdout(%rip), %rsi
	movl	$10, %edi
	addq	$8, %r15
	call	_IO_putc@PLT
	cmpq	%r14, %r15
	jne	.L14
.L13:
	movq	stdout(%rip), %rsi
	addq	$8, %rsp
	.cfi_def_cfa_offset 56
	movl	$10, %edi
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
	jmp	_IO_putc@PLT
	.cfi_endproc
.LFE42:
	.size	printMatrix, .-printMatrix
	.p2align 4,,15
	.globl	freeMatrix
	.type	freeMatrix, @function
freeMatrix:
.LFB43:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	movq	(%rdi), %rdi
	call	free@PLT
	movq	%rbx, %rdi
	popq	%rbx
	.cfi_def_cfa_offset 8
	jmp	free@PLT
	.cfi_endproc
.LFE43:
	.size	freeMatrix, .-freeMatrix
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
