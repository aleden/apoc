#pragma once
#include "apoccommon.h"
#include "apocexception.h"

namespace Apoc
{
  namespace ProcessManager
  {
    bool IsProcessRunning();
    void HandleException(Exception);
  }
}
