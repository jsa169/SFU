    .globl dot_prod
dot_prod:

	# rdi = Pointer to A
	# rsi = Pointer to B

	# edx = n
	# ecx = i
	# r8d = j
	# al = return value

	# /rax /rcx /rdx /rsi /rdi /r8 r9 r10 r11


	xorl	%eax, %eax

	movl	%edx, %r11d		#Size per row
	movb	$0, %al		# Set return value to 0

	imull	%ecx, %r11d 	# Position of first first A element
	addq	%r11, %rdi		# Position of first A element

	addq	%r8, %rsi		# Position of first first B element

	movl	%edx,%r11d		#Size per row

Loop:
	movq 	(%rdi), %r9		# set current value of A
	imulq 	(%rsi), %r9		# multiply A * B   ->   A

	addb	%r9b, %al


Back:

	incq 	%rdi			# Increment A by 1
	addq	%r11, %rsi		# Add size per row to B

	decl 	%edx			# increment k by 1
	cmpl	$0, %edx		# (n-1) - 0 ? 0
	jg	Loop					

	ret
