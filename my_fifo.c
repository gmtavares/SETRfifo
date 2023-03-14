#include <stdlib.h>
#include <stdio.h>
#include "my_fifo.h"

/*typedef struct {
	int *buffer;
	int size;
	int head;
	int tail;
	int count;
} FIFO;*/

void MyFIFOInit(FIFO *fifo, int size) {
	if (!fifo) {
		#ifdef DEBUG
			printf("FIFO pointer is NULL\n");
		#endif
		return;
	}
	fifo->buffer = (int*)malloc(size * sizeof(int));
	if (!fifo->buffer) {
		#ifdef DEBUG
			printf("Failed to allocate buffer\n");
		#endif
		return;
	}
	fifo->size = size;
	fifo->head = 0;
	fifo->tail = -1;
	fifo->count = 0;
	#ifdef DEBUG
		printf("FIFO initialized with size %d\n", size);
	#endif
}

void MyFIFOInsert(FIFO *fifo, int item) {
	if (!fifo) {
		#ifdef DEBUG
			printf("FIFO pointer is NULL\n");
		#endif
		return;
	}
	if (fifo->count == fifo->size) {
		#ifdef DEBUG
			printf("FIFO is full\n");
		#endif
		return;
	}
	fifo->tail = (fifo->tail + 1) % fifo->size;
	fifo->buffer[fifo->tail] = item;
	fifo->count++;
	#ifdef DEBUG
		printf("Item %d inserted in FIFO\n", item);
	#endif
}

int MyFIFORemove(FIFO *fifo) {
	if (!fifo) {
		#ifdef DEBUG
			printf("FIFO pointer is NULL\n");
		#endif
		return 0;
	}
	if (fifo->count == 0) {
		#ifdef DEBUG
			printf("FIFO is empty\n");
		#endif
		return 0;
	}
	int item = fifo->buffer[fifo->head];
	fifo->head = (fifo->head + 1) % fifo->size;
	fifo->count--;
	#ifdef DEBUG
		printf("Item %d removed from FIFO\n", item);
	#endif
	return item;
}

int MyFIFOPeep(FIFO *fifo) {
	if (!fifo) {
		#ifdef DEBUG
			printf("FIFO pointer is NULL\n");
		#endif
		return 0;
	}
	if (fifo->count == 0) {
		#ifdef DEBUG
			printf("FIFO is empty\n");
		#endif
		return 0;
	}
	#ifdef DEBUG
		printf("Peeped at item %d in FIFO\n", fifo->buffer[fifo->head]);
	#endif
	return fifo->buffer[fifo->head];
}

int MyFIFOSize(FIFO *fifo) {
	if (!fifo) {
		#ifdef DEBUG
			printf("FIFO pointer is NULL\n");
		#endif
		return 0;
	}
	#ifdef DEBUG
		printf("FIFO size is %d\n", fifo->count);
	#endif
	return fifo->count;
}
