#sum_float.s
#
#Description: sum up the elements in anarray, by applying the heuristic of adding the two
#             smallest. After each calculation, save the partial result into Q, then add the
#             two small number, until there is only on number left. Return that number
#
#Auther: Jichuan Shi
#Data:2019-10-24
#


	.globl sum_float

    # var map:
    #   %xmm0:  total
    #   %rdi:   F[n] (array pointer)
    #   %rsi:   n
    #   %rbp:   head pointer
    #   %rsp:   tail pointer
    #   %rdx:   loop counter
    #   %rcx:   infinity
    #   %xmm1:  x
    #   %xmm2:  y
    #   %xmm3:  temp

sum_float:
    push    %rbp
    mov    %rsp, %r8   		 #saving original stack pointer

    movq $0x7f800000, %rcx   #push infinity to Q  						 
    push %rcx

    mov    %rsp, %rbp  	     # Q <- empty
    addq $8, %rsp

    mov $1, %rdx   			 #loop counter = 1
    mov %rsi, %rax           #array size counter

loop:
    cmpq    %rsi, %rdx       # while (counter < n) {        	 
    jge    endloop

    xorps    %xmm0, %xmm0       # total <- 0.0
    movss    (%rdi), %xmm1      #head F
    movss    (%rbp), %xmm3      #head Q

    cmp $0, %rax               #if array size counter = 0
    jg continuex               #head F = infinity
    movq %rcx, %xmm1
 
continuex:   	 
    minss    %xmm3, %xmm1       #x = min(head Q, head F)
    comiss     (%rdi), %xmm1    
    je dequeuex

    subq $8, %rbp   			 #dequeue x from Q if head Q smaller
    jmp followx

dequeuex:
    addq $4, %rdi   			 #dequeue F from F if head F smaller, array size counter
    dec %rax

followx:   
    movss    (%rdi), %xmm2   	#head F
    movss    (%rbp), %xmm3      #head Q

    cmp $0, %rax                #if array size counter = 0
    jg continuey                #head F = infinity
    movq %rcx, %xmm2

continuey:         
    minss    %xmm3, %xmm2       #x = min(head Q, head F)
    comiss     (%rdi), %xmm2
    je dequeuey

    subq $8, %rbp   			 #dequeue Q
    jmp followy

dequeuey:
    addq $4, %rdi   			 #dequeue F, array size counter --
    dec %rax

followy:
    addss    %xmm1, %xmm0       #total = x+y
    addss    %xmm2, %xmm0
    movq    %xmm0, %r9
    push    %r9                 #push total
    push    %rcx                #push infinity at back of queue
    addq $8, %rsp

    inc    %rdx   				#loop counter ++
    jmp    loop                	# }

endloop:
    movq    (%rbp), %xmm0
    mov     %r8, %rsp
    pop   	 %rbp
    ret
