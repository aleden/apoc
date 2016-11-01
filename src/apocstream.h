#pragma once
#include "apoccommon.h"
#include "apocstring.h"

namespace Apoc
{
  class Stream
  {
  public:

    virtual Stream* Clone() = 0;

    //
    // Read
    //

    virtual UInt Read(Byte* out, UInt count)
    { return 0; }

    template <typename T>
    inline UInt Read(T* out)
    { return Read((Byte*)out, sizeof(T)); }

    inline UInt ReadString(Character* string)
    {
      UInt count = 0;

      for (;;)
      {
        count += Read((Byte*)string, sizeof(Character));

	if (*string == 0)
	  break;

	++string;
      }

      return count;
    }

    //
    // Write
    //

    virtual UInt Write(const Byte* source, UInt byteCount)
    { return 0; }

    template <typename T>
    inline UInt Write(const T& source)
    { return Write((Byte*)&source, sizeof(T)); }

    virtual void Flush() {}

    inline UInt WriteString(const Character* string)
    {
      UInt characterCount = CountString(string);
      Write((Byte*)string, sizeof(Character) * characterCount);
      return characterCount;
    }

    //
    // Seek
    //

    virtual UInt GetSize() const
    { return 0; }

    virtual UInt GetPosition() const
    { return 0; }

    virtual UInt Jump(UInt elementCount)
    { return 0; }

    virtual Int Seek(Int elementOffset)
    { return 0; }
  };
}
