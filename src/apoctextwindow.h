#pragma once
#include "apoccommon.h"
#include "apocwindow.h"
#include "apocstream.h"
#include "apocarray.h"

namespace Apoc
{
  //! An abstraction upon a normal Window which plots in terms of pixels, text window renders characters instead.
  class TextWindow : public Window
  {
  public:
    inline TextWindow() {}

    //! Reimplement to convert pixels to characters
    inline const Size2d& GetSize()
    { return Window::GetSize(); }

    void PlotCharacter(Character character, const Point2d& position);
    void ClearText();
  };
}
