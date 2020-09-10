#pragma once
#include<iostream>

#define BLOCK_SIZE 8

struct Block {
	size_t size;
	bool IsFree;
};

/* IMP to take constants to make sure 
* we dont change the underlying value pointed by the pointers.
*/
static unsigned const char* head;	 // Head of the Heap (will always point to the 1st Block of the heap)
static unsigned const char* tail;	// Bottom of the Heap (will always point to the Last Block of the heap)
static unsigned const char* current; // Points to the current free block while allocating
static size_t maxCapasity;			// maximum capacity of the HeapManager
static size_t LargestAvailable;		// Largest free block 
static bool IsFull = false;		//The first allocation round. Set it to true, when current reaches end of the heap
								//When full current will be the address after the last block ALWAYS

class HeapManager {

public:

	static HeapManager* create(void*, size_t, unsigned int);
	void	_Destroy();

	void* alloc(size_t);
	void* alloc(size_t, unsigned int);

	bool _free(void*);
	void _collect();

	bool	_IsAllocated(void * i_ptr) const;
	bool	_Contains(void * i_ptr) const;

	size_t			_GetLargestFreeBlock() const;
	size_t			_GetTotalFreeMemory() const;

	void ShowMyOutstandingAllocations() const;
	void ShowMyFreeBlocks() const;
	
};
