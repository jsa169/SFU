all: s-talk

s-talk: s-talk.o list.o
	gcc -Wall -pthread -o s-talk s-talk.o list.o

s-talk.o: s-talk.c
	gcc -c s-talk.c

clean:
	rm -f s-talk s-talk.o