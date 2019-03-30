
// This was my own version of unit test

#include <iostream>
#include <windows.h>
#include "HeapManagerProxy.h"
#include "assert.h"
//#include "HeapManager_UnitTest.cpp"

//
//int main()
//{
//
//	using namespace HeapManagerProxy;
//
//	const size_t 		sizeHeap = 500;// 1024 * 1024;
//	const unsigned int 	numDescriptors = 2048;
//
//	// Allocate memory for my test heap.
//	void * pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
//	assert(pHeapMemory);
//
//	// Create a heap manager for my test heap.
//	HeapManager * pHeapManager = CreateHeapManager(pHeapMemory, sizeHeap, numDescriptors);
//	assert(pHeapManager);
//
//	//Alignments
//	const unsigned int	alignments[] = { 4, 8, 16, 32, 64 };
//	const unsigned int	index = rand() % (sizeof(alignments) / sizeof(alignments[0]));
//	const unsigned int	alignment = alignments[0];
//
//	size_t sizeAlloc =15;
//
//	void * _pt1 = alloc(pHeapManager, 97);
//	assert(_pt1);
//
//	void * _pt2 = alloc(pHeapManager, 103, alignment);
//	assert(_pt2);
//	assert((reinterpret_cast<uintptr_t>(_pt2) & (alignment - 1)) == 0);
//
//	void * _pt3 = alloc(pHeapManager, 90, alignment);
//	assert(_pt3);
//	assert((reinterpret_cast<uintptr_t>(_pt3) & (alignment - 1)) == 0);
//
//
//	bool test_Contain = Contains(pHeapManager,(unsigned char*)_pt1 + 491);
//
//
//	free(pHeapManager, _pt2);
//	free(pHeapManager, _pt3);
//	ShowFreeBlocks(pHeapManager);
//	
//
//
//	void * _pt4 = alloc(pHeapManager, 44, alignment);
//	assert(_pt4);
//	assert((reinterpret_cast<uintptr_t>(_pt3) & (alignment - 1)) == 0);
//	
//	
//	Collect(pHeapManager);
//	
//
//ShowOutstandingAllocations(pHeapManager);
//
//	void * _pt5 = alloc(pHeapManager, 10, alignment);
//	assert(_pt5);
//	assert((reinterpret_cast<uintptr_t>(_pt5) & (alignment - 1)) == 0);
//
//	free(pHeapManager, _pt5);
//
//	ShowFreeBlocks(pHeapManager);
//	ShowOutstandingAllocations(pHeapManager);
//
//	bool test = IsAllocated(pHeapManager, _pt1);
//	std::cout << std::endl << test;
//	test = IsAllocated(pHeapManager, _pt2);
//	std::cout << std::endl << test;
//	test = IsAllocated(pHeapManager, _pt3);
//	std::cout << std::endl << test;
//	test = IsAllocated(pHeapManager, _pt4);
//	std::cout << std::endl << test;
//	test = IsAllocated(pHeapManager, _pt5);
//	std::cout << std::endl << test;
//
//	Collect(pHeapManager);
//	ShowFreeBlocks(pHeapManager);
//	ShowOutstandingAllocations(pHeapManager);
//	size_t Largest = GetLargestFreeBlock(pHeapManager);
//	std::cout << std::endl << "Largest : "<<Largest;
//
//	size_t TotalFree = GetTotalFreeMemory(pHeapManager);
//	std::cout << std::endl << "Total Free : " << TotalFree;
//
////	free(pHeapManager,_pt1);
//	free(pHeapManager, _pt2);
//
//	
//	ShowFreeBlocks(pHeapManager);
//
//
//	
//
//	getchar();
//	return 0;
//}