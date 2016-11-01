#pragma once
#include "apoccommon.h"
#include "apocstream.h"

namespace Apoc
{
  namespace DiskIO
  {
    //! Size of a sector
    const UInt SECTOR_SIZE = 512;

    struct Sector
    {
      Byte data[SECTOR_SIZE];
    };

    //! @param size Number of sectors to read (SECTOR_SIZE * size bytes)
    void Read(UInt sectorIndex, Sector* destination, UInt size);

    //! @param size Number of sectors to write (SECTOR_SIZE * size bytes)
    void Write(UInt sectorIndex, Sector* source, UInt size);

    UInt GetSectorCount();

    Stream* CreateStream();
  }
}

