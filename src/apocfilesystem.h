#pragma once
#include "apoccommon.h"
#include "apocstream.h"

namespace Apoc
{
  class FileSystem
  {
  public:
    enum TYPE
    {
      TYPE_UNIX
    };

    class File;

    class Directory
    {
    public:
      virtual inline ~Directory() {}

      virtual File* OpenFile(const Character* name) = 0;
    };

    class File
    {
    public:
      enum ACCESS
      {
        ACCESS_READ,
        ACCESS_WRITE,
        ACCESS_ALL
      };

    public:
      virtual inline ~File() {}

      virtual Stream* GetStream() = 0;
    };

  private:
    TYPE type;
    Stream* source;

  protected:
    inline Stream* GetSource()
    { return source; }

  public:
    FileSystem(Stream* source) : source(source) {}
    virtual ~FileSystem() {}

    virtual Directory* OpenDirectory(const Character* path) = 0;

    static FileSystem* Open(Stream*, TYPE);
    static FileSystem* Open(Stream*);

    static void Create(Stream*, TYPE);
  };
}
