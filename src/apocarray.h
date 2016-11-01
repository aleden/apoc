#pragma once
#include "apoccommon.h"

namespace Apoc
{
  //! This data structure provides the features of a simple static C array, with nothing else except an extra "end" pointer to keep track how many elements have been stored, and some extra functions for conveinence.
  template <typename T, UInt SIZE = 0xFF>
  class Array
  {
  public:
    class Iterator
    {
      T* element;

    public:
      inline Iterator(T* element = 0) : element(element) {}

      Iterator& operator = (const Iterator& iterator)
      {
        element = iterator.element;
        return *this;
      }
 
      Iterator operator + (Int nextCount)
      { return Iterator(element + nextCount); }

      Iterator operator - (Int previousCount)
      { return Iterator(element - previousCount); }

      Int operator - (const Iterator& iterator)
      { return element - iterator.element; }

      Iterator& operator ++ ()
      {
        ++element;

        return *this;
      }

      Iterator operator ++ (int)
      {
        T* oldElement = element;
        ++element;

        return Iterator(oldElement);
      }

      Iterator& operator -- ()
      {
        --element;

        return *this;
      }

      Iterator operator -- (int)
      {
        T* oldElement = element;
        --element;

        return Iterator(oldElement);
      }

      T& operator * ()
      { return *element; }

      const T& operator * () const
      { return *element; }

      bool operator != (const Iterator& iterator)
      { return this->element != iterator.element; }
 
      bool operator == (const Iterator& iterator)
      { return this->element == iterator.element; }
    };

    T array[SIZE];
    T* end;

  public:
    inline Array(UInt size)
    { end = array + size; }

    inline Array()
    { end = array; }

    inline const T& Get(UInt index) const
    { return array[index]; }

    inline void Set(UInt index, const T& element)
    { array[index] = element; }

    inline void Append(T element)
    { *end++ = element; }

    inline T* BeginPointer()
    { return array; }

    inline const T* BeginPointer() const
    { return array; }

    inline T* EndPointer()
    { return end; }

    inline const T* EndPointer() const
    { return end; }

    inline Iterator Begin()
    { return Iterator(array); }

    inline Iterator End()
    { return Iterator(end); }

    inline UInt GetCapacity()
    { return SIZE; }

    inline UInt GetSpace()
    { return SIZE - GetSize(); }

    inline UInt GetSize() const
    { return end - array; }

    inline void Resize(UInt size)
    { end = array + size; }

    inline T RemoveEnd()
    {
      if (end <= array)
        return *end;

      T temporary = *(end - 1);
      --end;
      return temporary;
    }

    inline void TrimFromBegin(UInt elementCount)
    {
      for (T* p = array; p + elementCount < end; ++p)
        *p = *(p + elementCount);

      end -= elementCount;
    }

    inline void TrimFromEnd(UInt elementCount)
    {
      end -= elementCount;
      if (end < array)
        end = array;
    }

    inline void Clear()
    { end = array; }
  };
};
