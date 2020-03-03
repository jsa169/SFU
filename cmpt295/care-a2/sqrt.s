#filename: sqrt.s
#
#Description: This code ueses the Digit-by-digit algorithm for square root(sqrt).
#			  It will compute the sqrt from the most significant bit down to the
#			  least. It will give an integer result, that represents the floor of
#			  the true sqrt. For example sqrt(2) = 1.414, the result will be "1"
#
#
#Auther: Jichuan Shi
#Date: 2019-09-27
#
#---------------------------------------------------------------------
	.globl sqrt
sqrt:

	#%edi - x
	#%eax - return value

	movl $0, %eax   	#result <- 0

	movl $15, %ecx		#set k to 15
	movl $0x8000, %r8d	#set mask to 1000 0000 0000 0000

forloop:#-------------------------------------------------------------
						#for k from 15 downto 0 do:
	cmpl $0, %ecx			#if count - 0 ? 0
	jl endl						#jump to return
	decl %ecx				#count k --											

	xorl %r8d, %eax			#change the kth bit of result to 1
	
	movl %eax, %esi
	imul %esi, %esi 		#square the result and store in temp
	
	cmpl %esi, %edi			#if ("temp") result * result > x then:	
	jb changeback				#jump to change back		
	
	shr $1, %r8d			#shift max 1 position to the right
	jmp forloop				#jump back to for loop

changeback:#----------------------------------------------------------

	xorl %r8d, %eax		#change the kth bit of result back to 0
	shr $1, %r8d		#shift max 1 position to the right
	jmp forloop			#jump back to for loop			

endl:#----------------------------------------------------------------
	ret 				#return result

	