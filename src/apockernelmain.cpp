#include "apockernel.h"

namespace Apoc
{
  namespace Kernel
  {
    void Main();
  }
}

extern unsigned long start_ctors, end_ctors, start_dtors, end_dtors;

extern "C" void KernelMain()
{
  // Call static constructors
  for (unsigned long *constructor(&start_ctors); constructor < &end_ctors; ++constructor)
    ((void (*) (void)) (*constructor)) ();

  Apoc::Kernel::Main();

  // Call static destructors
  for (unsigned long *destructor(&start_dtors); destructor < &end_dtors; ++destructor)
    ((void (*) (void)) (*destructor)) ();
}
