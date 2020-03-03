all: wi

Driver: Driver.o List.o Patient.o 
	g++ -Wall -o Driver Driver.o List.o Patient.o

wi: walkIn.o List.o Patient.o
	g++ -Wall -o wi walkIn.o List.o Patient.o

Driver.o: Driver.cpp List.h Patient.h
	g++ -Wall -std=c++03 -c Driver.cpp

walkIn.o: walkIn.cpp List.h Patient.h
	g++ -Wall -std=c++03 -c walkIn.cpp

List.o: List.h List.cpp
	g++ -Wall -std=c++03 -c List.cpp

Patient.o: Patient.h Patient.cpp
	g++ -Wall -std=c++03 -c Patient.cpp

clean:
	rm -f wi *.o