#pragma once
#include "apoccommon.h"

namespace Apoc
{
  // #pragma pack(push,1) and #pragma pack(pop) force your compiler 
  // to pack the structure as byte-aligned. 
  #pragma pack (push, 1)

  //! Class for representing a 2d vector. It is guaranteed that
  //! this class will have only the fields x, and y and in
  //! that order, and it will be byte-aligned.
  template <typename T>
  class Vector2d
  {
  public:
    //! The x value
    T x;
    //! The y value
    T y;

    //! Empty constructors, sets fields to zero
    inline Vector2d()
    { x = y = static_cast<T>(0); }
    
    //! Constructor taking in n
    //! \param[in] n The value x and y will be set to
    inline Vector2d(const T& n)
    { x = y = n; }

    //! Constructor taking in x and y
    //! \param[in] x The initial x value
    //! \param[in] y The initial y value
    inline Vector2d(const T& x, const T& y)
    { this->x = x; this->y = y; }
    
    //! Constructor taking in a vector
    //! \param[in] v The vector to be set to
    inline Vector2d(const Vector2d<T>& v)
    { (*this) = v; }
    
    //! Empty deconstructor
    ~Vector2d() {}

    //
    // Comparison/Assignment overloads
    //

    //! Sets the second vector equal to this vector
    //! \param[in] v Sets the vector equal to v
    //! \return this vector
    inline Vector2d<T>& operator = (const Vector2d& v)
    { x = v.x; y = v.y; return *this; }

    //! Sets the number to all the fields of this vector
    //! \param[in] n This is set to all the fields
    //! \return this vector
    inline Vector2d<T>& operator = (const T& n)
    { x = n; y = n; return *this; }

    //! Tests if the number is equal to all the fields 
    //! of this vector
    //! \param[in] rhs The number
    //! \return True if equal, false if not
    inline bool operator == (const T& rhs) const
    { return (x == rhs && y == rhs); }

    //! Tests if the other vector is equal to this vector
    //! \param[in] rhs The other vector
    //! \return True if equal, false if not
    inline bool operator == (const Vector2d<T>& rhs) const
    { return (x == rhs.x && y == rhs.y); }

    //! Tests if the number is not equal to any of the fields 
    //! of this vector
    //! \param[in] rhs The number
    //! \return True if equal, false if not
    inline bool operator != (const T& rhs) const
    { return (x != rhs || y != rhs); }

    //! Tests if the other vector is not equal to this vector
    //! \param[in] rhs The other vector
    //! \return True if equal, false if not
    inline bool operator != (const Vector2d<T>& rhs) const
    { return (x != rhs.x || y != rhs.y); }

    //
    // Arithmetic overloads
    //

    //! Subtracts the other vector from this vector into 
    //! a new vector
    //! \param[in] rhs Other vector
    //! \return The subtracted vector
    inline Vector2d<T> operator - (const Vector2d<T>& rhs) const
    { return Vector2d<T>(x - rhs.x, y - rhs.y); }

    //! Subtracts the number from all the fields of this vector
    //! into a new vector
    //! \param[in] rhs The number
    //! \return The subtracted vector
    inline Vector2d<T> operator - (const T& rhs) const
    { return Vector2d<T>(x - rhs.x, y - rhs.y); }

    //! Subtracts the other vector from this vector
    //! \param[in] rhs Other vector
    //! \return This vector
    inline Vector2d<T>& operator -= (const Vector2d<T>& rhs)
    { x -= rhs.x; y -= rhs.y; return *this; }

    //! Subtracts the number from all the fields of this vector
    //! \param[in] rhs The number
    //! \return This vector
    inline Vector2d<T>& operator -= (const T& rhs)
    { x -= rhs; y -= rhs; return *this; }

    //! Adds the other vector to this vector into
    //! a new vector
    //! \param[in] rhs Other vector
    //! \return The added vector
    inline Vector2d<T> operator + (const Vector2d<T>& rhs) const
    { return Vector2d<T>(x + rhs.x, y + rhs.y); }

    //! Adds the number to all the fields of this vector
    //! into a new vector
    //! \param[in] rhs The number
    //! \return The added vector
    inline Vector2d<T> operator + (const T& rhs) const
    { return Vector2d<T>(x + rhs, y + rhs); }

    //! Adds the other vector to this vector
    //! \param[in] rhs Other vector
    //! \return This vector
    inline Vector2d<T>& operator += (const Vector2d<T>& rhs)
    { x += rhs.x; y += rhs.y; return *this; }

    //! Adds the number to all the fields of this vector
    //! \param[in] rhs The number
    //! \return This vector
    inline Vector2d<T>& operator += (const T& rhs)
    { x += rhs; y += rhs; return *this; }

    //! Multiplies the other vector and this vector into
    //! a new vector
    //! \param[in] rhs Other vector
    //! \return The multiplied vector
    inline Vector2d<T> operator * (const Vector2d<T>& rhs) const
    { return Vector2d<T>(x * rhs.x, y * rhs.y); }

    //! Mutiplies the number to all the fields of this vector
    //! into a new vector
    //! \param[in] rhs The number
    //! \return The multiplied vector
    inline Vector2d<T> operator * (const T& rhs) const
    { return Vector2d<T>(x * rhs, y * rhs); }

    //! Mutiplies the other vector to this vector
    //! \param[in] rhs Other vector
    //! \return This vector
    inline Vector2d<T>& operator *= (const Vector2d<T>& rhs)
    { x *= rhs.x; y *= rhs.y; return *this; }

    //! Mutiplies the number to all the fields of this vector
    //! \param[in] rhs The number
    //! \return This vector
    inline Vector2d<T>& operator *= (const T& rhs)
    { x *= rhs; y *= rhs; return *this; }

    //! Divides this vector by the other vector into
    //! a new vector
    //! \param[in] rhs Other vector
    //! \return The divided vector
    inline Vector2d<T> operator / (const Vector2d<T>& rhs) const
    { return Vector2d<T>(x / rhs.x, y / rhs.y); }

    //! Divides all this vector's fields by the number
    //! into a new vector
    //! \param[in] rhs The number
    //! \return The divided vector
    inline Vector2d<T> operator / (const T& rhs) const
    { return Vector2d<T>(x / rhs, y / rhs); }

    //! Divides this vector by the other vector
    //! \param[in] rhs Other vector
    //! \return This vector
    inline Vector2d<T>& operator /= (const Vector2d<T>& rhs)
    { x /= rhs.x; y /= rhs.y; return *this; }

    //! Divides all the fields of this vector by the number
    //! \param[in] rhs Other number
    //! \return This vector
    inline Vector2d<T>& operator /= (const T& rhs)
    { x /= rhs; y /= rhs; return *this; }
  };

  #pragma pack (pop)

  typedef Vector2d<Float32> Vector2df;
  typedef Vector2d<Int>     Vector2di;
  typedef Vector2d<UInt>    Vector2dui;

  typedef Vector2d<Int> Point2d;
  typedef Vector2dui Size2d;
}
