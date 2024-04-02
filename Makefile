CPP=g++
CPPFLAGS=-std=c++17 -I.

main: main.o Field.o
	$(CPP) $(CPPFLAGS) -o main main.o Field.o

main.o : main.cpp
	$(CPP) $(CPPFLAGS) -c main.cpp

Field.o : Field.cpp
	$(CPP) $(CPPFLAGS) -c Field.cpp

clean :
	rm main Field.o main.o

