#include "apoctextgraphics.h" 
#include "apocstring.h"
#include "x86/apocx86.h"

namespace Apoc
{
  namespace TextGraphics
  {
    UInt8 textAttribute = GREEN_FOREGROUND;
    UInt cursorPosition = 0;

    static inline void UpdateCursorPosition();
    static inline Int8* GetStartVidMem();
    static inline Int8* GetEndVidMem();

    UInt GetNumRows()
    { return 25; } 

    UInt GetNumColumns()
    { return 80; }

    UInt8 GetTextAttribute()
    { return textAttribute; }

    void SetTextAttribute(UInt8 newTextAttribute)
    { textAttribute = newTextAttribute; }

    void Clear()
    {
      for (UInt* vm = (UInt*)GetStartVidMem(); (void*)vm < (void*)GetEndVidMem(); ++vm)
#if APOC_ARCH == APOC_ARCH_X86_32
        *vm = 0x07200720;
#elif APOC_ARCH == APOC_ARCH_X86_64
        *vm = 0x0720072007200720;
#endif
    }

    void PutCharacter(Character character, UInt position)
    {
      *(GetStartVidMem() + position*2) = static_cast<Int8>(character);
      *(GetStartVidMem() + position*2 + 1) = GetTextAttribute();
    }

    void PutCharacter(Character character, const Vector2di& position)
    { PutCharacter(character, position.y*GetNumColumns() + position.x); }

    void SetCursorPosition(UInt position)
    {
      cursorPosition = position;
      UpdateCursorPosition();
    }

    void SetCursorPosition(const Vector2dui& position)
    { SetCursorPosition(position.x + position.y*GetNumColumns()); }

    UInt GetCursorPosition()
    { return cursorPosition; }

    static inline void UpdateCursorPosition()
    {
      // Write cursor location low byte index to CRT index register
      X86::OUTB(0x03D4, 0x0F);

      // Write new low byte of cursor position to CRT data register
      X86::OUTB(0x3D5, static_cast<UInt8>((cursorPosition) & 0xFF));

      // Write cursor location high byte index to CRT index register
      X86::OUTB(0x03D4, 0x0E);

      // Write new high byte of cursor position to CRT data register
      X86::OUTB(0x3D5, static_cast<UInt8>((cursorPosition >> 8) & 0xFF));
    }

    static inline Int8* GetStartVidMem()
    { return (Int8*)0xB8000; }

    static inline Int8* GetEndVidMem()
    { return (Int8*)0xBFFFF; }
  }
}
