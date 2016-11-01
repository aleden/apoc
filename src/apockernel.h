#pragma once
#include "apoccommon.h"
#include "apocstring.h"

namespace Apoc
{
  class Console;

  namespace Kernel
  {
    UInt GetVersion();
    const Int8* GetVersionString();
    const Int8* GetVersionNumberString();

    Console* GetConsole();

    void Log(const Int8* message);

    void Halt(const Int8* reason);
  }
}
