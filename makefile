CC = gcc
CFLAGS = -Wall -O3

all: FIFOTester

FIFOTester: my_fifo.o main.o
	$(CC) $(CFLAGS) -o FIFOTester my_fifo.o

my_fifo.o: my_fifo.c my_fifo.h
	$(CC) $(CFLAGS) -c my_fifo.c

clean:
	rm -f FIFOTester *.o
