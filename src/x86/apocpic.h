#pragma once
#include "apoccommon.h"

namespace Apoc
{
  namespace X86
  {
    namespace PIC
    {
      void Initialize();
      void SignalEOI(UInt irq);
    }
  }
}
