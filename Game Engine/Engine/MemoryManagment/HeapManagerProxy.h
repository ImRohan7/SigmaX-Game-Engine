#ifndef __HEAP_MANAGER_PROXY_H
#define __HEAP_MANAGER_PROXY_H

#include <stdint.h>

class HeapManager;

namespace HeapManagerProxy
{
	HeapManager *	CreateHeapManager(void * i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors);
	void			Destroy(HeapManager * i_pManager);

	void *			alloc(HeapManager * i_pManager, size_t i_size);
	void *			alloc(HeapManager * i_pManager, size_t i_size, unsigned int i_alignment);
	bool			_free(HeapManager * i_pManager, void * i_ptr);

	void			Collect(HeapManager * i_pManager);

	bool			Contains(HeapManager * i_pManager, void * i_ptr);
	bool			IsAllocated(HeapManager * i_pManager, void * i_ptr);

	size_t			GetLargestFreeBlock(HeapManager * i_pManager);
	size_t			GetTotalFreeMemory(HeapManager * i_pManager);

	void			ShowFreeBlocks(HeapManager * i_pManager);	
	void			ShowOutstandingAllocations(HeapManager * i_pManager);

} // namespace HeapManagerProxy
#endif // __HEAP_MANAGER_PROXY_H