#include "apocscrollingtextwindow.h"

namespace Apoc
{
  void ScrollingTextWindow::Update()
  {
    ClearText();

    Point2d position(0, 0);

    Array<Character, TEXT_BUFFER_SIZE>::Iterator pointer = text.Begin() + GetScrollCount();
    while (pointer != text.End() && position.y < static_cast<Int>(GetSize().y))
    {
      const Character& character = *pointer;

      if (character == '\n')
      {
        position.x = 0;
        ++position.y;
      }
      else
      {
        PlotCharacter(character, position);
        ++position.x;

        if (position.x >= static_cast<Int>(GetSize().x))
        {
          position.x = 0;
          ++position.y;
        }
      }

      ++pointer;
    }

    if (IsScrollingToEnd() && pointer != text.End())
    {
      ScrollLines(1);
      Update();
    }
  }

  void ScrollingTextWindow::ScrollForwardLine()
  {
    Array<Character, TEXT_BUFFER_SIZE>::Iterator pointer = text.Begin() + GetScrollCount();
    UInt count = 0;
    for (;;)
    {
      ++count;
      if (*pointer == '\n' || count > GetSize().x)
        break;

      ++pointer;
    }

    Scroll(count);
  }

  void ScrollingTextWindow::ScrollBackwardLine()
  {
    Array<Character, TEXT_BUFFER_SIZE>::Iterator pointer = text.Begin() + GetScrollCount() - 1;
    UInt count = 0;
    for (;;)
    {
      --pointer;
      ++count;
      if (*pointer == '\n' || count > GetSize().x)
        break;
    }

    Scroll(-count);
  }

  void ScrollingTextWindow::ScrollLines(Int lineCount)
  {
    if (lineCount > 0)
    {
      while (lineCount > 0)
      {
        ScrollForwardLine();
	--lineCount;
      }
    }
    else if (lineCount < 0)
    {
      while (lineCount < 0)
      {
        ScrollBackwardLine();
	++lineCount;
      }
    }
  }
}
