#pragma once
#include "apoccommon.h"

namespace Apoc
{
  namespace X86
  {
    //
    // Global Descriptor Table (GDT)
    //
    namespace GDT
    {
#if APOC_PLATFORM == APOC_PLATFORM_X86_32
      const UInt16 DEFAULT_CODE_SELECTOR = 8;
#elif APOC_PLATFORM == APOC_PLATFORM_X86_64
      const UInt16 DEFAULT_CODE_SELECTOR = 16;
#endif
    }
  }
}
