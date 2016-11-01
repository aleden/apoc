#include "apocmemorymanager.h"
#include "apocarray.h"
#include "apocsimpledataallocator.h"

namespace Apoc
{
  namespace MemoryManager
  {
    SimpleDataAllocator allocator;

    const Region* largestRegion = 0;
    UInt offset;

    bool Initialize()
    {
      for (UInt i = 0; i < MemoryManager::GetNumRegions(); ++i)
      {
        const MemoryManager::Region* region = MemoryManager::GetRegion(i);
	if (region->type == REGION_TYPE_USABLE)
	{
	  if (!largestRegion)
	    largestRegion = region;
	  else
#if APOC_ARCH == APOC_ARCH_X86_32
            largestRegion = region->lengthLow > largestRegion->lengthLow ? region : largestRegion;
#elif APOC_ARCH == APOC_ARCH_X86_64
            largestRegion = region->length > largestRegion->length ? region : largestRegion;
#endif
        }
      }

      // The kernel is from 100000h - 003FFFFFh, so we have to adjust largest region used to avoid overwriting it
#if APOC_ARCH == APOC_ARCH_X86_32
      if (largestRegion && (UInt)largestRegion->baseAddressLow < 0x3FFFFF)
        offset = 0x3FFFFF - (UInt)largestRegion->baseAddressLow;
#elif APOC_ARCH == APOC_ARCH_X86_64
      if (largestRegion && (UInt)largestRegion->baseAddress < 0x3FFFFF)
        offset = 0x3FFFFF - (UInt)largestRegion->baseAddress;
#endif

      return true;
    }

    static inline const Region* GetRegions()
    { return (MemoryManager::Region*)0xD00; }

    const Region* GetRegion(UInt index)
    { return GetRegions() + index; }

    UInt GetNumRegions()
    { return static_cast<UInt>(*((UInt32*)0x7bfb)); }

    void* Allocate(UInt size)
    {
#if APOC_ARCH == APOC_ARCH_X86_32
      return (void*)(largestRegion->baseAddressLow + allocator.Allocate(size) + offset);
#elif APOC_ARCH == APOC_ARCH_X86_64
      return (void*)(largestRegion->baseAddress + allocator.Allocate(size) + offset);
#endif
    }

    void Deallocate(void* memory)
    {
    }

    UInt GetRemaining()
    {
#if APOC_ARCH == APOC_ARCH_X86_32
      return largestRegion->lengthLow - allocator.GetUsedCount() - offset;
#elif APOC_ARCH == APOC_ARCH_X86_64
      return largestRegion->length - allocator.GetUsedCount() - offset;
#endif
    }
  };
} 
