#Description

( Unit test location:  SIGMA Engine/Memory Manager/Unit Tests/Unit_Test_FixedSizeAllocator.cpp )

1) Added PrintBits() method in BitArray class to make debugging easy. Method prints 8 bits of a byte.
	Location: SIGMA Engine/Memory Manager/BitArray
	File: BitArray.h
	Line: 103

2) Using _BitscanForward and _BitscanForward64 for 32 and 64 bit architecture
	Location: SIGMA Engine/Memory Manager/BitArray
	File: BitArray.h
	Line: 75-80

3) Added LOG(x) macro to display logs in Debug build (Added Preprocessor definition for Debug and Release)
	Location: SIGMA Engine/Memory Manager/Allocator
	File: Allocator.h
	Line: 8-12

4) Only Using Bitwise operators and left shift operator in BitArray class for all operations in functions.
	(Using ('&', '|', '~', '<<', '1UL', etc. ) for manipulating bits and generating results)
	Location: SIGMA Engine/Memory Manager/BitArray
	File: BitArray.h

5) Added MyString class to Engine.
	Location: SIGMA Engine/MyString

6)  Number of allocations done dynamically, not using fixed number of descriptors for Defalult Heap.
	(Max number of allocations can vary as per requirement, not limited to fixed number.)
	Location: SIGMA Engine/Memory Manager/HeapManager
	File: HeapManager.cpp
	
7)	Counting and Printing total number of blocks merged during garbage collection.
	(Helps while debuging and gives an idea of the working of garbage collector)
	Location: SIGMA Engine/Memory Manager/HeapManager
	File: HeapManager.cpp
	Line: 209
