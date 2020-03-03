all: TEST

TEST: test.o List.o
	gcc -Wall -o TEST test.o List.o

test.o: test.c
	gcc -c test.c

List.o: List.c List.h
	gcc -c List.c
clean:
	rm -f test *.o