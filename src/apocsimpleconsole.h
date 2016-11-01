#pragma once
#include "apoccommon.h"
#include "apocconsole.h"

namespace Apoc
{
  class SimpleConsole : public Console
  {
  public:
    typedef void (*CommandProcedure)(const Character**, Console*);
    struct Command
    {
      CommandProcedure procedure;
      const Character* name;
      const Character* description;
    };

  private:
    const Command* commands;

  public:
    //! Null-terminated list of command procedures
    inline SimpleConsole(const Command* commands, Stream* inputStream = 0, Stream* outputStream = 0, const Int8* name = "") : Console(inputStream, outputStream, name), commands(commands) {}

    void RunCommand(const Character** args);
  };
}

