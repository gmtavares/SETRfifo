#include <stdlib.h>

typedef struct {
	int *buffer;
	int size;
	int head;
	int tail;
	int count;
} FIFO;

void MyFIFOInit(FIFO *fifo, int size) {
	fifo->buffer = (int*)malloc(size * sizeof(int));
	fifo->size = size;
	fifo->head = 0;
	fifo->tail = -1;
	fifo->count = 0;
}

void MyFIFOInsert(FIFO *fifo, int item) {
	if (fifo->count == fifo->size) {
		return; // FIFO is full
	}
	fifo->tail = (fifo->tail + 1) % fifo->size;
	fifo->buffer[fifo->tail] = item;
	fifo->count++;
}

int MyFIFORemove(FIFO *fifo) {
	if (fifo->count == 0) {
		return 0; // FIFO is empty
	}
	int item = fifo->buffer[fifo->head];
	fifo->head = (fifo->head + 1) % fifo->size;
	fifo->count--;
	return item;
}

int MyFIFOPeep(FIFO *fifo) {
	if (fifo->count == 0) {
		return 0; // FIFO is empty
	}
	return fifo->buffer[fifo->head];
}

int MyFIFOSize(FIFO *fifo) {
	return fifo->count;
}
