#pragma once
#include "apocconfig.h"
#include "apoctypes.h"
#include "apocmemorymanager.h"

#if APOC_ARCH == APOC_ARCH_X86_32
inline void* operator new (unsigned int size)
#elif APOC_ARCH == APOC_ARCH_X86_64
inline void* operator new (long unsigned int size)
#endif
{ return Apoc::MemoryManager::Allocate(size); }

inline void operator delete (void* address)
{ return Apoc::MemoryManager::Deallocate(address); }

#if APOC_ARCH == APOC_ARCH_X86_32
inline void* operator new [] (unsigned int size)
#elif APOC_ARCH == APOC_ARCH_X86_64
inline void* operator new [] (long unsigned int size)
#endif
{ return Apoc::MemoryManager::Allocate(size); }

inline void operator delete [] (void* address)
{ return Apoc::MemoryManager::Deallocate(address); }
