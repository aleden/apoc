#include "apocutil.h"
#include "apocstring.h"
#include "apocstream.h"

namespace Apoc
{
  void DumpMemory(Byte* start, Byte* end, Stream* out)
  {
    const unsigned int numColumns = 16;

    UInt offset = 0;
    Int8 string[0xFF];
    while (start < end)
    {
      out->WriteString(IntToHexadecimalString(offset, string, 8));
      out->WriteString("  ");
      // Print start row view
      for (UInt i = 0; i < numColumns; ++i)
      {
        UInt8 byte = *((UInt8*)start);
        out->WriteString(IntToHexadecimalString(byte, string, 2));
        out->Write(' ');

	if (i == (numColumns / 2) - 1)
          out->Write(' ');

	++start;
 
        if (start == end)
        {
          start += (numColumns - i - 1);

          for (++i; i < numColumns; ++i)
            out->WriteString("   ");
 
          break;
        }
      }

      start -= numColumns;

      out->Write(' ');

      // Print ascii row view
      for (UInt i = 0; i < numColumns; ++i)
      {
        if (IsCharacterSymbol(*((Int8*)start)))
          out->Write(*((Int8*)start));
        else
          out->Write('.');

	++start;

        if (start == end)
          break;
      }

      out->Write('\n');

      offset += 16;
    }
  }
}
