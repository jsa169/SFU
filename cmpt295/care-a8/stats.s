	.file	"stats.c"
	.text
	.p2align 4,,15
	.globl	min_max_avg
	.type	min_max_avg, @function
min_max_avg:
.LFB23:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	testl	%edx, %edx
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
	movq	56(%rsp), %rbp
	movq	64(%rsp), %r12
	movq	%r9, -8(%rsp)
	movl	%esi, -28(%rsp)
	movq	%rcx, -24(%rsp)
	movq	%r8, -16(%rsp)
	movq	72(%rsp), %r9
	jle	.L79
	leal	-1(%rdx), %eax
	movss	.LC2(%rip), %xmm4
	movss	.LC3(%rip), %xmm3
	leaq	4(,%rax,4), %rcx
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L3:
	movss	%xmm4, 0(%rbp,%rax)
	movss	%xmm3, (%r12,%rax)
	movl	$0x00000000, (%r9,%rax)
	addq	$4, %rax
	cmpq	%rcx, %rax
	jne	.L3
.L2:
	movl	-28(%rsp), %ebx
	testl	%ebx, %ebx
	jle	.L48
	movq	80(%rsp), %rcx
	leal	-1(%rbx), %r8d
	movq	88(%rsp), %rsi
	movq	96(%rsp), %rax
	pxor	%xmm1, %xmm1
	movq	%r12, %r11
	movq	%rbp, %r10
	leaq	4(%rcx,%r8,4), %rbx
	leal	-3(%rdx), %r8d
	shrl	%r8d
	movq	%rbx, -48(%rsp)
	movl	%r8d, %ebx
	leaq	8(,%rbx,8), %r15
	leal	2(%r8,%r8), %ebx
	movl	%ebx, -36(%rsp)
	leal	-1(%rdx), %ebx
	movl	%ebx, -32(%rsp)
	.p2align 4,,10
	.p2align 3
.L35:
	cmpl	$2, %edx
	movss	%xmm4, (%rcx)
	movss	%xmm3, (%rsi)
	movl	$0x00000000, (%rax)
	jle	.L49
	pxor	%xmm2, %xmm2
	xorl	%r8d, %r8d
	.p2align 4,,10
	.p2align 3
.L22:
	movq	(%rdi), %rbx
	movss	(%rbx,%r8), %xmm0
	movaps	%xmm0, %xmm6
	addss	%xmm0, %xmm1
	minss	(%rcx), %xmm6
	movss	%xmm6, (%rcx)
	movaps	%xmm0, %xmm6
	maxss	(%rsi), %xmm6
	movss	%xmm6, (%rsi)
	movss	(%rax), %xmm6
	addss	%xmm0, %xmm6
	movss	%xmm6, (%rax)
	movaps	%xmm0, %xmm6
	minss	(%r10), %xmm6
	movss	%xmm6, (%r10)
	movaps	%xmm0, %xmm6
	maxss	(%r11), %xmm6
	movss	%xmm6, (%r11)
	addss	(%r9,%r8), %xmm0
	movss	%xmm0, (%r9,%r8)
	movss	4(%rbx,%r8), %xmm0
	movaps	%xmm0, %xmm6
	addss	%xmm0, %xmm2
	minss	(%rcx), %xmm6
	movss	%xmm6, (%rcx)
	movaps	%xmm0, %xmm6
	maxss	(%rsi), %xmm6
	movss	%xmm6, (%rsi)
	movss	(%rax), %xmm6
	addss	%xmm0, %xmm6
	movss	%xmm6, (%rax)
	movss	4(%rbp,%r8), %xmm6
	ucomiss	%xmm0, %xmm6
	jbe	.L18
	movss	%xmm0, 0(%rbp,%r8)
.L18:
	ucomiss	4(%r12,%r8), %xmm0
	jbe	.L20
	movss	%xmm0, 4(%r12,%r8)
.L20:
	addss	4(%r9,%r8), %xmm0
	movss	%xmm0, 4(%r9,%r8)
	addq	$8, %r8
	cmpq	%r15, %r8
	jne	.L22
	movslq	-36(%rsp), %rbx
.L5:
	cmpl	%ebx, %edx
	addss	%xmm2, %xmm1
	jle	.L23
	movl	-32(%rsp), %r8d
	movq	(%rdi), %r13
	subl	%ebx, %r8d
	salq	$2, %rbx
	leaq	4(,%r8,4), %r14
	addq	%rbx, %r13
	xorl	%r8d, %r8d
	addq	%r9, %rbx
	.p2align 4,,10
	.p2align 3
.L32:
	movss	0(%r13,%r8), %xmm0
	movaps	%xmm0, %xmm2
	addss	%xmm0, %xmm1
	minss	(%rcx), %xmm2
	movss	%xmm2, (%rcx)
	movaps	%xmm0, %xmm2
	maxss	(%rsi), %xmm2
	movss	%xmm2, (%rsi)
	movss	(%rax), %xmm2
	addss	%xmm0, %xmm2
	movss	%xmm2, (%rax)
	movaps	%xmm0, %xmm2
	minss	(%r10), %xmm2
	movss	%xmm2, (%r10)
	movaps	%xmm0, %xmm2
	maxss	(%r11), %xmm2
	movss	%xmm2, (%r11)
	addss	(%rbx,%r8), %xmm0
	movss	%xmm0, (%rbx,%r8)
	addq	$4, %r8
	cmpq	%r8, %r14
	jne	.L32
.L33:
	pxor	%xmm2, %xmm2
	movss	(%rax), %xmm0
	cvtsi2ss	%edx, %xmm2
	divss	%xmm2, %xmm0
.L34:
	movss	%xmm0, (%rax)
	addq	$4, %rcx
	addq	$4, %rsi
	addq	$4, %rax
	addq	$4, %r11
	addq	$4, %r10
	addq	$8, %rdi
	cmpq	-48(%rsp), %rcx
	jne	.L35
.L4:
	movl	-28(%rsp), %eax
	imull	%edx, %eax
	testl	%eax, %eax
	jle	.L51
	pxor	%xmm0, %xmm0
	cvtsi2ss	%eax, %xmm0
	divss	%xmm0, %xmm1
.L36:
	movq	-8(%rsp), %rax
	testl	%edx, %edx
	movss	%xmm1, (%rax)
	jle	.L37
	leal	-1(%rdx), %eax
	leaq	4(%r9,%rax,4), %rax
	pxor	%xmm1, %xmm1
	cvtsi2ss	-28(%rsp), %xmm1
	.p2align 4,,10
	.p2align 3
.L38:
	movss	(%r9), %xmm0
	addq	$4, %r9
	divss	%xmm1, %xmm0
	movss	%xmm0, -4(%r9)
	cmpq	%rax, %r9
	jne	.L38
.L37:
	movl	-28(%rsp), %edx
	testl	%edx, %edx
	jle	.L39
	leal	-1(%rdx), %ecx
	movq	80(%rsp), %rax
	salq	$2, %rcx
	leaq	4(%rcx,%rax), %rdx
	.p2align 4,,10
	.p2align 3
.L42:
	movss	(%rax), %xmm0
	addq	$4, %rax
	minss	%xmm4, %xmm0
	cmpq	%rax, %rdx
	movaps	%xmm0, %xmm4
	jne	.L42
	movq	-24(%rsp), %rax
	movss	%xmm0, (%rax)
	movq	88(%rsp), %rax
	leaq	4(%rcx,%rax), %rdx
	.p2align 4,,10
	.p2align 3
.L46:
	movss	(%rax), %xmm0
	addq	$4, %rax
	maxss	%xmm3, %xmm0
	cmpq	%rax, %rdx
	movaps	%xmm0, %xmm3
	jne	.L46
.L47:
	movq	-16(%rsp), %rax
	movss	%xmm3, (%rax)
	popq	%rbx
	.cfi_remember_state
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
	.p2align 4,,10
	.p2align 3
.L23:
	.cfi_restore_state
	testl	%edx, %edx
	jne	.L33
	movss	.LC1(%rip), %xmm0
	jmp	.L34
	.p2align 4,,10
	.p2align 3
.L49:
	pxor	%xmm2, %xmm2
	xorl	%ebx, %ebx
	jmp	.L5
	.p2align 4,,10
	.p2align 3
.L51:
	movss	.LC1(%rip), %xmm1
	jmp	.L36
.L48:
	pxor	%xmm1, %xmm1
	jmp	.L4
.L39:
	movq	-24(%rsp), %rax
	movss	%xmm4, (%rax)
	jmp	.L47
.L79:
	movss	.LC2(%rip), %xmm4
	movss	.LC3(%rip), %xmm3
	jmp	.L2
	.cfi_endproc
.LFE23:
	.size	min_max_avg, .-min_max_avg
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC1:
	.long	2143289344
	.align 4
.LC2:
	.long	2139095040
	.align 4
.LC3:
	.long	4286578688
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
