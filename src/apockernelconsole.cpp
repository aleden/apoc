#include "apockernelconsole.h"
#include "apocutil.h"
#include "apocstring.h"
#include "apocstream.h"
#include "apockernel.h"
#include "apocmemorymanager.h"
#include "apocdiskio.h"
#include "apocfilesystem.h"
#include "apocalgorithms.h"
#include "x86/apocx86.h"

namespace Apoc
{
  const char* regionTypeStrings[] =
  {
    "REGION_TYPE_UNKNOWN",
    "REGION_TYPE_USABLE",
    "REGION_TYPE_RESERVED",
    "REGION_TYPE_ACPI_RECLAIMABLE",
    "REGION_TYPE_ACPI_NVS",
    "REGION_TYPE_BAD"
  };

  void KernelConsole::ShowIDT(const Character** args, Console* console)
  {
    Int8 buff[0x20];
    console->GetOutputStream()->WriteString(IntToHexadecimalString(X86::IDT::GetIDTBase(), buff));
    console->GetOutputStream()->WriteString("h (");
    console->GetOutputStream()->WriteString(IntToHexadecimalString(X86::IDT::GetNumInterrupts(), buff));
    console->GetOutputStream()->WriteString("h)\n");

    console->GetOutputStream()->WriteString("Address   | Type\n");
    for (UInt i = 0; i < X86::IDT::GetNumInterrupts(); ++i)
    {
      console->GetOutputStream()->WriteString(IntToHexadecimalString((UInt)X86::IDT::GetInterrupt(i), buff, sizeof(UInt)*2)); console->GetOutputStream()->Write('h');
      console->GetOutputStream()->WriteString(" | ");
      console->GetOutputStream()->WriteString(IntToBinaryString(X86::IDT::GetDescriptor(i)->flags, buff, 8));
      console->GetOutputStream()->WriteString("b\n");
    }
  }

  void KernelConsole::ShowMem(const Character** args, Console* console)
  {
    console->GetOutputStream()->WriteString("Base Address     | Length           | Type\n");

    for (UInt i = 0; i < MemoryManager::GetNumRegions(); ++i)
    {
      const MemoryManager::Region* region = MemoryManager::GetRegion(i);
      Int8 buff[0xFF];
#if APOC_ARCH == APOC_ARCH_X86_32
      console->GetOutputStream()->WriteString(IntToHexadecimalString(region->baseAddressHigh, buff, 8));
      console->GetOutputStream()->WriteString(IntToHexadecimalString(region->baseAddressLow, buff, 8));
#elif APOC_ARCH == APOC_ARCH_X86_64
      console->GetOutputStream()->WriteString(IntToHexadecimalString(region->baseAddress, buff, 8));
#endif
      console->GetOutputStream()->WriteString(" | ");
#if APOC_ARCH == APOC_ARCH_X86_32
      console->GetOutputStream()->WriteString(IntToHexadecimalString(region->lengthHigh, buff, 8));
      console->GetOutputStream()->WriteString(IntToHexadecimalString(region->lengthLow, buff, 8));
#elif APOC_ARCH == APOC_ARCH_X86_64
      console->GetOutputStream()->WriteString(IntToHexadecimalString(region->length, buff, 8));
#endif
      console->GetOutputStream()->WriteString(" | ");
      console->GetOutputStream()->WriteString(IntToHexadecimalString(region->type, buff, 8));
      console->GetOutputStream()->WriteString(" [");
      console->GetOutputStream()->WriteString(regionTypeStrings[region->type]);
      console->GetOutputStream()->WriteString("]\n");
    }
  }

  void KernelConsole::ShowMemAvail(const Character** args, Console* console)
  {
    Int8 buff[0xFF];
    console->GetOutputStream()->WriteString(IntToDecimalString(MemoryManager::GetRemaining(), buff));
    console->GetOutputStream()->Write('\n');
  }

  void KernelConsole::DumpMem(const Character** args, Console* console)
  {
    UInt numBytes = 0;
    Int address = 0;

    for (const Character** argp = args + 1; *argp; ++argp)
    {
      if (AreStringsEqual(*argp, "-n"))
      {
	++argp;
	if (*argp)
	  numBytes = StringToInt(*argp); 
      }
      address = StringToInt(*argp); 
    }
    DumpMemory(reinterpret_cast<Byte*>(address), reinterpret_cast<Byte*>(address + numBytes), console->GetOutputStream());
  }

  void KernelConsole::DumpDisk(const Character** args, Console* console)
  {
    UInt numBytes = 0;
    UInt address = 0;

    for (const Character** argp = args + 1; *argp; ++argp)
    {
      if (AreStringsEqual(*argp, "-n"))
      {
	++argp;
	if (*argp)
	  numBytes = StringToInt(*argp); 
      }
      address = StringToInt(*argp); 
    }

    Stream* diskStream = DiskIO::CreateStream();
    diskStream->Jump(address);

    Byte* buff = new Byte[numBytes];

    diskStream->Read(buff, numBytes);
    delete diskStream;

    DumpMemory(buff, buff + numBytes, console->GetOutputStream());

    delete [] buff;
  }

  void KernelConsole::WriteMem(const Character** args, Console* console)
  {
  }

  void KernelConsole::WriteDisk(const Character** args, Console* console)
  {
    Int address = StringToInt(args[1]); 
    Int value = StringToInt(args[2]);

    Character buff[0xFF];
    console->GetOutputStream()->WriteString("*(");
    console->GetOutputStream()->WriteString(IntToHexadecimalString(address, buff));
    console->GetOutputStream()->WriteString(") = ");
    console->GetOutputStream()->WriteString(IntToDecimalString(value, buff));
    console->GetOutputStream()->WriteString("\n");

    Stream* diskStream = DiskIO::CreateStream();
    diskStream->Jump(address);
    diskStream->Write((Byte*)&value, 1);
    delete diskStream;
  }

  void KernelConsole::CreateFS(const Character** args, Console* console)
  {
    //BiStream<Byte>* diskStream = DiskIO::CreateStream();
    //FileSystem* fileSystem = FileSystem::Open(diskStream, FileSystem::TYPE_APOC);
  }

  void KernelConsole::ListFS(const Character** args, Console* console)
  {
  }

  void KernelConsole::TestMem(const Character** args, Console* console)
  {
    Character buff[0xFF];
    for (UInt i = 0; i < 5; ++i)
    {
      UInt allocationSize = i*2;
      void* allocation = MemoryManager::Allocate(allocationSize);

      console->GetOutputStream()->WriteString("Allocation #");
      console->GetOutputStream()->WriteString(IntToHexadecimalString(i, buff, 4));
      console->GetOutputStream()->WriteString(" [");
      console->GetOutputStream()->WriteString(IntToHexadecimalString((UInt)allocation, buff, 8));
      console->GetOutputStream()->WriteString("h ");
      console->GetOutputStream()->WriteString(IntToDecimalString((UInt)allocationSize, buff, 4));
      console->GetOutputStream()->WriteString("h]\n");
    }
  }

  void KernelConsole::Test(const Character**, Console* console)
  {
    Character buff[0xFF];

    Byte byte;
    ((KernelConsole*)console)->diskStream->Read(&byte, 1);
    console->GetOutputStream()->WriteString(IntToHexadecimalString((Int)byte, buff));
    console->GetOutputStream()->Write("\n");
  }

  static const SimpleConsole::Command kernelCommands[] =
  {
    {KernelConsole::ShowIDT, "SHOW-IDT", "Show interrupt descriptor table"},
    {KernelConsole::ShowMem, "SHOW-MEM", "Show memory regions"},
    {KernelConsole::ShowMemAvail, "SHOW-MEM-AVAIL", "Show memory available"},
    {KernelConsole::DumpMem, "DUMP-MEM", "Dump memory data to the screen"},
    {KernelConsole::DumpDisk, "DUMP-DISK", "Dump disk data to the screen"},
    {KernelConsole::WriteMem, "WRITE-MEM", "Write data to memory"},
    {KernelConsole::WriteDisk, "WRITE-DISK", "Write data to disk"},
    {KernelConsole::CreateFS, "CREATE-FS", "Create file system on the disk"},
    {KernelConsole::ListFS, "LIST-FS", "List the file system properties"},
    {KernelConsole::TestMem, "TEST-MEM", "Test the virtual memory allocator"},
    {0, 0}
  };

  KernelConsole::KernelConsole(Stream* in, Stream* out)
    : SimpleConsole(kernelCommands, in, out, Kernel::GetVersionString())
  {
  }
}
