/**
 * @file main.c
 * @brief A test application for the FIFO module
 */

#include <stdlib.h>
#include <stdio.h>
#include "my_fifo.h"

/**
 * @brief Main function of the test application
 *
 * Initializes a FIFO with size 3 and performs a sequence of actions to
 * verify the correctness of the FIFO module.
 *
 * This test application performs the following sequence of actions:
 * - Initializes a FIFO with size 3.
 * - Verifies that the FIFO is empty after initialization.
 * - Adds three items to the FIFO to fill it up.
 * - Verifies that the FIFO is full after adding the items.
 * - Tries to add another item to the full FIFO.
 * - Verifies that the FIFO is still full and that the new item was not added.
 * - Removes two items from the FIFO.
 * - Verifies that the removed items are correct.
 * - Adds two more items to the FIFO to fill it up again.
 * - Verifies that the FIFO is full again.
 * - Tries to remove an item from the empty FIFO.
 * - Verifies that the FIFO is still empty and that no item was removed.
 * If any of these actions fail to produce the expected results, the test application prints an error message and returns a non-zero exit code.
 * If all actions pass, the test application prints that it was a success and will return 0.
 * @return 0 if all tests passed, non-zero otherwise
 */

int main() {
	// Initialize a FIFO with size 3
	FIFO fifo;
	if (MyFIFOInit(&fifo, 3) == 1) {
		printf("ERROR: FIFO failed to initialize\n");
	}
	else {
		printf("SUCCESS: FIFO initialized\n");
	}
	// Verify that the FIFO is empty
	if (MyFIFOSize(&fifo) != 0) {
		printf("ERROR: FIFO is not empty after initialization\n");
		return 1;
	}
	else {
		printf("SUCCESS: FIFO initialized as empty\n");
	}

	int insertCount = 0;

	// Add some items to the FIFO
	if (MyFIFOInsert(&fifo, 1) == 1) {
		printf("ERROR: FIFO failed to insert\n");
		insertCount++;
	}
	if (MyFIFOInsert(&fifo, 2) == 1) {
		printf("ERROR: FIFO failed to insert\n");
		insertCount++;
	}
	if (MyFIFOInsert(&fifo, 3) == 1) {
		printf("ERROR: FIFO failed to insert\n");
		insertCount++;
	}
	if(insertCount==3) {
		printf("SUCCESS: Added all items to the FIFO");
	}


	// Verify that the FIFO is full
	if (MyFIFOSize(&fifo) != 3) {
		printf("ERROR: FIFO is not full after adding items\n");
		return 1;
	}

	// Try to add an item to the full FIFO
	if (MyFIFOInsert(&fifo, 4) == 1) {
		printf("SUCCESS: FIFO failed to insert\n");
	}

	// Verify that the FIFO is still full and that the new item was not added
	if (MyFIFOSize(&fifo) != 3) {
		printf("ERROR: FIFO size changed after attempting to insert item into full FIFO\n");
		return 1;
	}
	else {
		printf("SUCCESS: FIFO is still full and new item was not added\n");
	}

	// Remove some items from the FIFO
	int item1 = MyFIFORemove(&fifo);
	int item2 = MyFIFORemove(&fifo);

	// Verify that the removed items are correct
	if (item1 != 1 || item2 != 2) {
		printf("ERROR: Incorrect items removed from FIFO\n");
		return 1;
	}
	else {
		printf("SUCCESS: Correct items removed from FIFO\n");
	}

	// Add some more items to the FIFO
	MyFIFOInsert(&fifo, 4);
	MyFIFOInsert(&fifo, 5);

	// Verify that the FIFO is full again
	if (MyFIFOSize(&fifo) != 3) {
		printf("ERROR: FIFO is not full after adding more items\n");
		return 1;
	}
	else {
		printf("SUCCESS: FIFO is full again\n");
	}

	// Try to remove an item from the empty FIFO
	int item3 = MyFIFORemove(&fifo);
	int item4 = MyFIFORemove(&fifo);
	int item5 = MyFIFORemove(&fifo);
	int item6 = MyFIFORemove(&fifo);
	
	// Verify that the FIFO is still empty and that no item was removed
	if (MyFIFOSize(&fifo) != 0 || item6 != 0) {
		printf("ERROR: FIFO size changed or item removed from empty FIFO\n");
		return 1;
	}
	else {
		printf("SUCCESS: FIFO is still empty and that no item was removed\n");
	}

	// Return success if all tests passed
	printf("FIFOTester: All tests passed!\n");
	return 0;
}
