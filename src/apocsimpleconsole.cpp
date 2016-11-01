#include "apocsimpleconsole.h"

namespace Apoc
{
  void SimpleConsole::RunCommand(const Character** args)
  {
    const Character* commandName = *args;

    if (AreStringsEqual(commandName, "HELP"))
    {
      GetOutputStream()->WriteString("ABOUT - Show console name\nHELP - List available commands\n");
      for (const Command* i = commands; i->name; ++i)
      {
        GetOutputStream()->WriteString(i->name);
	if (i->description)
	{
	  GetOutputStream()->WriteString(" - ");
          GetOutputStream()->WriteString(i->description);
	}
        GetOutputStream()->Write('\n');
      }

      return;
    }

    for (const Command* i = commands; i->name; ++i)
    {
      if (AreStringsEqual(i->name, commandName))
      {
         i->procedure(args, this);
	 return;
      }
    }
    GetOutputStream()->WriteString("Command not found\n");
  }
}
