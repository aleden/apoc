#include "apoctextwindow.h"
#include "apocstream.h"
#include "apoctextgraphics.h"

namespace Apoc
{
  void TextWindow::PlotCharacter(Character character, const Point2d& position)
  {
    TextGraphics::PutCharacter(character, GetPosition() + position);
  }

  void TextWindow::ClearText()
  {
    TextGraphics::SetCursorPosition(-1);

    for (UInt y = 0; y < GetSize().y; ++y)
    {
      for (UInt x = 0; x < GetSize().x; ++x)
      {
	PlotCharacter(' ', Point2d(x, y));
      }
    }
  }
}
