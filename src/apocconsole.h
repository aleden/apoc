#pragma once
#include "apoccommon.h"
#include "apocarray.h"
#include "apocstring.h"
#include "apocstream.h"

namespace Apoc
{
  class TextWindow;

  //! An abstraction which takes user input, and returns user output. Everything else is seperate- this includes how the input string is formed, and how it is displayed. This abstraction works with an input-pipe and an output-pipe.
  class Console
  {
    Stream* inputStream;
    Stream* outputStream;
    const Int8* name;

  public:
    inline Console(Stream* inputStream = 0, Stream* outputStream = 0, const Int8* name = "") : inputStream(inputStream), outputStream(outputStream), name(name) {}

    void ReadInput();

    inline void SetInputStream(Stream* inputStream)
    { this->inputStream = inputStream; }

    inline void SetOutputStream(Stream* outputStream)
    { this->outputStream = outputStream; }

    inline Stream* GetOutputStream()
    { return outputStream; }

    inline Stream* GetInputStream()
    { return inputStream; }

  protected:
    virtual void RunCommand(const Character** args) = 0;
  };
}
