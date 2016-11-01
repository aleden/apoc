#pragma once
#include "apoccommon.h"
#include "apoctextwindow.h"

namespace Apoc
{
  class ScrollingTextWindow : public TextWindow
  {
    class TextStream : public Stream
    {
      ScrollingTextWindow* parent;

    public:
      inline TextStream(ScrollingTextWindow* parent) : parent(parent) {}

      inline Stream* Clone()
      { return new TextStream(parent); }

      UInt Write(const Byte* source, UInt count)
      {
        const Byte* end = source + count;
        while (source < end)
        {
          parent->text.Append(*source);
          ++source;
        }

        return count;
      }
    } textStream;

  protected:
    static const UInt TEXT_BUFFER_SIZE = 0xFFFF;

  private:
    bool scrollToEnd;
    Int rowsScrolled;
    Array<Character, TEXT_BUFFER_SIZE> text;

  protected:
    inline Array<Character, TEXT_BUFFER_SIZE>& GetText()
    { return text; }

  public:
    inline ScrollingTextWindow() : textStream(this), scrollToEnd(true), rowsScrolled(0) {}

    inline void Scroll(Int rowCount)
    { rowsScrolled = Maximum<Int>(rowsScrolled + rowCount, 0); }

    void ScrollLines(Int lineCount);

    void ScrollForwardLine();
    void ScrollBackwardLine();
    
    inline bool IsScrollingToEnd()
    { return scrollToEnd; }

    inline void SetScrollingToEnd(bool shouldScrollToEnd)
    { scrollToEnd = shouldScrollToEnd; }

    inline UInt GetScrollCount()
    { return rowsScrolled; }

    inline Stream* GetTextStream()
    { return &textStream; }

    void Update();
  };
}
