#pragma once
#include "apocsimpleconsole.h"
#include "apocstream.h"

namespace Apoc
{
  class KernelConsole : public SimpleConsole
  {
  public:
    Stream* diskStream;

    static void ShowIDT(const Character**, Console*);
    static void ShowMem(const Character**, Console*);
    static void ShowMemAvail(const Character**, Console*);

    static void DumpMem(const Character**, Console*);
    static void DumpDisk(const Character**, Console*);

    static void WriteMem(const Character**, Console*);
    static void WriteDisk(const Character**, Console*);

    static void CreateFS(const Character**, Console*);
    static void ListFS(const Character**, Console*);

    static void TestMem(const Character**, Console*);

    static void Test(const Character**, Console*);

    KernelConsole(Stream* input = 0, Stream* output = 0);
  };
};
