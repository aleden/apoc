#pragma once
#include "apoccommon.h"
#include "apocvec2d.h"
#include "apockey.h"
#include "apockeyboard.h"
#include "apocstream.h"

namespace Apoc
{
  //! Abstract concept of a window. A window can receive key presses.
  class Window
  {
    Stream* keyPressStream;
    Stream* keyReleaseStream;

    Point2d position;
    Size2d size;

   public:
    inline Window(Stream* keyPressStream, Stream* keyReleaseStream) : keyPressStream(keyPressStream), keyReleaseStream(keyReleaseStream) {}

    inline Window()
    {
      keyPressStream = Keyboard::GetKeyPressStream();
      keyReleaseStream = Keyboard::GetKeyReleaseStream();
    }

    inline void SetPosition(const Point2d& newPosition)
    { position = newPosition; }
    
    inline void SetSize(const Size2d& newSize)
    { size = newSize; }

    inline const Point2d& GetPosition()
    { return position; }

    inline const Size2d& GetSize()
    { return size; }

    virtual void OnKeyPress() {}
    virtual void OnKeyRelease() {}

    inline void SetKeyPressStream(Stream* in)
    { keyPressStream = in; }

    inline void SetKeyReleases(Stream* in)
    { keyReleaseStream = in; }

    inline Stream* GetKeyPressStream()
    { return keyPressStream; }

    inline Stream* GetKeyReleaseStream()
    { return keyReleaseStream; }
  };
}
