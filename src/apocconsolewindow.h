#pragma once
#include "apocscrollingtextwindow.h"
#include "apocarraystream.h"

namespace Apoc
{
  // Forward declaration
  class Console;

  //! This is an interactive "console" window which receives lines of text input from the user, outputs them to the console's input stream, and sends output from the console to the scrollable text window
  class ConsoleWindow : public ScrollingTextWindow
  {
    Array<Character, 0x1000> userInput;
    ArrayStream<Character, 0x1000> userInputStream;
    Console* console;

    Array<Character, TEXT_BUFFER_SIZE>::Iterator userInputStart;

  public:
    ConsoleWindow(Console*);
    void OnKeyPress();

    inline Stream* GetUserInputStream()
    { return &userInputStream; }

    inline Console* GetConsole()
    { return console; }
  };
}
