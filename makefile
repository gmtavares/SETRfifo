CC = gcc
CXXFLAGS = -Wall -03

LDFLAGS = -pthread -lm

TARGET = my_fifo FIFOTester

all: $(TARGET)

$(TARGET): my_fifo.o FIFOTester.o
		gcc -o $@ $^ $(LDFLAGS)

$(TARGET):

clean:
		rm -f *.o *~

cleanall:	clean
		rm -f $(TARGET)




# CC = gcc
# CFLAGS = -Wall -O3

# TARGET = my_fifo FIFOTester

# all:	$(TARGET)

# FIFOTester: my_fifo.o
# 	$(CC) $(CFLAGS) -o FIFOTester my_fifo.o

# my_fifo.o: my_fifo.c my_fifo.h
# 	$(CC) $(CFLAGS) -c my_fifo.c

# clean:
# 	rm -f FIFOTester *.o
