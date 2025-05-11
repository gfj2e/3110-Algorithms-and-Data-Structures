CC=g++
CFLAGS=-g -v

## Create the executable Run
Run:bst.o	wordEntry.o main.o
	$(CC) bst.o wordEntry.o main.o -o project_6

bst.o:bst.cpp
	$(CC) $(CFLAGS) -c bst.cpp

wordEntry.o:wordEntry.cpp
	$(CC) $(CFLAGS) -c wordEntry.cpp

main.o:main.cpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm *.o