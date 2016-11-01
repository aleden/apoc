#pragma once

namespace Apoc
{
  class VirtualMemorySystem
  {
    public:
      virtual UInt GetPageSize() = 0;
      virtual void MapPages(void* virtualAddress, void* physicalAddress, UInt pageCount);
      virtual void MapPage(void* virtualAddress, void* physicalAddress);
  };
}
