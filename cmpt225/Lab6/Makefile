
x:	main.o BST.o
	g++ -o x BST.o main.o

main.o:	main.cpp BST.h
	g++ -c main.cpp

BST.o:	BST.cpp BST.h
	g++ -c BST.cpp

clean:	
	rm -f *.o x
