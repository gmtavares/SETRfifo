#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int *buffer;
	int size;
	int head;
	int tail;
	int count;
} FIFO;

void MyFIFOInit(FIFO *fifo, int size) {
	if (!fifo) {
		printf("FIFO pointer is NULL\n");
		return;
	}
	fifo->buffer = (int*)malloc(size * sizeof(int));
	if (!fifo->buffer) {
		printf("Failed to allocate buffer\n");
		return;
	}
	fifo->size = size;
	fifo->head = 0;
	fifo->tail = -1;
	fifo->count = 0;
	printf("FIFO initialized with size %d\n", size);
}

void MyFIFOInsert(FIFO *fifo, int item) {
	if (!fifo) {
		printf("FIFO pointer is NULL\n");
		return;
	}
	if (fifo->count == fifo->size) {
		printf("FIFO is full\n");
		return;
	}
	fifo->tail = (fifo->tail + 1) % fifo->size;
	fifo->buffer[fifo->tail] = item;
	fifo->count++;
}

int MyFIFORemove(FIFO *fifo) {
	if (!fifo) {
		printf("FIFO pointer is NULL\n");
		return 0;
	}
	if (fifo->count == 0) {
		printf("FIFO is empty\n");
		return 0;
	}
	int item = fifo->buffer[fifo->head];
	fifo->head = (fifo->head + 1) % fifo->size;
	fifo->count--;
	return item;
}

int MyFIFOPeep(FIFO *fifo) {
	if (!fifo) {
		printf("FIFO pointer is NULL\n");
		return 0;
	}
	if (fifo->count == 0) {
		printf("FIFO is empty\n");
		return 0;
	}
	return fifo->buffer[fifo->head];
}

int MyFIFOSize(FIFO *fifo) {
	if (!fifo) {
		printf("FIFO pointer is NULL\n");
		return 0;
	}
	return fifo->count;
}
