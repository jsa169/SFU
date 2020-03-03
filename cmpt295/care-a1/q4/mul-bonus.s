##This Method will add a to it self until the total number of a exceeds the requirement b. 
##Then add what ever that is left.
##if b = 1500
##Result = 2a --> 4a --> 8a --> 16a --> 32a --> 64a --> 128a --> 256a --> 512a --> 1024a --> stop
##Result = 1024a + a + a + a + a + ........ + a = 1500a
##
##Old method:    1500    comparisons      1500  additions
##New Methods    9 + 476 comparisons      9+476 additions
##
##Possible to reloop from 1024, but don't have enough tools yet
##
##Name: Jichuan Shi
##Date: September 19, 2019
##
##


	.globl times
times:

	# %edi		a 
	# %esi		b		
	# %eax		return value


	movl	$1,	%ecx			#set counting variable, %ecx = 1
	movl	%edi, %eax			#set initial return vlue, %eax = 0

loop:
	movl	%ecx, %ebp			#put count into temp, %ebp = temp
	addl 	%ebp, %ebp			#double temp, temp = temp + temp

	cmpl	%ebp, %esi			#check loop condition, if b - temp? 0
	jbe		addrest				#jump to add rest if temp > b

	addl	%eax, %eax			#double result, %edu = %eax + %eax
	addl 	%ecx, %ecx			#double count, %ecx = % ecx + %ecx
	jmp 	loop				#jump to start of loop


addrest:
	cmpl	%ecx, %esi			#check loop condition, b - count ? 0
	je		return				#jump to conclusion count = b

	addl	%edi, %eax			#add a to result, %ead = %eax + a
	incl 	%ecx				#increase counting varible by 1, %ecx + 1
	jmp 	addrest				#jump to start of addrest

return:
	ret
