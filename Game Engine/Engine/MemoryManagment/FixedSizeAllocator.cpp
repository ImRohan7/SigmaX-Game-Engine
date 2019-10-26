#include"FixedSizeAllocator.h"

FixedSizeAllocator::FixedSizeAllocator() {}

FixedSizeAllocator* FixedSizeAllocator::createFSA(void* i_ptr, size_t i_sizeOfBlock, size_t i_NumOfBlock)
{
	// Construct FSA
	FixedSizeAllocator* temp = static_cast<FixedSizeAllocator*>(i_ptr);
	temp->Initialize(i_ptr, i_sizeOfBlock, i_NumOfBlock);
	return static_cast<FixedSizeAllocator*>(i_ptr);
}

void FixedSizeAllocator::Initialize(void* i_ptr, size_t i_sizeOfBlock, size_t i_NumOfBlock)
{
	void* runner = i_ptr;

	// initialize private members	
	mSizeOfBlock = i_sizeOfBlock;
	mNumOfBitArrays = (i_NumOfBlock % (size_t)8) ? i_NumOfBlock / (size_t)8 + 1 : i_NumOfBlock / (size_t)8;
	
	// Move runner
	runner = static_cast<unsigned char*>(runner) + sizeof(FixedSizeAllocator);
	
	// Initialize BitArray
	for (unsigned int i = 0; i < mNumOfBitArrays; i++)
	{
		mByte = BitArray::Create(runner, true);
		runner = static_cast<unsigned char*>(runner) + sizeof(BitArray);
		static_cast<void*>(runner);
	}

	// Set starting point
	mStartingPoint = static_cast<unsigned char*>(runner) + sizeof(size_t);
}

void* FixedSizeAllocator::_Falloc()
{
	unsigned long Index, mask;
	int count = -1;
	unsigned char IsNonZero = 0;

	// Check for available space
	for (unsigned int i = 0; i < mNumOfBitArrays; i++)
	{
		IsNonZero = mByte[i].findFirstSet(Index);
		if (Index >= 8) { IsNonZero = 0; }
		count++;
		if (IsNonZero) { break; }
	}

	//If available then Set Bit, Count that location plus return address
	if (IsNonZero)
	{
		void * toReturn = static_cast<unsigned char*>(mStartingPoint) + (count * 8 + Index) * (mSizeOfBlock);
		// Set bit			
		mByte[count].SetBit(Index);
		return toReturn;
	}
	else
	{
		return NULL;
	}
}

void FixedSizeAllocator::_free(void* i_ptr)
{
	// Find the Bit from address
	int count = 0;
	int Index = 0;

	void* runner = mStartingPoint;

	while (i_ptr != runner)
	{
		runner = static_cast<unsigned char*>(runner) + mSizeOfBlock;
		Index++;
		if (Index >= 8) { Index = 0; count++; }
	}

	// Clear Bit
	mByte[count].ClearBit(Index);
	i_ptr = nullptr;
}

// Get
size_t FixedSizeAllocator::getSizeOfBlock() { return mSizeOfBlock; }
size_t FixedSizeAllocator::getSizeOfBitArray() { return mNumOfBitArrays; }

void* FixedSizeAllocator::getStartingPoint() {
	return static_cast<void*>(mStartingPoint);
}
