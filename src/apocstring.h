#pragma once
#include "apoccommon.h"
#include "apocutf8.h"
#include "apocmath.h"
#include "apocalgorithms.h"

namespace Apoc
{
  inline bool IsCharacterPrintable(Character character)
  { return IsBetweenInclusive(character, ' ', '~') || character == '\n'; }

  inline bool IsCharacterSymbol(Character character)
  { return IsBetweenInclusive(character, '!', '~'); }

  template <typename CHAR>
  UInt FindInString(CHAR* string, CHAR character)
  {
    UInt count = 0;
    while (*string != '\0')
    {
      if (*string == character)
        return count;

      ++count;
      ++string;
    }

    return count;
  }

  template <typename T>
  inline UInt CountString(const T* string)
  {
    UInt c = 0;
    while (*string != '\0')
    {
      ++c;
      ++string;
    }

    return c;
  }

  template <typename CHAR>
  inline bool AreStringsEqual(const CHAR* stringA, const CHAR* stringB)
  {
    while (*stringA == *stringB)
    {
      if (*stringA == '\0')
        return true;

      ++stringA;
      ++stringB;
    }

    return false;
  }

  template <typename T>
  inline void ReverseString(const T* string, T* reversedString)
  {
    UInt length = CountString(string);

    for (const T* p = string + length; p > string; --p)
      *reversedString++ = *p;
    
    *reversedString = '\0';
  }

  template <typename T>
  inline void ReverseString(T* string)
  {
    UInt length = CountString(string);

    for (UInt i = 0; i < length/2; ++i)
    {
      auto temp = string[length - i - 1];
      string[length - i - 1] = string[i];

      string[i] = temp;
    }
  }

  template <typename CHAR>
  inline UInt CopyString(const CHAR* source, CHAR* destination)
  {
    UInt count = 0;
    for (;;)
    {
      ++count;
      if ((*destination = *source) == 0)
        break;

      ++destination;
      ++source;
    }

    return count;
  }

  template <typename CHAR>
  inline void CopyString(const CHAR* start, const CHAR* end, CHAR* destination)
  {
    while (start < end)
      *destination++ = *start++;

    *destination = '\0';
  }

  //! Null-terminated array of string pointers
  template <typename CHAR>
  inline void SplitString(const CHAR* string, const CHAR* splitString, CHAR** outStrings)
  {
    const CHAR* lastPCopied = string;
    for (; *string != '\0'; ++string)
    {
      const CHAR* sp = splitString;
      while (*sp == *string)
      {
        ++string;
        ++sp;

        if (*sp == '\0') // Have we reached the end of the split string?
        {
          UInt splitStringLength = CountString(splitString);

          // Copy from lastPCopied to (p - splitStringLength)
          CopyString(lastPCopied, string - splitStringLength, *outStrings++);

          if (!*outStrings)
            return;

          // Set lastPCopied to p
          lastPCopied = string;
        }
      }
    }

    CopyString(lastPCopied, string, *outStrings++);
    *outStrings = 0;
  }

  template <typename INT, typename CHAR, UInt BASE>
  inline CHAR* IntToString(INT integer, CHAR* string, UInt length = 0)
  {
    CHAR* p = string;
    do
    {
      CHAR digit = integer % BASE;
      digit += (digit > 9 ? 'A' - 10 : '0');
      *p++ = digit;
    } while ((integer /= BASE) > 0);

    if (length)
    {
      Int digitsLeft = static_cast<Int>(p - string);
      for (Int i = 0; i < (static_cast<Int>(length) - digitsLeft); ++i)
        *p++ = '0';
    }

    *p = '\0';

    ReverseString(string);

    return string;
  }

  //! e.g. (BASE = 10): "123456789"
  //!      (BASE = 16): "123ABCDEF"
  template <typename CHAR, UInt BASE>
  Int StringToInt(CHAR* string)
  {
    Int integer = 0;

    while (*string != '\0')
    {
      Int digitValue;
      if (IsBetweenInclusive(*string, '0', '9'))
        digitValue = (*string) - '0';
      else if (BASE >= 16 && IsBetweenInclusive(*string, 'A', 'Z'))
        digitValue = (*string) - 'A' + 10;
      else
        return integer;

      integer *= BASE;
      integer += digitValue;

      ++string;
    }

    return integer;
  }

  template <typename INT, typename CHAR>
  inline CHAR* IntToBinaryString(INT integer, CHAR* string, UInt length = 0)
  { return IntToString<INT, CHAR, 2>(integer, string, length); }

  template <typename INT, typename CHAR>
  inline CHAR* IntToOctalString(INT integer, CHAR* string, UInt length = 0)
  { return IntToString<INT, CHAR, 8>(integer, string, length); }

  template <typename INT, typename CHAR>
  inline CHAR* IntToDecimalString(INT integer, CHAR* string, UInt length = 0)
  { return IntToString<INT, CHAR, 10>(integer, string, length); }

  template <typename INT, typename CHAR>
  inline CHAR* IntToHexadecimalString(INT integer, CHAR* string, UInt length = 0)
  { return IntToString<INT, CHAR, 16>(integer, string, length); }

  template <typename CHAR>
  inline Int BinaryStringToInt(CHAR* string)
  { return StringToInt<CHAR, 2>(string); }

  template <typename CHAR>
  inline Int OctalStringToInt(CHAR* string)
  { return StringToInt<CHAR, 8>(string); }

  template <typename CHAR>
  inline Int DecimalStringToInt(CHAR* string)
  { return StringToInt<CHAR, 10>(string); }

  template <typename CHAR>
  inline Int HexadecimalStringToInt(CHAR* string)
  { return StringToInt<CHAR, 16>(string); }

  //! Converts a string to an integer with a base
  //! based on the suffix (b = binary, h = hex, o = octal)
  template <typename CHAR>
  inline Int StringToInt(CHAR* string)
  {
    switch (string[CountString(string) - 1])
    {
      case 'h':
        return HexadecimalStringToInt(string);
      case 'b':
        return BinaryStringToInt(string);
      case 'o':
        return OctalStringToInt(string);
      default:
        return DecimalStringToInt(string);
    }
  }
}
