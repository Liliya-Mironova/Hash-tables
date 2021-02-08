CC=g++

CFLAGS=-c -Wall -std=gnu++11

all: hw2

hw2: list.o hashfunc.o filereader.o creator.o main.o
	$(CC) list.o hashfunc.o filereader.o creator.o main.o -o hw2

list.o: list.cpp
	$(CC) $(CFLAGS) list.cpp

hashfunc.o: hashfunc.cpp
	$(CC) $(CFLAGS) hashfunc.cpp

filereader.o: filereader.cpp
	$(CC) $(CFLAGS) filereader.cpp

creator.o: creator.cpp
	$(CC) $(CFLAGS) creator.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

clean:
	rm -rf *.o hw2