#pragma once
#include "apoccommon.h"

namespace Apoc
{
  template <typename ITERATORA, typename ITERATORB>
  void Copy(ITERATORA sourceBegin, ITERATORA sourceEnd, ITERATORB destination)
  {
    while (sourceBegin != sourceEnd)
      *destination++ = *sourceBegin++;
  }

  template <typename ITERATORA, typename ITERATORB>
  void Copy(ITERATORA sourceBegin, ITERATORA sourceEnd, ITERATORB destinationStart, ITERATORB destinationEnd)
  {
    while (sourceBegin != sourceEnd && destinationStart != destinationEnd)
      *destinationStart++ = *sourceBegin++;
  }

  template <typename ITERATORA, typename ITERATORB>
  void ReverseCopy(ITERATORA sourceBegin, ITERATORA sourceEnd, ITERATORB destination)
  {
    while (sourceEnd != sourceBegin)
      *destination++ = *sourceEnd--;
  }

  template <typename ITERATORA, typename ITERATORB, typename T>
  void CopyValue(ITERATORA destinationStart, ITERATORB destinationEnd, const T& value)
  {
    while (destinationStart != destinationEnd)
      *destinationStart++ = value;
  }

  template <typename T>
  inline bool IsBetweenInclusive(T number, T min, T max)
  { return number >= min && number <= max; }

  template <typename T>
  inline T Minimum(T a, T b)
  { return a < b ? a : b; }

  template <typename T>
  inline T Maximum(T a, T b)
  { return a > b ? a : b; }
}
