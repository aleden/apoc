#include "apocpit.h"
#include "apocx86.h"

namespace Apoc
{
  namespace X86
  {
    namespace PIT
    {
      void Initialize()
      {
	OUTB(0x43, 0x36);
	OUTB(0x40, 0);
	OUTB(0x40, 0);
      }
    }
  }
}
