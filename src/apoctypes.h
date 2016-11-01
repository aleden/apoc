#pragma once
#include "apocconfig.h"

namespace Apoc
{
  //! Guaranteed to be 32 bit float
  typedef float Float32;

  //! Guaranteed to be 64 bit float
  typedef double Float64;

  //! Guaranteed to be 8 bit signed int
  typedef char Int8;
	  
  //! Guaranteed to be 16 bit signed int
  typedef short Int16;
	  
  //! Guaranteed to be 32 bit signed int
  typedef int Int32;

  //! Guaranteed to be 64 bit signed int
  #if APOC_ARCH == APOC_ARCH_X86_64
  typedef long Int64;
  #endif

  //! Guaranteed to be 8 bit unsigned int
  typedef unsigned char UInt8;

  //! Guaranteed to be 16 bit unsigned int
  typedef unsigned short UInt16;
	  
  //! Guaranteed to be 32 bit unsigned int
  typedef unsigned int UInt32;

  //! Guaranteed to be 64 bit unsigned int
  #if APOC_ARCH == APOC_ARCH_X86_64
  typedef unsigned long UInt64;
  #endif

  //! Not a number. A byte (data).
  typedef UInt8 Byte;

  //! Guaranteed to be a signed int having the machine word size
  #if APOC_ARCH == APOC_ARCH_X86_64
  typedef Int64 Int;
  #elif APOC_ARCH == APOC_ARCH_I386
  typedef Int32 Int;
  #endif

  //! Guaranteed to be an unsigned int having the machine word size
  #if APOC_ARCH == APOC_ARCH_X86_64
  typedef UInt64 UInt;
  #elif APOC_ARCH == APOC_ARCH_I386
  typedef UInt32 UInt;
  #endif

  //! Guaranteed to be a float having the machine word size
  #if APOC_ARCH == APOC_ARCH_X86_64
  typedef Float64 Float;
  #elif APOC_ARCH == APOC_ARCH_I386
  typedef Float32 Float;
  #endif

  typedef Int8 Character;
}
