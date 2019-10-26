//#include "Allocator.h"
//#include "ConsolePrint.h"
//
//#if HEAP_DEBUG == 1
////#define LOG(x) std::cout << x << std::endl
//#define LOG(x) DEBUG_PRINT(x);
//#elif defined(HEAP_RELEASE)
//#define LOG(x)
//#endif
//
//// malloc
//void * __cdecl malloc(size_t i_size)
//{ 
//	LOG("Overloaded malloc() Called");
//	void * pReturn=nullptr;
//	// Find FSA
//	FixedSizeAllocator * pFSA = FindFixedSizeAllocator(i_size);
//	if (pFSA) {
//		pReturn = pFSA->_Falloc();
//
//#ifdef _SHOW_LOGS
//		std::cout << "malloc From Fixed with size: " << i_size << std::endl;
//#endif // _SHOW_LOGS
//	}
//	
//	// if no FSA available or there was one and it is full
//	if (pReturn == nullptr) {
//		pReturn = HeapManagerProxy::alloc(getHeap(), i_size);
//
//#ifdef _SHOW_LOGS
//		std::cout << "malloc From Default with size: " << i_size << std::endl;
//#endif	// _SHOW_LOGS
//	}
//
//	return (void*)pReturn;
//}
//
//void __cdecl free(void * i_ptr) 
//{
//	LOG("Overloaded free() called");
//	// Find FSA
//	FixedSizeAllocator* pFSA = FindFixedSizeAllocator(i_ptr);
//	// If FSA==NULL then go check for Default Heap
//	if (pFSA){
//		LOG("Calling free() from FSA");
//		pFSA->_free(i_ptr);
//	}
//	else{
//		LOG("Calling free from DefaultHeap");
//		HeapManagerProxy::_free(getHeap(),i_ptr);
//	}
//}
//
//// New
//void *operator new(size_t i_size)
//{
//	LOG("Overloaded new called");
//	void * pReturn = nullptr;
//	FixedSizeAllocator * pFSA = FindFixedSizeAllocator(i_size);
//	if (pFSA) {
//		pReturn = pFSA->_Falloc();
//
//#ifdef _SHOW_LOGS
//		std::cout << "new From Fixed with size: " << i_size << std::endl;
//#endif	// _SHOW_LOGS
//	}
//
//	// if no FSA available or there was one and it is full
//	if (pReturn == nullptr) {
//		pReturn = HeapManagerProxy::alloc(getHeap(), i_size);
//
//#ifdef _SHOW_LOGS
//		std::cout << "new From Default with size: " << i_size << std::endl;
//#endif // _SHOW_LOGS
//	}
//	return (void*)pReturn;
//
//}
//
//// New[]
//void *operator new[](size_t i_size) 
//{
//	LOG("Overaloaded new[] called");  
//	void * pReturn = nullptr;
//	FixedSizeAllocator * pFSA = FindFixedSizeAllocator(i_size);
//	if (pFSA) {
//		pReturn = pFSA->_Falloc();
//
//#ifdef _SHOW_LOGS
//		std::cout << "New[] From Fixed with size: " << i_size << std::endl;
//#endif // _SHOW_LOGS
//	}
//
//	// if no FSA available or there was one and it is full
//	if (pReturn == nullptr) {
//		pReturn = HeapManagerProxy::alloc(getHeap(), i_size);
//
//#ifdef _SHOW_LOGS
//		std::cout << "new[] From Default with size: " << i_size << std::endl;
//#endif // _SHOW_LOGS
//	}
//	return (void*)pReturn;
//}
//
//// Delete
//void operator delete(void* i_ptr)
//{
//	LOG("Overaloaded Delete called");
//// Find FSA
//	FixedSizeAllocator* pFSA = FindFixedSizeAllocator(i_ptr);
//
//	// If FSA==NULL then go check for Default Heap
//	if (pFSA) {
//		LOG("calling _free() from FSA");
//		pFSA->_free(i_ptr);
//	}
//	else {
//		LOG("calling _free() from Default Heap");
//		HeapManagerProxy::_free(getHeap(), i_ptr);
//	}
//}
//
//// Delete[]
//void operator delete[](void* i_ptr)
//{
//	LOG("Overaloaded Delete[] called");
//	// Find FSA
//	FixedSizeAllocator* pFSA = FindFixedSizeAllocator(i_ptr);
//	// If FSA==NULL then go check for Default Heap
//	if (pFSA) {
//		LOG("calling _free() from FSA");
//		pFSA->_free(i_ptr);
//	}
//	else {
//		LOG("calling _free() from Default Heap");
//		HeapManagerProxy::_free(getHeap(), i_ptr);
//	}}
//
//// Aligned new
//void *operator new(size_t i_size, NewAlignment i_align)
//{
//		LOG("new with alignment called");
//	void *toBeReturned;
//	switch (i_align)
//	{
//		case NEW_ALIGN_16:
//		case NEW_ALIGN_32:
//
//			LOG("Alignment case: 16,32");
//			toBeReturned = HeapManagerProxy::alloc(getHeap(), i_size, i_align);
//			return toBeReturned;
//		
//		default:
//			LOG("Alignment case: Default");
//			toBeReturned = HeapManagerProxy::alloc(getHeap(), i_size, 4);
//			return toBeReturned;
//	}
//}
//
//// Aligned delete
//void operator delete(void * i_ptr, NewAlignment i_align) 
//{
//	LOG("NOOOO....Aligned delete called");
//	std::cout << "Should not happen.\n";
//	if (i_ptr != 0)
//	{
//		HeapManagerProxy::_free(getHeap(), i_ptr);
//	}
//}
//
////Not Using just for exp
//void *operator new(size_t size,int x) 
//{
//	LOG("Mirracle");	
//	return malloc(size*x);
//}
