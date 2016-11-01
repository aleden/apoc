#include "apocunixfilesystem.h"
#include "apocalgorithms.h"
#include "apocdiskio.h"

namespace Apoc
{
  FileSystem::Directory* UnixFileSystem::OpenDirectory(const Character* path)
  {
    UnixFileSystem::Directory* directory = new UnixFileSystem::Directory;
    return directory;
  }

  FileSystem::File* UnixFileSystem::Directory::OpenFile(const Character* name)
  {
    UnixFileSystem::File* file = new UnixFileSystem::File;
    return file;
  }

  Stream* UnixFileSystem::File::GetStream()
  {
    return stream;
  }

  void UnixFileSystem::Create(Stream* stream)
  {
    //
    // |  Super Block  |  INode Block   |  Data Block   |
    // |               |                |               |
    // |  1 Sector     |  20 Sectors    |  ~Sectors     |
    // |               |                |               |
    //
    SuperBlock superBlock;
    superBlock.magicIdentifier[0] = 'U';
    superBlock.magicIdentifier[1] = 'F';
    superBlock.magicIdentifier[2] = 'S';
    superBlock.magicIdentifier[3] = '\0';
    superBlock.inodeCount = 0;
    superBlock.blockSize = DEFAULT_BLOCK_SIZE;

    stream->Write(superBlock);

    stream->Jump(DiskIO::SECTOR_SIZE);

    INode rootNode;
    rootNode.index = superBlock.inodeCount++;
    rootNode.type = INODE_DIRECTORY_TYPE;
    rootNode.linkCount = 0;
    rootNode.size = 0;
    CopyValue(rootNode.directBlocks, rootNode.directBlocks + sizeof(rootNode.directBlocks), 0);
  }
}
