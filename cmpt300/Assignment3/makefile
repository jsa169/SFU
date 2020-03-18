all: simulation

simulation: simulation.o list.o function.o
	gcc -Wall -o simulation simulation.o list.o function.o

s-simulation.o: simulation.c
	gcc -c simulation.c

function.o: function.c function.h
	gcc -c function.c
clean:
	rm -f simulation.o function.o simulation