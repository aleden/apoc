#include "apocconsolewindow.h"
#include "apocconsole.h"
#include "apockeyboard.h"
#include "apockernel.h"
#include "apocconsole.h"
#include "apocstream.h"
#include "apocalgorithms.h"

namespace Apoc
{
  ConsoleWindow::ConsoleWindow(Console* console) :
    userInputStream(&userInput), console(console)
  {
    console->SetInputStream(GetUserInputStream());
    console->SetOutputStream(GetTextStream());

    GetTextStream()->WriteString("> ");

    userInputStart = GetText().End();
  }

  void ConsoleWindow::OnKeyPress()
  {
    SetScrollingToEnd(false);

    KEY key;
    Keyboard::GetKeyPressStream()->Read(&key);

    if (IsKeyPrintable(key))
    {
      Character character;
      Keyboard::GetTextStream()->Read(&character);

      if (IsCharacterPrintable(character))
      {
	GetTextStream()->Write(character);
        SetScrollingToEnd(true);
	if (character == '\n')
	{
	  userInput.Resize(GetText().End() - userInputStart);
	  userInputStream.Jump(0);
	  Copy(userInputStart, GetText().End() - 1, userInput.Begin());
	  *(userInput.End() - 1) = 0;

	  GetConsole()->ReadInput();

	  GetTextStream()->WriteString("> ");
	  userInputStart = GetText().End();
	}
      }
    }

    switch (key)
    {
      case KEY_PAGE_DOWN:
        ScrollLines(GetSize().y);
        break;

      case KEY_PAGE_UP:
        ScrollLines(-GetSize().y);
        break;

      case KEY_BACKSPACE:
        GetText().RemoveEnd();
        break;

      default:
        break;
    }

    Update();
  }
}
