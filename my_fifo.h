#ifndef MY_FIFO_H
#define MY_FIFO_H

/**
 * @file my_fifo.h
 * @brief A module that implements a FIFO data structure
 */

/**
 * @brief A struct representing a FIFO
 */
typedef struct {
	int *buffer; /**< The buffer holding the FIFO's data */
	int size; /**< The size of the FIFO */
	int head; /**< The index of the FIFO's head */
	int tail; /**< The index of the FIFO's tail */
	int count; /**< The number of items in the FIFO */
} FIFO;

/**
 * @brief Initialize the FIFO
 *
 * @param fifo A pointer to the FIFO to initialize
 * @param size The size of the FIFO
 */
void MyFIFOInit(FIFO *fifo, int size);

/**
 * @brief Add an item to the FIFO
 *
 * @param fifo A pointer to the FIFO to add the item to
 * @param item The item to add to the FIFO
 */
void MyFIFOInsert(FIFO *fifo, int item);

/**
 * @brief Remove and return an item from the FIFO
 *
 * @param fifo A pointer to the FIFO to remove the item from
 * @return The item that was removed from the FIFO, or 0 if the FIFO is empty
 */
int MyFIFORemove(FIFO *fifo);

/**
 * @brief Return the oldest item in the FIFO, without removing it
 *
 * @param fifo A pointer to the FIFO to return the item from
 * @return The oldest item in the FIFO, or 0 if the FIFO is empty
 */
int MyFIFOPeep(FIFO *fifo);

/**
 * @brief Return the number of items in the FIFO
 *
 * @param fifo A pointer to the FIFO to return the size of
 * @return The number of items in the FIFO
 */
int MyFIFOSize(FIFO *fifo);

#endif /* MY_FIFO_H */
