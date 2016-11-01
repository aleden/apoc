#pragma once
#include "x86/apocx86.h"
#include "apockernel.h"

#define DEBUG

namespace Apoc
{
  static inline void ASSERT(bool expression)
  {
#ifdef DEBUG
    if (!expression)
      X86::INT3();
#endif
  }
}
