#pragma once

#define APOC_ARCH_X86_32 0
#define APOC_ARCH_X86_64 1

#ifndef __ASSEMBLER__
namespace Apoc
{
  enum CPU_ARCHITECTURE
  {
    CPU_ARCHITECTURE_X86_32,
    CPU_ARCHITECTURE_X86_64
  };
}
#endif
