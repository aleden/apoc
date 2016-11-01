#include "apocfilesystem.h"
#include "apocunixfilesystem.h"

namespace Apoc
{
  FileSystem* FileSystem::Open(Stream* source, TYPE type)
  {
    return 0;
  }

  FileSystem* FileSystem::Open(Stream* source)
  {
    return 0;
  }

  void (*fsCreators[1])(Stream*) =
  {
    UnixFileSystem::Create
  };

  void FileSystem::Create(Stream* stream, TYPE type)
  { fsCreators[type](stream); }
}
