#pragma once
#include "BitArray.h"

class FixedSizeAllocator {
	
public:
	FixedSizeAllocator();

	// Initialization
	static FixedSizeAllocator* createFSA(void* i_ptr, size_t i_sizeOfBlock, size_t i_NumOfBlock);
	void Initialize(void* i_ptr, size_t i_sizeOfBlock, size_t i_NumOfBlock);

	// Get
	size_t getSizeOfBlock();
	size_t getSizeOfBitArray();
	void* getStartingPoint();

	// Allocation and Freeing
	void* _Falloc();
	void _free(void* i_ptr);

	private:
		size_t mSizeOfBlock;	// size of each block (16, 32 , 96 etc.)
		size_t mNumOfBitArrays; // Num of BitArrays (Bytes)
		void* mStartingPoint; // Starting address of the memory to be allocated
		BitArray* mByte; // BitArray object Represents one byte per object
};