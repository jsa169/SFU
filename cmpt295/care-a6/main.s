	.file	"main.c"
	.text
	.p2align 4,,15
	.globl	lsearch_1
	.type	lsearch_1, @function
lsearch_1:
.LFB42:
	.cfi_startproc
	testl	%esi, %esi
	movl	$-1, %eax
	jle	.L1
	cmpl	(%rdi), %edx
	je	.L6
	subl	$1, %esi
	movl	$1, %ecx
	addq	$1, %rsi
	jmp	.L3
	.p2align 4,,10
	.p2align 3
.L4:
	addq	$1, %rcx
	cmpl	%edx, -4(%rdi,%rcx,4)
	je	.L1
.L3:
	cmpq	%rsi, %rcx
	movl	%ecx, %eax
	jne	.L4
	movl	$-1, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L6:
	xorl	%eax, %eax
.L1:
	rep ret
	.cfi_endproc
.LFE42:
	.size	lsearch_1, .-lsearch_1
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Initializing array . . ."
.LC1:
	.string	"Array initialized. . ."
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC2:
	.string	"Starting test of function %d . . .\n"
	.section	.rodata.str1.1
.LC3:
	.string	"Error: A[N] not consistent.\n"
	.section	.rodata.str1.8
	.align 8
.LC4:
	.string	"Error: A[N-1] not consistent.\n"
	.align 8
.LC5:
	.string	"It took %ld microseconds to run function %d.\n"
	.section	.rodata.str1.1
.LC6:
	.string	"Totalling work %d . . .\n"
	.section	.rodata.str1.8
	.align 8
.LC7:
	.string	"Error: Results of searches disagree.\n"
	.section	.rodata.str1.1
.LC8:
	.string	"Total misses = %ld, %ld\n"
	.section	.rodata.str1.8
	.align 8
.LC9:
	.string	"Total of positions searched = %ld, %ld\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB41:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	leaq	.LC0(%rip), %rdi
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	leaq	A(%rip), %r14
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movl	$1, %ebp
	leaq	4(%r14), %r12
	movl	$-1431655765, %ebx
	subq	$3576, %rsp
	.cfi_def_cfa_offset 3632
	movq	%fs:40, %rax
	movq	%rax, 3560(%rsp)
	xorl	%eax, %eax
	leaq	lsearch_1(%rip), %rax
	movq	%rax, 336(%rsp)
	movq	lsearch_2@GOTPCREL(%rip), %rax
	movq	%rax, 344(%rsp)
	call	puts@PLT
	xorl	%edi, %edi
	xorl	%eax, %eax
	movl	$0, (%r14)
	call	time@PLT
	movl	%eax, %edi
	call	srand@PLT
	.p2align 4,,10
	.p2align 3
.L9:
	movl	%ebp, %eax
	mull	%ebx
	shrl	%edx
	leal	(%rdx,%rdx,2), %eax
	leal	0(%rbp,%rbp,2), %edx
	cmpl	%eax, %ebp
	sete	%al
	addl	$1, %ebp
	addq	$4, %r12
	movzbl	%al, %eax
	addl	%edx, %eax
	movl	%eax, -4(%r12)
	call	rand@PLT
	movl	%eax, %r13d
	call	rand@PLT
	movslq	%r13d, %rcx
	movl	%r13d, %edx
	imulq	$-2147418109, %rcx, %rcx
	sarl	$31, %edx
	shrq	$32, %rcx
	addl	%r13d, %ecx
	sarl	$14, %ecx
	subl	%edx, %ecx
	movl	%ecx, %edx
	sall	$15, %edx
	subl	%ecx, %edx
	movslq	%eax, %rcx
	imulq	$-2147450879, %rcx, %rcx
	subl	%edx, %r13d
	cltd
	sall	$16, %r13d
	shrq	$32, %rcx
	addl	%eax, %ecx
	sarl	$15, %ecx
	subl	%edx, %ecx
	movl	%ecx, %edx
	sall	$16, %edx
	subl	%ecx, %edx
	subl	%edx, %eax
	orl	%r13d, %eax
	cltd
	idivl	%ebp
	movl	-4(%r12), %eax
	movslq	%edx, %rdx
	movl	(%r14,%rdx,4), %ecx
	movl	%ecx, -4(%r12)
	cmpl	$5000000, %ebp
	movl	%eax, (%r14,%rdx,4)
	jne	.L9
	movl	19999996(%r14), %eax
	leaq	.LC1(%rip), %rdi
	movl	20000000(%r14), %r13d
	leaq	352(%rsp), %r15
	leaq	lsearch_1(%rip), %rbp
	movl	%eax, 40(%rsp)
	movq	%r15, %rbx
	call	puts@PLT
	leaq	48(%rsp), %rax
	movq	$1, 8(%rsp)
	movq	%r15, 24(%rsp)
	movq	%rax, 16(%rsp)
	leaq	192(%rsp), %rax
	movq	%rax, 32(%rsp)
.L15:
	movq	8(%rsp), %rax
	leaq	.LC2(%rip), %rsi
	movl	$1, %edi
	xorl	%r15d, %r15d
	movl	%eax, %edx
	movl	%eax, 44(%rsp)
	xorl	%eax, %eax
	call	__printf_chk@PLT
	movq	16(%rsp), %rsi
	xorl	%edi, %edi
	call	getrusage@PLT
	movl	40(%rsp), %r12d
	jmp	.L13
	.p2align 4,,10
	.p2align 3
.L10:
	cmpl	%r12d, 19999996(%r14)
	jne	.L35
	addq	$1, %r15
	cmpq	$400, %r15
	je	.L36
.L13:
	movl	%r15d, %edx
	movl	$5000000, %esi
	leaq	A(%rip), %rdi
	call	*%rbp
	movl	%eax, (%rbx,%r15,4)
	cmpl	%r13d, 20000000(%r14)
	je	.L10
	leaq	.LC3(%rip), %rdi
	call	perror@PLT
.L8:
	movq	3560(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L37
	addq	$3576, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
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
.L35:
	.cfi_restore_state
	leaq	.LC4(%rip), %rdi
	call	perror@PLT
	jmp	.L8
.L36:
	movq	32(%rsp), %rsi
	xorl	%edi, %edi
	addq	$1600, %rbx
	call	getrusage@PLT
	movq	192(%rsp), %rdx
	subq	48(%rsp), %rdx
	leaq	.LC5(%rip), %rsi
	movl	44(%rsp), %ecx
	xorl	%eax, %eax
	movl	$1, %edi
	imulq	$1000000, %rdx, %rdx
	addq	200(%rsp), %rdx
	subq	56(%rsp), %rdx
	call	__printf_chk@PLT
	cmpq	$2, 8(%rsp)
	jne	.L38
	movq	24(%rsp), %r15
	leaq	.LC6(%rip), %rsi
	movl	$3, %edx
	movl	$1, %edi
	xorl	%eax, %eax
	xorl	%r12d, %r12d
	call	__printf_chk@PLT
	xorl	%ebx, %ebx
	xorl	%edx, %edx
	xorl	%ecx, %ecx
	leaq	1600(%r15), %r8
	xorl	%r10d, %r10d
	xorl	%ebp, %ebp
	xorl	%r13d, %r13d
	xorl	%r11d, %r11d
	jmp	.L16
	.p2align 4,,10
	.p2align 3
.L41:
	movslq	%esi, %rax
	addq	%rax, %rbx
	movl	1600(%r15), %eax
	cmpl	$-1, %eax
	je	.L39
.L33:
	movslq	%eax, %rdi
	addq	%rdi, %rbp
	cmpl	%esi, %eax
	jne	.L40
.L18:
	addq	$4, %r15
	cmpq	%r8, %r15
	je	.L19
.L16:
	movl	(%r15), %esi
	cmpl	$-1, %esi
	jne	.L41
	movl	1600(%r15), %eax
	addq	$1, %r10
	addq	$5000000, %rbx
	movl	$1, %r12d
	cmpl	$-1, %eax
	jne	.L33
.L39:
	addq	$1, %r11
	addq	$5000000, %rbp
	cmpl	%esi, %eax
	movl	$1, %r13d
	je	.L18
.L40:
	leaq	.LC7(%rip), %rdi
	call	perror@PLT
	jmp	.L8
.L19:
	testb	%r13b, %r13b
	leaq	.LC8(%rip), %rsi
	movl	$1, %edi
	cmovne	%r11, %rcx
	testb	%r12b, %r12b
	cmovne	%r10, %rdx
	xorl	%eax, %eax
	call	__printf_chk@PLT
	leaq	.LC9(%rip), %rsi
	movq	%rbp, %rcx
	movq	%rbx, %rdx
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	jmp	.L8
.L38:
	movq	344(%rsp), %rbp
	movq	$2, 8(%rsp)
	jmp	.L15
.L37:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE41:
	.size	main, .-main
	.comm	A,20000000,32
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
