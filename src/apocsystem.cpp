#include "apocsystem.h"
#include "apoccommon.h"

namespace Apoc
{
  namespace System
  {
    CPU_ARCHITECTURE GetCPUArchitecture()
    {
#if APOC_ARCH == APOC_ARCH_X86_32
      return CPU_ARCHITECTURE_X86_32;
#elif APOC_ARCH == APOC_ARCH_X86_64
      return CPU_ARCHITECTURE_X86_64;
#endif
    }
  }
}

