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

int MyFIFOInit(FIFO *fifo, int size) {
	if (!fifo) {
		#ifdef DEBUG
			printf("FIFO pointer is NULL\n");
		#endif
		return 1;
	}
	fifo->buffer = (int*)malloc(size * sizeof(int));
	if (!fifo->buffer) {
		#ifdef DEBUG
			printf("Failed to allocate buffer\n");
		#endif
		return 1;
	}
	fifo->size = size;
	fifo->head = 0;
	fifo->tail = -1;
	fifo->count = 0;
	#ifdef DEBUG
		printf("FIFO initialized with size %d\n", size);
	#endif
	return 0;
}

int MyFIFOInsert(FIFO *fifo, int item) {
	if (!fifo) {
		#ifdef DEBUG
			printf("FIFO pointer is NULL\n");
		#endif
		return 1;
	}
	if (fifo->count == fifo->size) {
		#ifdef DEBUG
			printf("FIFO is full\n");
		#endif
		return 1;
	}
	fifo->tail = (fifo->tail + 1) % fifo->size;
	fifo->buffer[fifo->tail] = item;
	fifo->count++;
	#ifdef DEBUG
		printf("Item %d inserted in FIFO\n", item);
	#endif
	return 0;
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

int MyFIFOPrint(FIFO* fifo)
	{
	//check if the FIFO is full
	if(MyFIFOSize(fifo) == 0)
		{
		#ifdef DEBUG
			printf("->FIFO empty!!!\n");
		#endif
		return 1;
		}

	//print the FIFO's array
	int cnt = fifo->count;
	int idx = fifo->head;

	while(cnt > 0)
		{
		printf("Value %d: %d\n", (fifo->count - cnt + 1), fifo->buffer[idx]);
		idx = (idx + 1) % fifo->size;//circular way
		cnt--;
		}
	return 0;
	}
	

int FIFOResize(FIFO *fifo, int newSize) {
	if (newSize < fifo->count) {
		#ifdef DEBUG
			printf("FIFO cannot be resized to a smaller size than the current number of elements.\n");
		#endif
		return 1;
	}

	int *new_buffer = (int*) malloc(newSize * sizeof(int));
	if (new_buffer == NULL) {
		#ifdef DEBUG
			printf("Error: Failed to allocate memory for new buffer.\n");
		#endif
		return 1;
	}

	// Copy elements to the new buffer
	int i, j;
	for (i = fifo->head, j = 0; j < fifo->count; ++i, ++j) {
		if (i == fifo->size) i = 0;
		new_buffer[j] = fifo->buffer[i];
	}

	free(fifo->buffer);
	fifo->buffer = new_buffer;
	fifo->size = newSize;
	fifo->head = 0;
	fifo->tail = fifo->count;

	return 0;
}
