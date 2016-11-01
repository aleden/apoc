#pragma once
#include "apoccommon.h"

namespace Apoc
{
  //! TODO
  class UTF8Pointer
  {
    Int8* data;
  public:

    template <typename T>
    inline UTF8Pointer(T* data) : data((Int8*)data) {}

    inline UInt operator *()
    { return *data; }

    inline UTF8Pointer& operator ++()
    {
      ++data;
      return *this;
    }

    inline UTF8Pointer operator ++(int)
    {
      UTF8Pointer copy = *this;
      ++(*this);
      return copy;
    }

    inline Int8* GetData()
    { return data; }

    inline const Int8* GetData() const
    { return data; }
  };
}
