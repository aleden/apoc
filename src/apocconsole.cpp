#include "apocconsole.h"
#include "apoctextgraphics.h"
#include "apoctextwindow.h"
#include "apockeyboard.h"

namespace Apoc
{
  void Console::ReadInput()
  {
    Character string[0xFF];
    GetInputStream()->ReadString(string);

    if (AreStringsEqual(string, "ABOUT"))
    {
      GetOutputStream()->WriteString(name);
      GetOutputStream()->WriteString(" Console\n");
      return;
    }

    Character a0[0xFF] = {0}, a1[0xFF] = {0}, a2[0xFF] = {0}, a3[0xFF] = {0};
    Character* args[] = {a0, a1, a2, a3, 0};
    SplitString(string, " ", args);

    RunCommand((const Character**)args);
  }
}
