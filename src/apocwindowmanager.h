#pragma once
#include "apoccommon.h"
#include "apockey.h"

namespace Apoc
{
  // Forward declarations
  class TextWindow;
  class Window;

  namespace WindowManager
  {
    void Initialize();
    void AddWindow(Window*);

    void OnKeyRelease();
    void OnKeyPress();

    Window* GetActiveWindow();
  }
}
