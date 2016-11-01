#pragma once
#include "apoccommon.h"
#include "apocarray.h"
#include "apocstream.h"

namespace Apoc
{
  template <typename T, UInt SIZE = 0xFF>
  class ArrayStream : public Stream
  {
    Array<T, SIZE>* array;
    Byte* position;

  public:
    inline ArrayStream(Array<T, SIZE>* array) : array(array) , position((Byte*)array->BeginPointer()) {}

    inline Stream* Clone()
    {
      ArrayStream* clone = new ArrayStream(array);
      clone->position = position;
      return clone;
    }

    inline UInt Read(Byte* out, UInt count = 1)
    {
      for (UInt i = 0; i < count; ++i)
        *out = *position++;

      return count;
    }

    UInt Write(const Byte* source, UInt count = 1)
    {
      while (count != 0)
        *position++ = *source++;

      return count;
    }

    virtual UInt GetSize() const
    { return array->GetSize() * sizeof(T); }

    virtual UInt GetPosition() const
    { return position - (Byte*)array->BeginPointer(); }

    virtual UInt Jump(UInt elementCount)
    {
      position = (Byte*)array->BeginPointer() + elementCount;
      return elementCount;
    }

    virtual Int Seek(Int elementOffset)
    {
      Byte* seekedPosition = Maximum((Byte*)array->BeginPointer(), position + elementOffset);
      Int move = seekedPosition - position;
      position = seekedPosition;
      return move;
    }
  };
}

