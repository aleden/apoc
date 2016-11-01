#include "apocwindowmanager.h"
#include "apocwindow.h"
#include "apoctextwindow.h"
#include "apocarray.h"
#include "apocstream.h"
#include "apockeyboard.h"
#include "apockernel.h"
#include "apocconsole.h"
#include "apocstream.h"
#include "apoctextgraphics.h"
#include "apoclinkedlist.h"

namespace Apoc
{
  namespace WindowManager
  {
    LinkedList<Window*> windows;
    Window* activeWindow;

    void Initialize()
    {
    }

    void AddWindow(Window* window)
    {
      for (LinkedList<Window*>::Iterator wp = windows.Begin(); wp != windows.End(); ++wp)
      {
        Window* w = *wp;
        w->SetSize(Size2d(w->GetSize().x / 2, w->GetSize().y / 2));
      }

      window->SetSize(Size2d(TextGraphics::GetNumColumns(), TextGraphics::GetNumRows()));

      windows.Append(window);
      activeWindow = window;
    }

    void OnKeyRelease()
    {
      if (!GetActiveWindow())
        return;

      if (GetActiveWindow()->GetKeyReleaseStream() == Keyboard::GetKeyReleaseStream())
        GetActiveWindow()->OnKeyRelease();
    }

    void OnKeyPress()
    {
      if (!GetActiveWindow())
        return;

      if (GetActiveWindow()->GetKeyPressStream() == Keyboard::GetKeyPressStream())
        GetActiveWindow()->OnKeyPress();
    }

    Window* GetActiveWindow()
    { return activeWindow; }
  }
}
