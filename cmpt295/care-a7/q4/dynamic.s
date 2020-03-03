	.file	"dynamic.c"
	.text
	.globl	new_42
	.type	new_42, @function
new_42:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$8, %edi
	call	malloc@PLT
	movq	%rax, -16(%rbp)
	movq	$42, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	new_42, .-new_42
	.globl	N
	.data
	.align 8
	.type	N, @object
	.size	N, 8
N:
	.quad	10
	.text
	.globl	donotmuchofanything
	.type	donotmuchofanything, @function
donotmuchofanything:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	N(%rip), %rax
	leaq	-1(%rax), %rdx
	movq	%rdx, N(%rip)
	testq	%rax, %rax
	je	.L5
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	donotmuchofanything
	movq	N(%rip), %rax
	addq	$1, %rax
	movq	%rax, N(%rip)
.L5:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	donotmuchofanything, .-donotmuchofanything
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
