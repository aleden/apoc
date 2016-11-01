#pragma once
#include "apoccommon.h"
#include "apocqueue.h"
#include "apocstream.h"

namespace Apoc
{
  template <typename T>
  class InQueueStream : public Stream
  {
    Queue<T>* queue;
    UInt bytesRead;

  public:
    inline InQueueStream(Queue<T>* queue) : queue(queue), bytesRead(0) {}

    inline Stream* Clone()
    {
      InQueueStream* clone = new InQueueStream(queue);
      clone->bytesRead = bytesRead;
      return clone;
    }
    UInt Read(Byte* out, UInt count)
    {
      typename LinkedList<T>::Iterator iterator = queue->GetFront();

      while (count != 0)
      {
	*out++ = *(((Byte*)(&(*iterator))) + bytesRead);
        --count;
	++bytesRead;

        if (bytesRead == sizeof(T))
        {
          queue->Dequeue();
          iterator = queue->GetFront();
          bytesRead = 0;
        }
      }
      return count;
    }

    virtual UInt GetAvailable() const
    { return 0; }
  };
}

