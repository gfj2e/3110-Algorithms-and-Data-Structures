CC=g++
CFLAGS=-g -v

## Create the executable Run
Run:type.o	flightMap.o main.o
	$(CC) type.o flightMap.o main.o -o project_3

type.o:type.cpp
	$(CC) $(CFLAGS) -c type.cpp

flightMap.o:flightMap.cpp
	$(CC) $(CFLAGS) -c flightMap.cpp

main.o:main.cpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm *.o