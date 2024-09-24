#include <stdio.h>
#include <stdlib.h>

typedef struct ArrayList {
	int *array; // dynamically allocated array
	int length; // number of items in the priority queue
	int allocationSize; // capacity of the priority queue
} ArrayList_t;

/*
• Allocate memory on the heap for the priority queue data structure.
• Allocate memory on the heap for an array containing four integers.
• Initialize the length and allocation size variables.
• Return the address of the priority queue data structure.
*/
ArrayList_t* CreateAndInitPQueue() {
	ArrayList_t *pQueue = (ArrayList_t*)malloc(sizeof(ArrayList_t));
	pQueue->array = (int*)malloc(sizeof(int) * 4);
	pQueue->allocationSize = 4;
	pQueue->length = 0;
	
	return pQueue;
}

/*
• Allocate memory on the heap for an array that is twice the size of the existing array.
• Free up the memory previously allocated to the existing array.
*/
void Resize(ArrayList_t *pQue) {
	int *newArr = (int*)malloc(sizeof(int) * pQue->allocationSize * 2);
	for(int i = 0; i < pQue->length; i++) {
		newArr[i] = pQue->array[i];
	}
	free(pQue->array);
	pQue->array = newArr;
	pQue->allocationSize *= 2;
	
	return;
}

/*
• Return 1 (true) if the priority queue is empty (i.e. has no items in it); return 0 (false) otherwise.
*/
int IsEmpty(ArrayList_t *pQue) {
	if (pQue->length == 0) {
		return 1;
	}
	
	return 0;
}

/*
• Return the size of the priority queue (i.e. the number of values in the priority queue).
*/
int GetLength(ArrayList_t *pQue) {
	return pQue->length;
}

/*
• Return the height of the max heap.
*/
int GetHeight(ArrayList_t *pQue) {
	int currIndex = pQue->length - 1;
	int height = 0;
	while(currIndex > 0) {
		currIndex = (currIndex - 1) / 2;
		height++;
	}
	
	return height;
}

int GetParentValue(ArrayList_t *pQue, int index) {
	if(index > 0) {
		return pQue->array[(index - 1) / 2];
	}
	printf("Parent does not exist.\n");
	return 0;
}

int GetLeftChildValue(ArrayList_t *pQue, int index) {
	int indexLeftChild = (2 * index) + 1;
	if(indexLeftChild > pQue->length - 1) {
		printf("Left child does not exist.\n");
		return 0;
	}
	return pQue->array[indexLeftChild];
}

int GetRightChildValue(ArrayList_t *pQue, int index) {
	int indexRightChild = (2 * index) + 2;
	if(indexRightChild > pQue->length - 1) {
		printf("Right child does not exist.\n");
		return 0;
	}
	return pQue->array[indexRightChild];
}

int GetParentIndex(int index) {
	if(index > 0) {
		return (index - 1) / 2;
	}
	printf("Parent does not exist.\n");
}

int GetLeftChildIndex(int index) {
	return (2 * index) + 1;
}

int GetRightChildIndex(int index) {
	return (2 * index) + 2;
}

/*
• Insert the new value after all equal or higher values in the priority queue.
• Reorder the values in the max heap as necessary (to maintain the max heap property).
• Resize the dynamic array as necessary.
*/
void Enqueue(ArrayList_t *pQue, int value) {
	if(pQue->length == pQue->allocationSize) {
		Resize(pQue);
	}
	
	pQue->array[pQue->length] = value;
	int currIndex = pQue->length;
	pQue->length++;
	for(int i = 0; i < GetHeight(pQue); i++) {
		if(GetParentValue(pQue, currIndex) < value) {
			//swap with parent index
			int temp = GetParentValue(pQue, currIndex);
			pQue->array[GetParentIndex(currIndex)] = value;
			pQue->array[currIndex] = temp;
			currIndex = GetParentIndex(currIndex);
		}
	}
	
	return;
}

/*
• Remove the value from the front of the priority queue.
• Reorder the values in the max heap as necessary (to maintain the max heap property).
• Return the value.
*/
int Dequeue(ArrayList_t *pQue) {
	int value = pQue->array[0];
	int currIndex = 0;
	pQue->array[0] = pQue->array[pQue->length - 1];
	pQue->length--;
	for(int i = 0; i < GetHeight(pQue); i++) {
		/*
		if(GetLeftChildValue(pQue, currIndex) > GetRightChildValue(pQue, currIndex)) {
			pQue->array[currIndex] = GetLeftChildValue(pQue, currIndex);
		}
		else {
			pQue->array[currIndex] = GetRightChildValue(pQue, currIndex);
		}
		*/
		if(GetLeftChildIndex(currIndex) < pQue->length && GetRightChildIndex(currIndex) < pQue->length) {
			//swap with greater child
			if(GetLeftChildValue(pQue, currIndex) > GetRightChildValue(pQue, currIndex) &&
			   GetLeftChildValue(pQue, currIndex) > pQue->array[currIndex]) {
				int temp = pQue->array[currIndex];
				pQue->array[currIndex] = GetLeftChildValue(pQue, currIndex);
				pQue->array[GetLeftChildIndex(currIndex)] = temp;
				//update currIndex
				currIndex = GetLeftChildIndex(currIndex);
			}
			else if(GetRightChildValue(pQue, currIndex) > GetLeftChildValue(pQue, currIndex) &&
			        GetRightChildValue(pQue, currIndex) > pQue->array[currIndex]) {
				int temp = pQue->array[currIndex];
				pQue->array[currIndex] = GetRightChildValue(pQue, currIndex);
				pQue->array[GetRightChildIndex(currIndex)] = temp;
				//update currIndex
				currIndex = GetRightChildIndex(currIndex);
			}
		}
		else if(GetLeftChildIndex(currIndex) < pQue->length) {
			if(GetLeftChildValue(pQue, currIndex) > pQue->array[currIndex]) {
				int temp = pQue->array[currIndex];
				pQue->array[currIndex] = GetLeftChildValue(pQue, currIndex);
				pQue->array[GetLeftChildIndex(currIndex)] = temp;
				//update currIndex
				currIndex = GetLeftChildIndex(currIndex);
			}
		}
	}
	
	return value;
}

/*
• Return the value from the front of the priority queue.
• Do NOT remove the value from the priority queue
*/
int Peek(ArrayList_t *pQue) {
	return pQue->array[0];
}

/*
• Print the values that are in the priority queue, starting at the front of the priority queue.
*/
void PrintPQueue(ArrayList_t *pQue) {
	
	for(int i = 0; i < pQue->length; i++) {
		printf("%d ", pQue->array[i]);
	}
	printf("\n");
	
	return;
}

int main() {
	int value;
	ArrayList_t *pQueue = CreateAndInitPQueue();
	if (IsEmpty(pQueue)) {
	printf("Priority Queue is empty.\n");
	} else {
	printf("Priority Queue is not empty.\n");
	} // Output: Priority Queue is empty.
	
	Enqueue(pQueue, 52);
	Enqueue(pQueue, 39);
	PrintPQueue(pQueue); // Output: 52 39
	
	Enqueue(pQueue, 81);
	PrintPQueue(pQueue); // Output: 81 39 52
	
	Enqueue(pQueue, 17);
	Enqueue(pQueue, 46);
	value = Peek(pQueue);
	printf("Value = %d \n", value); // Output: Value = 81
	value = GetLength(pQueue);
	printf("Length = %d \n", value); // Output: Length = 5
	value = GetHeight(pQueue);
	printf("Height = %d \n", value); // Output: Height = 2
	PrintPQueue(pQueue); // Output: 81 46 52 17 39
	
	Enqueue(pQueue, 105);
	Enqueue(pQueue, 94);
	Enqueue(pQueue, 23);
	PrintPQueue(pQueue); // Output: 105 46 94 23 39 52 81 17
	value = GetHeight(pQueue);
	printf("Height = %d \n", value); // Output: Height = 3
	
	if (IsEmpty(pQueue)) {
	printf("Priority Queue is empty.\n");
	} else {
	printf("Priority Queue is not empty.\n");
	} // Output: Priority Queue is not empty.
	
	value = Dequeue( pQueue);
	printf("Value = %d \n", value); // Output: Value = 105
	PrintPQueue(pQueue); // Output: 94 46 81 23 39 52 17
	value = GetHeight(pQueue);
	printf("Height = %d \n", value); // Output: Height = 2
	
	value = Peek(pQueue);
	printf("Value = %d \n", value); // Output: Value = 94
	value = Dequeue(pQueue);
	printf("Value = %d \n", value); // Output: Value = 94
	PrintPQueue(pQueue); // Output: 81 46 52 23 39 17
	
	value = Dequeue(pQueue);
	value = Dequeue(pQueue);
	value = GetLength(pQueue);
	printf("Length = %d \n", value); // Output: Length = 4
	value = GetHeight(pQueue);
	printf("Height = %d \n", value); // Output: Height = 2
	PrintPQueue(pQueue); // Output: 46 39 17 23
	
	value = Dequeue(pQueue);
	printf("Value = %d \n", value); // Output: Value = 46
	value = GetHeight(pQueue);
	printf("Height = %d \n", value); // Output: Height = 1
	PrintPQueue(pQueue); // Output: 39 23 17
	
	value = Dequeue(pQueue);
	printf("Value = %d \n", value); // Output: Value = 39
	value = GetLength(pQueue);
	printf("Length = %d \n", value); // Output: Length = 2
	PrintPQueue(pQueue); // Output: 23 17
	
	value = Dequeue(pQueue);
	printf("Value = %d \n", value); // Output: Value = 23
	value = GetHeight(pQueue);
	printf("Height = %d \n", value); // Output: Height = 0
	PrintPQueue(pQueue); // Output: 17
	
	value = Dequeue(pQueue);
	printf("Value = %d \n", value); // Output: Value = 17
	value = GetLength(pQueue);
	printf("Length = %d \n", value); // Output: Length = 0
	PrintPQueue(pQueue); // Output:
	
	if (IsEmpty(pQueue)) {
	printf("Priority Queue is empty.\n");
	} else {
	printf("Priority Queue is not empty.\n");
	} // Output: Priority Queue is empty.
	
	return 0;
}