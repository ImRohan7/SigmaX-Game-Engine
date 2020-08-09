#include "MemorySystem.h"

FSAInitdata FSAdesci[3];

// Default Heap and FSA
HeapManager* pHeapDefault;
FixedSizeAllocator* FSA[3];

// Not actually using..Just for info
size_t sizeFSA = 48000;
size_t sizeBitArray = 88; // 13 + 25 + 50
void* BeginFSA;
void* EndFSA;
void* BeginHeap;

HeapManager* getHeap() {
	return pHeapDefault;
}

void InitializeFSAdata() {

	FSAdesci[0].sizeBlock = 16;
	FSAdesci[0].numBlocks = 100;

	FSAdesci[1].sizeBlock = 32;
	FSAdesci[1].numBlocks = 200;

	FSAdesci[2].sizeBlock = 96;
	FSAdesci[2].numBlocks = 400;
}

bool InitializeMemorySystem(void * i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors)
{
	BeginFSA = i_pHeapMemory;
	EndFSA = static_cast<unsigned char*>(i_pHeapMemory) + sizeFSA;

	void * RunBoy = i_pHeapMemory;

	// Create FSA data
	InitializeFSAdata();

	// Initialize FSA
	for (int i = 0; i < 3; i++) {
		FSA[i] = FixedSizeAllocator::createFSA(RunBoy, FSAdesci[i].sizeBlock, FSAdesci[i].numBlocks); // create FSA and BitArray
		
		RunBoy = static_cast<unsigned char*>(RunBoy) + FSAdesci[i].sizeBlock * FSAdesci[i].numBlocks + FSAdesci[i].numBlocks / 8 + 1 + sizeof(FixedSizeAllocator);
		static_cast<unsigned char*>(RunBoy);
	}

	void* forHeap = static_cast<unsigned char*>(i_pHeapMemory) + 50000;
	BeginHeap = forHeap;

	// Initialize Heap Manager
	pHeapDefault = HeapManagerProxy::CreateHeapManager(forHeap, i_sizeHeapMemory - 50000, i_OptionalNumDescriptors);
	return true;
}

FixedSizeAllocator* FindFixedSizeAllocator(size_t i_size)
{
	//	return FSA[0];
	if (i_size >= 0 && i_size <= 16) {
		return FSA[0];
	}
	else if (i_size >= 17 && i_size <= 32) { return FSA[1]; }
	else if (i_size >= 33 && i_size <= 96) { return FSA[2]; }
	else
	{
		return NULL;
	}
}

FixedSizeAllocator* FindFixedSizeAllocator(void* i_ptr)
{
	//	return FSA[0];
	if (i_ptr >= FSA[0]->getStartingPoint() && i_ptr < FSA[1]->getStartingPoint()) {
		return FSA[0];
	}
	else if (i_ptr >= FSA[1]->getStartingPoint() && i_ptr < FSA[2]->getStartingPoint()) {
		 return FSA[1];
	}
	else if (i_ptr >= FSA[2]->getStartingPoint() && i_ptr < pHeapDefault) {
		return FSA[2]; 
	}
	else
	{
		return NULL;
	}
}

void Collect(){
	HeapManagerProxy::Collect(getHeap());
}

void DestroyMemorySystem() {
	FSA[0] = NULL;
	FSA[1] = NULL;
	FSA[2] = NULL;
	HeapManagerProxy::Destroy(getHeap());
}

