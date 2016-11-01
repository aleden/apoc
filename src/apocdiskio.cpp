#include "apocdiskio.h"
#include "apocmath.h"
#include "apocalgorithms.h"
#include "apocassert.h"
#include "x86/apocx86.h"

namespace Apoc
{
  namespace DiskIO
  {
    const UInt IDE_BSY = 0x80;
    const UInt IDE_DRDY = 0x40;
    const UInt IDE_DF = 0x20;
    const UInt IDE_ERR = 0x01;
    const Int diskno = 0;

    class DiskStream : public Stream
    {
      UInt position;

    public:
      inline DiskStream(UInt position = 0) : position(position) {}

      inline Stream* Clone()
      { return new DiskStream(position); }

      UInt Write(const Byte* source, UInt count = 1)
      {
        UInt sectorIndex = Math::Round(static_cast<Float>(position) / static_cast<Float>(sizeof(Sector)));
        UInt sectorCount = Math::Ceil(static_cast<Float>(count) / static_cast<Float>(sizeof(Sector)));
        UInt sectorOffset = position % sizeof(Sector);

        Sector* buffer = new Sector[sectorCount];
        DiskIO::Read(sectorIndex, buffer, sectorCount);
	Copy(source, source + count, (Byte*)buffer + sectorOffset);
	DiskIO::Write(sectorIndex, buffer, sectorCount);
        delete [] buffer;

        position += count;
        return count;
      }

      void Flush()
      {
      }

      UInt Read(Byte* out, UInt count)
      {
        UInt sectorIndex = Math::Round(static_cast<Float>(position) / static_cast<Float>(sizeof(Sector)));
        UInt sectorCount = Math::Ceil(static_cast<Float>(count) / static_cast<Float>(sizeof(Sector)));
        UInt sectorOffset = position % sizeof(Sector);

        Sector* buffer = new Sector[sectorCount];
        DiskIO::Read(sectorIndex, buffer, sectorCount);
	Copy((Byte*)buffer + sectorOffset, (Byte*)buffer + sectorOffset + count, out);
        delete [] buffer;

        position += count;
        return count;
      }

      virtual UInt GetSize() const
      { return GetSectorCount() * sizeof(Sector); }

      virtual UInt GetPosition()
      { return position; }

      virtual UInt Jump(UInt elementCount)
      { return position = elementCount; }

      virtual Int Seek(Int elementOffset)
      {
        Int move = Maximum(-static_cast<Int>(position), elementOffset);
	position += move;
        return move;
      }
    };

    static int ide_wait_ready(bool check_error)
    {
      int r;

      while (((r = X86::INB(0x1F7)) & (IDE_BSY|IDE_DRDY)) != IDE_DRDY)
        /* do nothing */;

      if (check_error && (r & (IDE_DF|IDE_ERR)) != 0)
        return -1;
      return 0;
    }

    int ide_read(UInt32 secno, void *dst, UInt nsecs)
    {
      int r;

      ASSERT(nsecs <= 256);

      ide_wait_ready(0);

      X86::OUTB(0x1F2, nsecs);
      X86::OUTB(0x1F3, secno & 0xFF);
      X86::OUTB(0x1F4, (secno >> 8) & 0xFF);
      X86::OUTB(0x1F5, (secno >> 16) & 0xFF);
      X86::OUTB(0x1F6, 0xE0 | ((diskno&1)<<4) | ((secno>>24)&0x0F));
      X86::OUTB(0x1F7, 0x20);	// CMD 0x20 means read sector

      for (; nsecs > 0; nsecs--, dst = ((UInt8*)dst + SECTOR_SIZE))
      {
        if ((r = ide_wait_ready(1)) < 0)
          return r;
        X86::INSL(0x1F0, dst, SECTOR_SIZE/4);
      }
      return 0;
    }

    int ide_write(UInt secno, const void *src, UInt nsecs)
    {
      int r;

      ASSERT(nsecs <= 256);

      ide_wait_ready(0);

      X86::OUTB(0x1F2, nsecs);
      X86::OUTB(0x1F3, secno & 0xFF);
      X86::OUTB(0x1F4, (secno >> 8) & 0xFF);
      X86::OUTB(0x1F5, (secno >> 16) & 0xFF);
      X86::OUTB(0x1F6, 0xE0 | ((diskno&1)<<4) | ((secno>>24)&0x0F));
      X86::OUTB(0x1F7, 0x30);	// CMD 0x30 means write sector

      for (; nsecs > 0; nsecs--, src = ((UInt8*)src + SECTOR_SIZE))
      {
        if ((r = ide_wait_ready(1)) < 0)
          return r;
        X86::OUTSL(0x1F0, src, SECTOR_SIZE/4);
      }

      return 0;
    }

    void Read(UInt sectorIndex, Sector* destination, UInt size)
    {
      ide_read(sectorIndex, (void*)destination, size);
    }

    void Write(UInt sectorIndex, Sector* source, UInt size)
    {
      ide_write(sectorIndex, (void*)source, size);
    }

    UInt GetSectorCount()
    { return 0; }

    Stream* CreateStream()
    {
      DiskStream* stream = new DiskStream;
      return stream;
    }
  }
}
