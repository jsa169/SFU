#filename: sqrtrd.s
#
#Description: This code ueses the Digit-by-digit algorithm for square root(sqrt).
#			  It will compute the sqrt from the most significant bit down to the
#			  least. It will calculate the floor and ceil of the true sqrt, then
#			  round the which ever is closer to the true sqrt. 
#			  For example: sqrt(2)=1.414 which is 1, sqrt(3)=1.732 which is 2
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

forloop:#finds the floor of sqrt---------------------------------------
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

endl:#round sqrt to either floor or ceil------------------------------
	
	movl %eax, %esi		#get floor of sqrt from above
	imul %esi, %esi		#floor^2

	movl %eax, %ecx		#duplicate result
	incl %ecx			#get ceiling of sqrt
	imul %ecx, %ecx		#ceiling^2

	subl %edi, %ecx		#difference between x and ceil^2
	subl %esi, %edi		#difference between x and floor^2

	cmpl %edi, %ecx		#compare the resulting differences
	jge return			#jump to return if floor^2 is closer to x
	incl %eax			#if ceil^2 is closer to x, increase sqrt(floor) by 1

return:#--------------------------------------------------------------
	ret 				#return result

	