#include"HeapManager.h"
#include <assert.h>
#include <stdio.h>

#ifndef _SHOW_LOGS
#define _SHOW_LOGS
#endif

	HeapManager* HeapManager::create(void * i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors)
	{
			head = static_cast<unsigned char*>(i_pMemory);	//Set head to the begining of the heap
			tail = static_cast<unsigned char*>(i_pMemory) + i_sizeMemory - 1; // Last adrress of the heap
			current = static_cast<unsigned char*>(i_pMemory);
			maxCapasity = i_sizeMemory;
			Block* _temp = static_cast<Block*>(i_pMemory);
			_temp->size = i_sizeMemory;
			_temp->IsFree = true;

			//First removing the constantness and then converting the pointer type to HeapManger
			return reinterpret_cast<HeapManager*>(const_cast<unsigned char*>(current));
	}

	void HeapManager::_Destroy() 
	{
		head = NULL;
		tail = NULL;
		current = NULL;
	}
	
	void* HeapManager::alloc(size_t i_size)
	{
		if (i_size > maxCapasity - 64) { return NULL; }  // Ooops ! Can't allocate such a huge block.
		if (const_cast<unsigned char*>(current) + BLOCK_SIZE + i_size > tail) { IsFull = true; } //First round complete set IsFull to true
		
		if (!IsFull)		//If the first round is not complete
		{
			Block * _temp = reinterpret_cast<Block*>(const_cast<unsigned char*>(current));
			
// Following line left undeleted purposely to identify the difference between reinterpret cast and const_cast
//Block* _temp = const_cast<Block*>(current);	//This will not compile
			
			_temp->size = i_size;
			_temp->IsFree = false;

			void* toBeReturned = reinterpret_cast<unsigned char*>(_temp) + BLOCK_SIZE;

			current = static_cast<unsigned char*>(toBeReturned) + _temp->size;

			//unsigned char* c = (unsigned char*)current; //Filling with an Identifier for detecting Visually
			//*c = 'A';

			return static_cast<void*>(toBeReturned);
		}

		else //First fit
		{
			Block* _fit = reinterpret_cast<Block*>(const_cast<unsigned char*>(head));;
#ifdef _SHOW_LOGS
			std::cout << "After full";
#endif // _SHOW_LOGS

			do {
				if (_fit->IsFree == true && _fit->size >= i_size)						//Fit the new block in the free one
				{
					_fit->IsFree = false;
					return (void*)((char*)_fit+BLOCK_SIZE);
				}

				_fit = (Block*)((unsigned char*)_fit + BLOCK_SIZE + _fit->size);
			} while (_fit!=(Block*)current);

			return NULL;	//Returns null if no space
		}

	}

	void* HeapManager::alloc(size_t i_size, unsigned int i_alignment) 
	{
		if (i_size > maxCapasity - 64) { return NULL; }   // Ooops ! Can't allocate such a huge block.
		if ((unsigned char*)current + BLOCK_SIZE + i_size > tail) { IsFull = true; } //First round complete

		if (!IsFull)
		{
			void* pPtr = (unsigned char*)current + BLOCK_SIZE;  //Making size for Block Descriptor (Current+8)

			if ((reinterpret_cast<uintptr_t>(pPtr) & (i_alignment - 1)) == 0)  //Check if it's already aligned
			{
				return alloc(i_size);
			}

			else //Add padding and call malloc()
			{
				pPtr = (unsigned char*)pPtr + BLOCK_SIZE; //Adding size for Pad-Block Descriptor (current+16)

				unsigned int padding_size = i_alignment - (reinterpret_cast<uintptr_t>(pPtr) % i_alignment); //Calculate Padding

				Block* Pad = (Block*)current;				//Initializing padding block
				Pad->IsFree = true;
				Pad->size = (size_t)padding_size;

				current = (unsigned char*)current + (unsigned int)Pad->size + BLOCK_SIZE;

				//	return NULL;
				return alloc(i_size);

			}
		}
		else			//Only assigns if the block size is greater than 200 
		{
			Block* _fit = (Block*)head;
#ifdef _SHOW_LOGS
			std::cout << "\nAfter full Aligned";
#endif // _SHOW_LOGS
			
			do {
				if (_fit->IsFree == true && _fit->size >= i_size && _fit->size >= 200)						//Find a free block
				{
					void* _toBeChecked = (void*)((unsigned char*)_fit + BLOCK_SIZE);
					if ((reinterpret_cast<uintptr_t>(_toBeChecked) & (i_alignment - 1)) == 0)  //Check if it's already aligned
					{
						_fit->IsFree = false;
						return (void*)(_toBeChecked);
					}	
					else
					{
						void* _new = (void*)((unsigned char*)_toBeChecked + (BLOCK_SIZE));

						unsigned int padding_size = i_alignment - (reinterpret_cast<uintptr_t>(_new) % i_alignment); //Calculate Padding

						Block* _Aligned = (Block*)((unsigned char*)_new + padding_size - BLOCK_SIZE);

						_Aligned->IsFree = false;
						_Aligned->size = _fit->size - padding_size - BLOCK_SIZE;

						_fit->IsFree = true;
						_fit->size = padding_size;

						return (void*)((unsigned char*)_Aligned + BLOCK_SIZE);
					}
					
				}

				_fit = (Block*)((unsigned char*)_fit + BLOCK_SIZE + _fit->size);
			} while (_fit != (Block*)current);

			return NULL;
		}
	}

	bool HeapManager::_free(void* i_ptr)
	{
		assert(head);
		assert(i_ptr);
		//TO DO: Check if it's allocated, If not return False

		Block* _temp = (Block*)((unsigned char*)i_ptr - BLOCK_SIZE);
		_temp->IsFree = true;
		
	//	i_ptr = NULL; //Set NULL to the pointer allocated to user

		return true;
	}

	void HeapManager::_collect()
	{
		unsigned int totalMerged=0;  //Keep track of the number of blocks merged
		bool KeepItClean = true;
		bool IsMerged = false;

		Block* _prev = (Block*)head;
		Block* _cur = (Block*)((unsigned char*)_prev + _prev->size + BLOCK_SIZE);

		do {
			if (_prev->IsFree == true && _cur->IsFree == true)	// Check for abutting blocks
			{
				//Merging blocks
				_prev->size += BLOCK_SIZE + _cur->size;
				_cur->size = NULL;
				_cur = (Block*)((unsigned char*)_prev + _prev->size + BLOCK_SIZE);
				totalMerged++;
				IsMerged = true;
			}
		
			//Changing only if _cur is not at the end
			if (reinterpret_cast<uintptr_t>(_cur) < reinterpret_cast<uintptr_t>(current))
			{
				_prev = (Block*)_cur;
				_cur = (Block*)((unsigned char*)_cur + _cur->size + BLOCK_SIZE);
			}

			//Check if _cur reaches the end

			if (reinterpret_cast<uintptr_t>(_cur) >= reinterpret_cast<uintptr_t>(current))
			{	//If no merge occured then exit
				if (IsMerged == false) 
				{
					KeepItClean = false;
					break;
				}
				else
				{
					//Again starting from the top
					_prev = (Block*)head;
					_cur = (Block*)((unsigned char*)_prev + _prev->size + BLOCK_SIZE);
					IsMerged = false;
				}
			}
		} while (KeepItClean);
		std::cout << "\nDuring Garbage Collection Blocks Merged : " << totalMerged << std::endl;
	}

	bool HeapManager::_IsAllocated(void * i_ptr) const
	{
		assert(head);
		void* _temp = (void*)i_ptr;

		//Block* prev = (Block*)head;
		Block* cur = (Block*)head;
		
		do {
			if (((char*)cur + cur->size + BLOCK_SIZE) > _temp)
			{
				if (cur->IsFree == false)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			cur = (Block*)((unsigned char*)cur + cur->size + BLOCK_SIZE);
		} while (cur != (Block*)current);
		return false;
	}

	bool HeapManager::_Contains(void * i_ptr) const		//Check between head and tail
	{
		if (i_ptr >= head && i_ptr <= tail) { return true; }
		return false;
	}

	size_t	HeapManager::_GetLargestFreeBlock() const
	{
		size_t largest=0;
		Block* cur = (Block*)head;

		do {
			if (cur->IsFree && cur->size > largest)
			{
				largest = cur->size;
			}
			cur = (Block*)((unsigned char*)cur + cur->size + BLOCK_SIZE);
		} while (cur != (Block*)current);

//Check if the 1st round is not complete and current is greater than the Largest
		if ((size_t)(reinterpret_cast<uintptr_t>(tail) - reinterpret_cast<uintptr_t>(current)) > largest) //If yes then change largest to the current size
		{
			largest = (size_t)(reinterpret_cast<uintptr_t>(tail) - reinterpret_cast<uintptr_t>(current));
			return largest;
		}
		return largest;
	}

	size_t	HeapManager::_GetTotalFreeMemory() const
	{
		size_t _freeCount = 0;
		Block* cur = (Block*)head;

		do {
			if (cur->IsFree)
			{
				_freeCount += cur->size;
			}
			cur = (Block*)((unsigned char*)cur + cur->size + BLOCK_SIZE);
		} while (cur != (Block*)current);

		//Count the free memory between current and tail
		_freeCount += (size_t)(reinterpret_cast<uintptr_t>(tail) - reinterpret_cast<uintptr_t>(current));

		return _freeCount;
	}

	void HeapManager::ShowMyOutstandingAllocations() const
	{
		assert(head);
		std::cout << std::endl << "\nAllocated Blocks: \n";

		Block* cur = (Block*)head;
		do {
			if (!cur->IsFree)
			{
				std::cout << "Block:  " << (void*)((unsigned char*)cur + BLOCK_SIZE) << "\tDecimal: " << reinterpret_cast<uintptr_t>((unsigned char*)cur + BLOCK_SIZE)
					<< "\tSIZE:  " << cur->size << std::endl;
			}
			cur = (Block*)((unsigned char*)cur + cur->size + BLOCK_SIZE);
			
		} while (cur!=(Block*)current);
	}

	void HeapManager::ShowMyFreeBlocks() const
	{
		assert(head);
		std::cout << std::endl << "\nFree Blocks: \n";
		
		Block* cur = (Block*)head;
		do {
			if (cur->IsFree)
			{
				std::cout << "Block:  " << (void*)((unsigned char*)cur + BLOCK_SIZE) << "\tDecimal: " << reinterpret_cast<uintptr_t>((unsigned char*)cur + BLOCK_SIZE)
					<< "\tSIZE:  " << cur->size << std::endl;
			}
			cur = (Block*)((unsigned char*)cur + cur->size + BLOCK_SIZE);
		} while (cur != (Block*)current);
	}
