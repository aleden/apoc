#pragma once
#include "apoccommon.h"
#include "apoclinkedlist.h"

namespace Apoc
{
  template <typename T>
  class Queue
  {
    LinkedList<T> linkedList;

  public:
    //! Adds an element to the back of the queue
    inline void Enqueue(const T& value)
    { linkedList.Append(value); }

    //! Removes the element at the front of the queue
    inline void Dequeue()
    { linkedList.Remove(linkedList.Begin()); }

    //! Gets the element at the front of the queue
    inline typename LinkedList<T>::Iterator GetFront()
    { return linkedList.Begin(); }

    inline const typename LinkedList<T>::Iterator GetFront() const
    { return linkedList.Begin(); }

    //! Gets the element at the back of the queue
    inline typename LinkedList<T>::Iterator GetBack()
    { return linkedList.End(); }

    inline const typename LinkedList<T>::Iterator GetBack() const
    { return linkedList.Begin(); }
  };
}
