#include "apockernel.h"
#include "apoccommon.h"
#include "apoctextgraphics.h"
#include "apocstring.h"
#include "apocwindowmanager.h"
#include "apockernelconsole.h"
#include "apocconsolewindow.h"
#include "apocstream.h"
#include "apocmemorymanager.h"
#include "x86/apocx86.h"

#define APOC_VERSION "1.0"

namespace Apoc
{
  namespace Kernel
  {
    KernelConsole kernelConsole;

    static void Initialize();
    static void RunLoop();
    static void Loop();

    void Main()
    {
      Initialize();

      RunLoop();
    }

    static void Initialize()
    {
      X86::PIC::Initialize();
      X86::PIT::Initialize();
      Keyboard::Initialize();
      X86::IDT::Initialize();
      MemoryManager::Initialize();
      WindowManager::Initialize();

      ConsoleWindow kernelConsoleWindow(&kernelConsole);
      WindowManager::AddWindow(&kernelConsoleWindow);
      kernelConsoleWindow.Update();

      for (;;)
      {
      }
    }

    static void RunLoop()
    {
      while (true)
	Loop();
    }

    static void Loop()
    {
    }

    Console* GetConsole()
    { return &kernelConsole; }

    UInt GetVersion()
    { return 1; }

    const Int8* GetVersionString()
    {
      #if APOC_ARCH == APOC_ARCH_X86_32
        static const Int8 apocVersionString[] = "Apoc Kernel " APOC_VERSION " x86-32";
      #elif APOC_ARCH == APOC_ARCH_X86_64
        static const Int8 apocVersionString[] = "Apoc Kernel " APOC_VERSION " x86-64";
      #endif
      
      return apocVersionString;
    }

    const Int8* GetVersionNumberString()
    { return APOC_VERSION; }

    void Log(const Int8* message)
    {
      kernelConsole.GetOutputStream()->WriteString(message);
    }

    void Halt(const Int8* reason)
    {
      kernelConsole.GetOutputStream()->WriteString("SYSTEM FAILURE: ");
      kernelConsole.GetOutputStream()->WriteString(reason);
      
      for (;;);
    }
  }
}

extern "C" void __cxa_pure_virtual()
{}

void *__dso_handle;
 
extern "C" int __cxa_atexit(void (*destructor) (void *), void *arg, void *dso)
{ return 0; }

extern "C" void __cxa_finalize(void *f)
{}
