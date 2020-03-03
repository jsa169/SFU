##Name: Jichuan Shi
##Date: September 19, 2019
##
##
	.globl times
times:
	##mov %edi, %eax      #  remove these two lines before
	##imull %esi, %eax    #  you start writing your code

	# %edi		a 
	# %esi		b		
	# %eax		return value


	movl	$0,	%ecx			#set counting variable to 0
	movl	$0, %eax			#set initial return vlue to 0

loop:
	cmpl	%ecx, %esi			#check loop condition, if all b of a's are added
	je		return				#jump to conclusion if all complete

	addl	%edi, %eax			#add 1 of a to result
	incl 	%ecx				#increase counting varible by 1
	jmp 	loop				#jump to start of loop
	
return:
	ret

