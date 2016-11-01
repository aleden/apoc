#pragma once
#include "apocconfig.h"
#include "apoctypes.h"

namespace Apoc
{
  namespace MemoryManager
  {
#if APOC_ARCH == APOC_ARCH_X86_32
    #pragma pack(push, 1)
    struct Region
    {
      UInt32 baseAddressLow;
      UInt32 baseAddressHigh;
      UInt32 lengthLow;
      UInt32 lengthHigh;
      UInt32 type;
      UInt32 extendedAttributes;
    };
    #pragma pack (pop)
#elif APOC_ARCH == APOC_ARCH_X86_64
    #pragma pack(push, 1)
    struct Region
    {
      UInt64 baseAddress;
      UInt64 length;
      UInt32 type;
      UInt32 extendedAttributes;
    };
    #pragma pack (pop)
#endif

    enum REGION_TYPE
    {
      REGION_TYPE_UNKNOWN,
      REGION_TYPE_USABLE,
      REGION_TYPE_RESERVED,
      REGION_TYPE_ACPI_RECLAIMABLE,
      REGION_TYPE_ACPI_NVS,
      REGION_TYPE_BAD
    };

    bool Initialize();

    const Region* GetRegion(UInt index);
    UInt GetNumRegions();

    UInt GetRemaining();
    void* Allocate(UInt);
    void Deallocate(void*);
  };
}
