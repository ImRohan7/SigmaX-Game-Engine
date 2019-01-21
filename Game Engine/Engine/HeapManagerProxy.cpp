#include "HeapManagerProxy.h"
#include <assert.h>
#include <stdio.h>
#include "HeapManager.h"

namespace HeapManagerProxy
{

	HeapManager * CreateHeapManager(void * i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors)
	{
		return HeapManager::create(i_pMemory, i_sizeMemory, i_numDescriptors);
	}

	void Destroy(HeapManager * i_pManager)
	{
		assert(i_pManager);

		i_pManager->_Destroy();
	}

	void * alloc(HeapManager * i_pManager, size_t i_size)
	{
		
		assert(i_pManager);
		return i_pManager->alloc(i_size);	
	}

	void * alloc(HeapManager * i_pManager, size_t i_size, unsigned int i_alignment)
	{
		assert(i_pManager);
		
		return i_pManager->alloc(i_size, i_alignment);
	}

	bool _free(HeapManager * i_pManager, void * i_ptr)
	{
		assert(i_pManager);

		return i_pManager->_free(i_ptr);
	}

	void Collect(HeapManager * i_pManager)
	{
		assert(i_pManager);
		i_pManager->_collect();
	}

	bool Contains(HeapManager * i_pManager, void * i_ptr)
	{
		assert(i_pManager);
		return i_pManager->_Contains(i_ptr);
	}

	bool IsAllocated(HeapManager * i_pManager, void * i_ptr)
	{
		assert(i_pManager);
		return i_pManager->_IsAllocated(i_ptr);
	}

	size_t GetLargestFreeBlock(HeapManager * i_pManager)
	{
		assert(i_pManager);
		return i_pManager->_GetLargestFreeBlock();
	}

	size_t GetTotalFreeMemory(HeapManager * i_pManager)
	{
		assert(i_pManager);
		return i_pManager->_GetTotalFreeMemory();
	}

	void ShowFreeBlocks(HeapManager * i_pManager)
	{
		assert(i_pManager);

		i_pManager->ShowMyFreeBlocks();
	}

	void ShowOutstandingAllocations(HeapManager * i_pManager)
	{
		assert(i_pManager);
		i_pManager->ShowMyOutstandingAllocations();

/*
#ifdef __TRACK_ALLOCATIONS
		i_pManager->ShowOutstandingAllocations();
#else
		printf("HeapManager compiled without __TRACK_ALLOCATIONS defined.\n");
#endif*/

	}

} // namespace HeapManagerProxy
