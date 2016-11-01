#pragma once
#include "apoccommon.h"
#include "apocvec2d.h"

namespace Apoc
{
  namespace Math
  {
    //! Constant for 32 bit PI.
    const Float32 PI32 = 3.14159265359f;

    //! Constant for reciprocal of 32 bit PI.
    const Float32 RECIPROCAL_PI32 = 1.f/PI32;

    //! Constant for 64 bit PI.
    const Float64 PI64 = 3.1415926535897932384626433832795028841971693993751;

    //! Constant for 64 bit reciprocal of PI.
    const Float64 RECIPROCAL_PI64 = 1.0/PI64;

    template <typename T>
    T Power(T value, UInt power)
    {
      if (power == 0)
        return 1;

      T ret = 1;
      for (UInt i = 0; i < power; ++i)
        ret *= value;

      return ret;
    }

    inline Int Ceil(Float32 x)
    {
      const Float32 h = 0.5f;

      Int t;

      __asm__ __volatile__ (
      "fadd %2 \n\t"
      "fistpl %0 \n\t"
      : "=m"(t)
      : "t"(x), "f"(h)
      : "st"
      );
      return t;
    }

    inline Int Round(Float32 x)
    {
      Int t;

      __asm__ __volatile__ (
      "fistpl %0 \n\t"
      : "=m"(t)
      : "t"(x)
      : "st"
      );
      return t;
    }
  }
}
