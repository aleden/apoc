#pragma once
#include "apoccommon.h"

namespace Apoc
{
  namespace X86
  {
    //
    // Interrupt Descriptor Table (IDT)
    //
    namespace IDT
    {
      // This is an entry in the IDT
      #pragma pack (push, 1)
      struct Descriptor
      {
	// Bits 0-16 of interrupt address
	UInt16 baseLow;

	// Code selector in GDT
	UInt16 codeSelector;

	// Reserved (0)
	UInt8 reserved;

	// Bit flags
	UInt8 flags;

#if APOC_ARCH == APOC_ARCH_X86_64
        // Bits 16-31 of interrupt address
        UInt16 baseMiddle;

        // Bits 32-63 of interrupt address
        UInt32 baseHigh;

        // Reserved (0)
        UInt32 reserved2;
#else
	// Bits 16-31 of interrupt address
	UInt16 baseHigh;
#endif
      };
      #pragma pack (pop)

      //! Must be in the format 0D110, where D is descriptor type
      enum DESCRIPTOR_FLAG
      {
        DESCRIPTOR_FLAG_BIT16   = 0x06, //00000110
        DESCRIPTOR_FLAG_BIT32   = 0x0E, //00001110
        DESCRIPTOR_FLAG_RING1   = 0x40, //01000000
        DESCRIPTOR_FLAG_RING2   = 0x20, //00100000
        DESCRIPTOR_FLAG_RING3   = 0x60, //01100000
        DESCRIPTOR_FLAG_PRESENT = 0x80 //10000000
      };

      typedef void (/*_cdecl*/ *Interrupt)(void);

      //! Initialize IDT with basic routines
      void Initialize();

      //! Get an interrupt from the IDT
      //! \param index The interrupt index
      Interrupt* GetInterrupt(UInt8 index);

      //! Install interrupt routine
      void InstallInterrupt(Interrupt, UInt8 index, UInt8 flags, UInt16 codeSelector);

      volatile Descriptor* GetDescriptor(UInt8 index);

      UInt GetIDTBase();
      UInt GetNumInterrupts();
    }
  }
}
