#pragma once
#include "apoccommon.h"
#include "apocfilesystem.h"
#include "apocstream.h"

namespace Apoc
{
  //! TODO
  class UnixFileSystem : public FileSystem
  {
  public:
    static const UInt32 DEFAULT_BLOCK_SIZE = 512;

    enum INODE_TYPE
    {
      INODE_FILE_TYPE,
      INODE_DIRECTORY_TYPE
    };

#pragma pack (push, 1)
    struct SuperBlock
    {
      Byte magicIdentifier[4];
      UInt32 inodeCount;
      UInt32 blockSize;
    };
#pragma pack (pop)

#pragma pack (push, 1)
    struct INode
    {
      UInt32 index;
      UInt8 type;
      UInt32 linkCount;
      UInt32 size;
      UInt32 directBlocks[12];
    };
#pragma pack (pop)

    class Directory : public FileSystem::Directory
    {
    public:
      File* OpenFile(const Character* name);
    };

    class File : public FileSystem::File
    {
      Stream* stream;
    public:
      Stream* GetStream();
    };

  public:
    UnixFileSystem(Stream* source) : FileSystem(source) {}

    FileSystem::Directory* OpenDirectory(const Character* path);

    static void Create(Stream*);
  };
}
