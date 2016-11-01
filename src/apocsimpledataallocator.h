#pragma once
#include "apoccommon.h"

namespace Apoc
{
  class SimpleDataAllocator
  {
    UInt usedCount;

  public:
    inline SimpleDataAllocator() : usedCount(0) {}

    //! Returns the address to the allocation
    UInt Allocate(UInt size);

    //! \param address The address of the allocation to be deallocated
    void Deallocate(UInt address);

    inline UInt GetUsedCount()
    { return usedCount; }
  };
}
