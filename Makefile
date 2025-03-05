# Just uncomment whichever it is on your machine
CPP=g++
#CPP=/opt/homebrew/bin/g++-13
CPPFLAGS=-std=c++20 -I.

main: main.o Field.o Graph.o PathAlgebra.o Path.o PathTable.o PAElement.o PathOrder.o SumCollector.o
	$(CPP) $(CPPFLAGS) -o main main.o Field.o Graph.o PathAlgebra.o Path.o PathTable.o PAElement.o PathOrder.o SumCollector.o

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

PathTable.o : PathTable.cpp
	$(CPP) $(CPPFLAGS) -c PathTable.cpp

PAElement.o : PAElement.cpp
	$(CPP) $(CPPFLAGS) -c PAElement.cpp

PathOrder.o : PathOrder.cpp
	$(CPP) $(CPPFLAGS) -c PathOrder.cpp

SumCollector.o : SumCollector.cpp
	$(CPP) $(CPPFLAGS) -c SumCollector.cpp

clean :
	rm main Field.o Graph.o main.o PathAlgebra.o Path.o PathTable.o PAElement.o PathOrder.o SumCollector.o
