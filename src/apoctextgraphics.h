#pragma once
#include "apoccommon.h"
#include "apocvec2d.h"
#include "apocstring.h"

namespace Apoc
{
  namespace TextGraphics
  {
    enum TEXT_ATTRIBUTE_FLAGS
    {
      BLUE_FOREGROUND    = 1 << 0,
      GREEN_FOREGROUND   = 1 << 1,
      RED_FOREGROUND     = 1 << 2,
      INTENSE_FOREGROUND = 1 << 3,
      BLUE_BACKGROUND    = 1 << 4,
      GREEN_BACKGROUND   = 1 << 5,
      RED_BACKGROUND     = 1 << 6,
      INTENSE_BACKGROUND = 1 << 7
    };
    UInt GetNumRows();
    UInt GetNumColumns();

    UInt8 GetTextAttribute();
    void SetTextAttribute(UInt8 textAttribute);

    void Clear();

    void PutCharacter(Character, UInt position);
    void PutCharacter(Character, const Point2d& position);

    void SetCursorPosition(UInt position);
    void SetCursorPosition(const Vector2dui& position);
    UInt GetCursorPosition();
  }
}
