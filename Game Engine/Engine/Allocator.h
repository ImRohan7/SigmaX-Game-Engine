//#pragma once
//#include "Windows.h"
//#include <assert.h>
//#include "iostream"
//#include "MemorySystem.h"
//#include "HeapManagerProxy.h"
//
//#if HEAP_DEBUG == 1
//#define LOG(x) std::cout << x << std::endl
//#elif defined(HEAP_RELEASE)
//#define LOG(x)
//#endif
//
//#ifndef _SHOW_LOGS
//#define _SHOW_LOGS
//#endif
//
//enum NewAlignment
//{
//	NEW_ALIGN_DEFAULT,
//	NEW_ALIGN_16 = 16,
//	NEW_ALIGN_32 = 32
//};
//
//// new, delete
//void *operator new(size_t);
//void operator delete(void*);
//
//// malloc, free
//void * __cdecl malloc(size_t);
//void __cdecl free(void*);
//
//// new[], delete[]
//void *operator new[](size_t);
//void operator delete[](void*);
//
//// Aligned new, delete
//void *operator new(size_t, NewAlignment);
//void operator delete(void*, NewAlignment);
//
////  Not using..Exprimental only
//void *operator new(size_t, int);