#lsearch_2.s
#
#
#Name: Jichuan Shi
#Date: 20109-10-30
#

#rdi = *A
#rsi = n
#rdx = target
#r9d = temp
#ecx = i
.globl	lsearch_2

lsearch_2:

	testl	%esi, %esi 				# if (n <= 0) return -1;
	jle	notFound					

	movslq	%esi, %rax				
	leaq	-4(%rdi,%rax,4), %rax 
	movl	(%rax), %r9d 			# temp = A[n-1];
	movl	%edx, (%rax)			# A[n-1] = target;
	
	cmpl	(%rdi), %edx			# if(target == A[0]){
	je	foundatzero					# 	 ['i = 0;
									# }else{									
	movl	$1, %ecx				# 	 i = 1;
									#	 
whileLoop:							# 	 while (A[i] != target){
	movl	%ecx, %r8d				# 	 
	addq	$1, %rcx				# 		  i++;
	cmpl	%edx, -4(%rdi,%rcx,4)	#    	 	 	 
	jne	whileLoop					#    }	 
									# }
compare:
	movl	%r9d, (%rax)			# A[n-1] = temp;
	leal	-1(%rsi), %eax
	cmpl	%r8d, %eax				# if (j < n-1) ret i;
	jg	found

	cmpl	%edx, %r9d				# else if (A[n-1] = target) ret n-1; 
	jne	notFound					# else ret -1;
	rep ret


found:
	movl	%r8d, %eax			
	ret


foundatzero:
	xorl	%r8d, %r8d				
	jmp	compare

notFound:
	movl	$-1, %eax	
	ret
