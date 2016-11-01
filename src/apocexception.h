#pragma once
#include "apocstring.h"

namespace Apoc
{
  class Exception
  {
    UTF8Pointer message;
  public:

    inline Exception(UTF8Pointer message) : message(message) {}

    inline UTF8Pointer GetMessage()
    { return message; }
  };
}
