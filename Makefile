CPP=g++
#CPP=/opt/homebrew/bin/g++-13
CPPFLAGS=-std=c++17 -I.

main: main.o Field.o Graph.o PathAlgebra.o Path.o
	$(CPP) $(CPPFLAGS) -o main main.o Field.o Graph.o PathAlgebra.o Path.o

main.o : main.cpp
	$(CPP) $(CPPFLAGS) -c main.cpp

Field.o : Field.cpp
	$(CPP) $(CPPFLAGS) -c Field.cpp

Graph.o : Graph.cpp
	$(CPP) $(CPPFLAGS) -c Graph.cpp

PathAlgebra.o : PathAlgebra.cpp
	$(CPP) $(CPPFLAGS) -c PathAlgebra.cpp

Path.o : Path.cpp
	$(CPP) $(CPPFLAGS) -c Path.cpp

clean :
	rm main Field.o Graph.o main.o PathAlgebra.o Path.o
