  
s-talk: s-talk.o list.o 
	gcc -pthread -o s-talk list.o s-talk.o

list.o: list.c list.h
	gcc -c list.c

s-talk.o: s-talk.c list.h
	gcc -c s-talk.c 

clean:
	rm *.o s-talk