#include "apocsimpledataallocator.h"
#include "apoclinkedlist.h"

namespace Apoc
{
  UInt SimpleDataAllocator::Allocate(UInt size)
  {
    UInt address = usedCount;
    usedCount += size;
    return address;
  }

  void SimpleDataAllocator::Deallocate(UInt address)
  {
  }
}

