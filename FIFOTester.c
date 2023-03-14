/**
 * @file main.c
 * @remarks Note: using Whitesmiths indetation
 * @author (2023) José Ribeiro, 72473 <j.miguel.ribeiro at ua.pt>
 * @author (2023) Gonçalo Tavares 93030 <gmtavares at ua.pt>
*/

#include <stdio.h>//to use printf, scanf
#include <stdlib.h>//to use malloc
#include <errno.h>//to use system error numbers (EPERM, EINVAL, ESRCH, ENOSPC, (...))
#include <assert.h>//to use asserts

#include "my_fifo.h"

int menuOption, value, c;//local variables declaration
int insertCount = 0;


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
 * - Resizes the FIFO to size 5
 * - Verifies that the FIFO is full again.
 * - Tries to remove an item from the empty FIFO.
 * - Verifies that the FIFO is still empty and that no item was removed.
 * If any of these actions fail to produce the expected results, the test application prints an error message and returns a non-zero exit code.
 * If all actions pass, the test application prints that it was a success and will return 0.
 * @return 0 if all tests passed, non-zero otherwise
 */

int AutoTest() {
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
	if(insertCount==0) {
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
	 printf("FIFO before resizing: \n");
	MyFIFOPrint(&fifo);

	int newSize = 5;
	int result = FIFOResize(&fifo, newSize);

	if(result == 0) {
		printf("FIFO after resizing to %d: \n", newSize);
		MyFIFOPrint(&fifo);
	}
	else {
	printf("Failed to resize FIFO.\n");
	}
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




/**********************************************************/
static void printMenu()
	{
	printf("+===============================================+\n"
		   "|            Manipulation functions             |\n"
		   "+===============================================+\n"
		   "| 1: Initialization of FIFO                     |\n"
		   "| 2: Insert new element in FIFO                 |\n"
		   "| 3: Peak tail (newest) element of the FIFO     |\n"
		   "| 4: Remove head (oldest) element from FIFO     |\n"
		   "| 5: isFull()                                   |\n"
		   "| 6: isEmpty()                                  |\n"
		   "| 7: size()                                     |\n"
		   "| 8: print()                                    |\n"
		   "| 9: Resize()                                   |\n"
		   "| 10: AutoTest()                                |\n"
		   "| 0: Quit                                       |\n"
		   "+===============================================+\n\n");
	}
/**********************************************************/

/**********************************************************/
static void readMenuOption()
	{
	menuOption = -1;
	do
		{
		printf("Option: ");
		scanf("%d", &menuOption);

		//flushes the stdin
		while(((c = getchar()) != '\n') && (c != EOF));//solution from the internet

		if((menuOption < 0) || (menuOption > 10)) printf("  Invalid value!\n");
		}
	while((menuOption < 0) || (menuOption > 10));
	//printf("Selected: %d\n", menuOption);
	}
/**********************************************************/

int main()
	{
	printMenu();
	while(1)
		{
		//printMenu();
		readMenuOption();//read the input of the menu option

		switch(menuOption)
			{
			/******************************************************************/
			case(0)://Exit
				printf("  Exit!!!\n");
				return(0);
			/******************************************************************/
			case(1)://FIFO initialization
				printf("  ->FIFO initialization\n");

				//------------------------------------------
				//read the input of the FIFO's size
				do
					{
					printf("  FIFO size (>0): ");
					scanf("%d", &value);//read the input number

					//flushes the stdin
					while(((c = getchar()) != '\n') && (c != EOF));//solution from the internet

					//invalid input size
					if(value <= 0) printf("  Invalid size!\n");
					}
				while(value <= 0);
				//------------------------------------------

				FIFO fifo;//declaration of the FIFO

				//initialization of the FIFO
				if(MyFIFOInit(&fifo, value) == 1)
					{
					printf("ERROR: FIFO failed to initialize\n");
					}
				else
					{
					printf("SUCCESS: FIFO initialized\n");
					}

				// Verify that the FIFO is empty
				if(MyFIFOSize(&fifo) != 0)
					{
					printf("ERROR: FIFO is not empty after initialization\n");
					return(1);
					}
				else
					{
					printf("SUCCESS: FIFO initialized as empty\n");
					}
				break;
			/******************************************************************/
			case(2)://FIFO insert
				printf("  ->FIFO insert\n");

				//------------------------------------------
				//read the input of the FIFO's size
				printf("  element: ");
				scanf("%d", &value);//error -> allowing letters and chars

				//flushes the stdin
				while(((c = getchar()) != '\n') && (c != EOF));//solution from the internet
				//------------------------------------------

				if(MyFIFOInsert(&fifo, value) == 1)
					{
					printf("ERROR: FIFO failed to insert\n");
					}
				else
					{
					insertCount++;
					}

				break;
			/******************************************************************/
			case(3)://FIFO peak
				printf("  ->FIFO peak\n");
				value = MyFIFOPeep(&fifo);
				printf("  Peaked element: %d\n", value);
				break;
			/******************************************************************/
			case(4)://FIFO remove head
				printf("  ->FIFO remove\n");

				int item1 = MyFIFORemove(&fifo);

				if(item1 == 0)//empty
					{
					printf("->FIFO empty!!!\n");
					}
				else
					{
					printf("->Sucessful removal!!!\n");
					}

				break;
			/******************************************************************/
			case(5)://isFull()
				printf("  ->FIFO isFull\n");

				//check if the FIFO is full
				if(MyFIFOSize(&fifo) == fifo.size)
					{
					printf("->FIFO full!!!\n");
					}
				else
					{
					printf("->FIFO not full!!!\n");
					}
				break;
			/******************************************************************/
			case(6)://isEmpty()
				printf("  ->FIFO isEmpty\n");

				//check if the FIFO is full
				if(MyFIFOSize(&fifo) == 0)
					{
					printf("->FIFO empty!!!\n");
					}
				else
					{
					printf("->FIFO not empty!!!\n");
					}
				break;
			/******************************************************************/
			case(7)://size()
				printf("  ->FIFO size = %d\n",MyFIFOSize(&fifo));
				break;
			/******************************************************************/
			case(8)://print()
				printf("  ->FIFO print: \n");
				MyFIFOPrint(&fifo);
				break;
			/******************************************************************/
			case(9)://Resize()
				printf("  ->FIFO resize: \n");
				printf("  New Size: ");
				scanf("%d", &value);//error -> allowing letters and chars
				//flushes the stdin
				while(((c = getchar()) != '\n') && (c != EOF));//solution from the internet
				printf("FIFO before resizing: \n");
				MyFIFOPrint(&fifo);
				int result = FIFOResize(&fifo, value);
				if(result == 0) {
					printf("FIFO after resizing to %d: \n", value);
					MyFIFOPrint(&fifo);
				}
				else {
				printf("Failed to resize FIFO.\n");
				}
				break;
			/******************************************************************/
			case(10)://size()
				printf("  ->FIFO AutoTest\n");
				if(AutoTest() == 1)
					printf("Tests Failed\n");
				break;
			/******************************************************************/
			default:
				break;
			/******************************************************************/
			}
		menuOption = -1;//resets the menuOption
		}
	return(0);
	}
