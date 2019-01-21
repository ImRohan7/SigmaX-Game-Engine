#pragma once
#include "HeapManagerProxy.h"
#include "FixedSizeAllocator.h"

// FSA Data
struct FSAInitdata {
	size_t sizeBlock;
	size_t numBlocks;
};

void InitializeFSAdata();

// InitializeMemorySystem - initialize your memory system including your HeapManager and some FixedSizeAllocators
bool InitializeMemorySystem(void * i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors);

// Find FS allocator by size
FixedSizeAllocator* FindFixedSizeAllocator(size_t i_size);
// Find FS allocator by address
FixedSizeAllocator* FindFixedSizeAllocator(void* i_ptr);

// Get
HeapManager* getHeap();

// Collect - coalesce free blocks in attempt to create larger blocks
void Collect();

// DestroyMemorySystem - destroy your memory systems
void DestroyMemorySystem();

