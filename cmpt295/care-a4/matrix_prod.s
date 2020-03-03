#matirx_prod.s
#
#Description: Takes matrix A, B, C, and size n as input. Calculate all the dot products
#			  Using A and B and store in C using dot_prod. Then, mod(result, 17) to get 
#			  the final result. Store the final result in C
#
#
#Author: Jichuan Shi
#Date: 2019-10-18
#
    .globl matrix_prod

matrix_prod:            # void matrix_prod(void *A, void *B, void *C, int n);
											#rdi		rsi		rdx		rcx

push	%rbx			#Push Callee Saved
push	%rbp
push	%r10
push	%r11
movq	%rdi, %rbx		# *A
movq	%rsi, %rbp		# *B
movq	%rdx, %r10		# *C
movq	%rcx, %r11		# n

mov	$-1, %r9			# i = -1

outerLoop:				#outerloop:
	mov	$-1, %r8			# j = -1
	incq	%r9				#i++

	cmpq %r9, %r11			# loop endloop if i = m
	je endloop			

innerLoop:					#innerloop:
	incq	%r8					#j++
	
	cmpq	%r8, %r11			# loop outerloop if j = n
	jle outerLoop
	
	push	%r8					#Push Caller saved
	push	%r9

	movq	%rbx,	%rdi		#Set arguments for function calling dot_peroduct
	movq	%rbp, 	%rsi
	movq	%r11,	%rdx
	movq	%r9,	%rcx
	movq	%r8,	%r8

	call	dot_prod			#call dot_peroduct

	movq	%rax,	%rdi		#Set arguments for function calling mod
	movq	$17,	%rsi
	call	mod 				#Call mod

	pop		%r9					#Pop caller saved
	pop		%r8

	movq	%rax, (%r10)		#set Value in Matrix C
	incq	%r10

	jmp innerLoop				#loop innerloop		

endloop:
	pop		%r11	#Pop callee saved
	pop		%r10
	pop		%rbp
	pop		%rbx
	ret				#ret
