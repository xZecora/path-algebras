CPP=g++
CPPFLAGS=-std=c++17 -I.

main: main.o Field.o Graph.o
	$(CPP) $(CPPFLAGS) -o main main.o Field.o Graph.o

main.o : main.cpp
	$(CPP) $(CPPFLAGS) -c main.cpp

Field.o : Field.cpp
	$(CPP) $(CPPFLAGS) -c Field.cpp

Graph.o : Graph.cpp
	$(CPP) $(CPPFLAGS) -c Graph.cpp

clean :
	rm main Field.o Graph.o main.o

