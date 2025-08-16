/**
 * ESP/Arduino Core Library
 * Copyright 2025 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#pragma once

#include "../library.h"

#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <string>
#include <iosfwd>


F_BEGIN_NAMESPACE


template <typename REAL>
class Vector2T;

template <typename REAL>
class Vector4T;


template <typename REAL>
class Vector3T
{
public:
    static const Vector3T<REAL> zero;
    static const Vector3T<REAL> ones;
    static const Vector3T<REAL> unitX;
    static const Vector3T<REAL> unitY;
    static const Vector3T<REAL> unitZ;

    //  Constructors and destructor ----------------------------------

    /// Default constructor. Creates an uninitialized 3-vector.
    Vector3T() { }
    /// Creates a 3-vector from the given values.
    Vector3T(REAL x, REAL y, REAL z);
    /// Creates a 3-vector from the given array of values.
    explicit Vector3T(const REAL* pValues);

    //  Conversions --------------------------------------------------

    /// Returns a pointer to the vector's array of values.
    REAL* ptr() { return &x; }
    /// Constant access to the vector's array of values.
    const REAL* ptr() const { return &x; }

    /// Conversion between 3-vectors of different types.
    template<typename T>
    operator Vector3T<T>() const {
        return Vector3T<T>((T)x, (T)y, (T)z);
    }

    //  Access -------------------------------------------------------
    //
    /// Sets the vector's components to the given values.
    void set(REAL x, REAL y, REAL z);
    /// Sets all components to the given value.
    void setAll(REAL v);
    /// Index access.
    REAL& operator[](size_t index);
    /// Const index access.
    const REAL& operator[](size_t index) const;
    /// Copies the vector's values to the given array.
    void copyTo(REAL* pValues) const;
    /// Copies the values from the given array.
    void copyFrom(const REAL* pValues);

    //  Operators ----------------------------------------------------

    /// Component-wise addition of two vectors: Compound-assignment.
    Vector3T<REAL>& operator+=(const Vector3T<REAL>& vec);
    /// Component-wise addition of a scalar: Compound-assignment.
    Vector3T<REAL>& operator+=(REAL scalar);
    /// Component-wise subtraction of two vectors: Compound-assignment.
    Vector3T<REAL>& operator-=(const Vector3T<REAL>& vec);
    /// Component-wise subtraction of a scalar: Compound-assignment.
    Vector3T<REAL>& operator-=(REAL scalar);
    /// Component-wise scalar multiplication: Compound assignment.
    Vector3T<REAL>& operator*=(REAL scalar);
    /// Component-wise scalar division: Compound assignment.
    Vector3T<REAL>& operator/=(REAL scalar);

    /// Returns true if all components of two vectors are equal.
    bool operator==(const Vector3T<REAL>& vec) const;
    /// Returns true if at least one component of the two vectors is different.
    bool operator!=(const Vector3T<REAL>& vec) const;

    //  Public commands ----------------------------------------------

    /// Sets all components of the vector to zero.
    void setZero();
    /// Normalizes the vector to unit length.
    void normalize();
    /// Homogenization of the vector by dividing it by its last component.
    void homogenize();

    //  Public queries -----------------------------------------------

    /// Returns the 2-norm (length) of the vector.
    REAL length() const;
    /// Returns the squared 2-norm of the vector.
    REAL lengthSquared() const;
    /// Returns the normalized vector (unit length).
    Vector3T<REAL> normalized() const;
    /// Returns the homogenized vector.
    Vector3T<REAL> homogenized() const;

    /// Returns the minimum component of the vector.
    inline REAL min() const;
    /// Returns the maximum component of the vector.
    inline REAL max() const;

    /// Returns the dot product of this and the given vector.
    REAL dot(const Vector3T<REAL>& other) const;
    /// Returns the cross product of this and the given vector.
    Vector3T<REAL> cross(const Vector3T<REAL>& other) const;

    /// Returns true if all components are equal to zero.
    bool allZero() const;
    /// Returns true if all components are equal to one.
    bool allOne() const;

    //  Public data --------------------------------------------------

    REAL x;
    REAL y;
    REAL z;
};

// Static members --------------------------------------------------------------

template <typename REAL>
const Vector3T<REAL> Vector3T<REAL>::zero(REAL(0.0), REAL(0.0), REAL(0.0));

template <typename REAL>
const Vector3T<REAL> Vector3T<REAL>::ones(REAL(1.0), REAL(1.0), REAL(1.0));

template <typename REAL>
const Vector3T<REAL> Vector3T<REAL>::unitX(REAL(1.0), REAL(0.0), REAL(0.0));

template <typename REAL>
const Vector3T<REAL> Vector3T<REAL>::unitY(REAL(0.0), REAL(1.0), REAL(0.0));

template <typename REAL>
const Vector3T<REAL> Vector3T<REAL>::unitZ(REAL(0.0), REAL(0.0), REAL(1.0));

// Constructors ----------------------------------------------------------------

template <typename REAL>
inline Vector3T<REAL>::Vector3T(REAL _x, REAL _y, REAL _z)
    : x(_x),
      y(_y),
      z(_z)
{
}

template <typename REAL>
inline Vector3T<REAL>::Vector3T(const REAL* pValues)
    : x(pValues[0]),
      y(pValues[1]),
      z(pValues[2])
{
}

// Access ----------------------------------------------------------------------

template <typename REAL>
inline void Vector3T<REAL>::set(REAL _x, REAL _y, REAL _z)
{
    x = _x;
    y = _y;
    z = _z;
}

template <typename REAL>
inline void Vector3T<REAL>::setAll(REAL scalar)
{
    x = scalar;
    y = scalar;
    z = scalar;
}

template <typename REAL>
inline REAL& Vector3T<REAL>::operator[](size_t index)
{
    assert(index < 3);
    return (&x)[index];
}

template <typename REAL>
inline const REAL& Vector3T<REAL>::operator[](size_t index) const
{
    assert(index < 3);
    return (&x)[index];
}

template <typename REAL>
inline void Vector3T<REAL>::copyTo(REAL* pValues) const
{
    pValues[0] = x;
    pValues[1] = y;
    pValues[2] = z;
}

template <typename REAL>
inline void Vector3T<REAL>::copyFrom(const REAL* pValues)
{
    x = pValues[0];
    y = pValues[1];
    z = pValues[2];
}

// Operators -------------------------------------------------------------------

template <typename REAL>
inline Vector3T<REAL>& Vector3T<REAL>::operator+=(const Vector3T<REAL>& vec)
{
    x += vec.x;
    y += vec.y;
    z += vec.z;
    return *this;
}

template <typename REAL>
inline Vector3T<REAL>& Vector3T<REAL>::operator+=(REAL scalar)
{
    x += scalar;
    y += scalar;
    z += scalar;
    return *this;
}

template <typename REAL>
inline Vector3T<REAL>& Vector3T<REAL>::operator-=(const Vector3T<REAL>& vec)
{
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    return *this;
}

template <typename REAL>
inline Vector3T<REAL>& Vector3T<REAL>::operator-=(REAL scalar)
{
    x -= scalar;
    y -= scalar;
    z -= scalar;
    return *this;
}

template <typename REAL>
inline Vector3T<REAL>& Vector3T<REAL>::operator*=(REAL scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

template <typename REAL>
inline Vector3T<REAL>& Vector3T<REAL>::operator/=(REAL scalar)
{
    REAL s = (REAL)1.0 / scalar;
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

template <typename REAL>
inline bool Vector3T<REAL>::operator==(const Vector3T<REAL>& vec) const
{
    return x == vec.x && y == vec.y && z == vec.z;
}

template <typename REAL>
inline bool Vector3T<REAL>::operator!=(const Vector3T<REAL>& vec) const
{
    return x != vec.x || y != vec.y || z != vec.z;
}

// Public commands -------------------------------------------------------------

template <typename REAL>
inline void Vector3T<REAL>::setZero()
{
    x = y = z = REAL(0.0);
}

template <typename REAL>
inline void Vector3T<REAL>::normalize()
{
    REAL invLength = REAL(1.0) / length();
    x *= invLength;
    y *= invLength;
    z *= invLength;
}

template <typename REAL>
inline void Vector3T<REAL>::homogenize()
{
    x /= z;
    y /= z;
    z = REAL(1.0);
}

// Public queries --------------------------------------------------------------

template <typename REAL>
inline REAL Vector3T<REAL>::length() const
{
    return sqrt(x*x + y * y + z * z);
}

template <typename REAL>
inline REAL Vector3T<REAL>::lengthSquared() const
{
    return x * x + y * y + z * z;
}

template <typename REAL>
inline Vector3T<REAL> Vector3T<REAL>::normalized() const
{
    REAL invLength = REAL(1.0) / length();
    return Vector3T<REAL>(x * invLength, y * invLength, z * invLength);
}

template <typename REAL>
inline Vector3T<REAL> Vector3T<REAL>::homogenized() const
{
    return Vector3T<REAL>(x / z, y / z, REAL(1.0));
}

template <typename REAL>
inline REAL Vector3T<REAL>::min() const
{
    return fTripleMin(x, y, z);
}

template <typename REAL>
inline REAL Vector3T<REAL>::max() const
{
    return fTripleMax(x, y, z);
}

template <typename REAL>
inline REAL Vector3T<REAL>::dot(const Vector3T<REAL>& other) const
{
    return x * other.x + y * other.y + z * other.z;
}

template <typename REAL>
inline Vector3T<REAL> Vector3T<REAL>::cross(const Vector3T<REAL>& other) const
{
    return Vector3T<REAL>(
                y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x);
}

template <typename REAL>
inline bool Vector3T<REAL>::allZero() const
{
    return x == REAL(0.0) && y == REAL(0.0) && z == REAL(0.0);
}

template <typename REAL>
inline bool Vector3T<REAL>::allOne() const
{
    return x == REAL(1.0) && y == REAL(1.0) && z == REAL(1.0);
}

// Related non-member functions ------------------------------------------------

/// Unary minus.
template <typename REAL>
inline Vector3T<REAL> operator-(const Vector3T<REAL>& vec)
{
    return Vector3T<REAL>(-vec.x, -vec.y, -vec.z);
}

/// Addition of two vectors.
template <typename REAL>
inline Vector3T<REAL> operator+(const Vector3T<REAL>& lhs, const Vector3T<REAL>& rhs)
{
    return Vector3T<REAL>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

/// Component-wise addition of a vector and a scalar.
template <typename REAL>
inline Vector3T<REAL> operator+(const Vector3T<REAL>& vec, REAL scalar)
{
    return Vector3T<REAL>(vec.x + scalar, vec.y + scalar, vec.z + scalar);
}

/// Component-wise addition of a scalar and a a vector.
template <typename REAL>
inline Vector3T<REAL> operator+(REAL scalar, const Vector3T<REAL>& vec)
{
    return Vector3T<REAL>(scalar + vec.x, scalar + vec.y, scalar + vec.z);
}

/// Subtraction of two vectors.
template <typename REAL>
inline Vector3T<REAL> operator-(const Vector3T<REAL>& lhs, const Vector3T<REAL>& rhs)
{
    return Vector3T<REAL>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

/// Component-wise subtraction of a vector and a scalar.
template <typename REAL>
inline Vector3T<REAL> operator-(const Vector3T<REAL>& vec, REAL scalar)
{
    return Vector3T<REAL>(vec.x - scalar, vec.y - scalar, vec.z - scalar);
}

/// Component-wise subtraction of a scalar and a vector.
template <typename REAL>
inline Vector3T<REAL> operator-(REAL scalar, const Vector3T<REAL>& vec)
{
    return Vector3T<REAL>(scalar - vec.x, scalar - vec.y, scalar - vec.z);
}

/// Component-wise multiplication of a vector and a scalar.
template <typename REAL>
inline Vector3T<REAL> operator*(const Vector3T<REAL>& vec, REAL scalar)
{
    return Vector3T<REAL>(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

/// Component-wise multiplication of a scalar and a vector.
template <typename REAL>
inline Vector3T<REAL> operator*(REAL scalar, const Vector3T<REAL>& vec)
{
    return Vector3T<REAL>(scalar * vec.x, scalar * vec.y, scalar * vec.z);
}

/// Component-wise division of a vector and a scalar.
template <typename REAL>
inline Vector3T<REAL> operator/(const Vector3T<REAL>& vec, REAL scalar)
{
    REAL inv = REAL(1.0) / scalar;
    return Vector3T<REAL>(vec.x * inv, vec.y * inv, vec.z * inv);
}

/// Component-wise division of a scalar and a vector.
template <typename REAL>
inline Vector3T<REAL> operator/(REAL scalar, const Vector3T<REAL>& vec)
{
    return Vector3T<REAL>(scalar / vec.x, scalar / vec.y, scalar / vec.z);
}

/// Dot product of two vectors.
template <typename REAL>
inline REAL operator*(const Vector3T<REAL>& v1, const Vector3T<REAL>& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

/// Dot product of two vectors.
template <typename REAL>
inline REAL dot(const Vector3T<REAL>& v1, const Vector3T<REAL>& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

/// Cross product of two vectors.
template <typename REAL>
inline Vector3T<REAL> cross(const Vector3T<REAL>& v1, const Vector3T<REAL>& v2)
{
    return Vector3T<REAL>(
                v1.y * v2.z - v1.z * v2.y,
                v1.z * v2.x - v1.x * v2.z,
                v1.x * v2.y - v1.y * v2.x);
}

/// Returns the component-wise minimum of two vectors.
template <typename REAL>
inline Vector3T<REAL> min(const Vector3T<REAL>& v1, const Vector3T<REAL>& v2)
{
    return Vector3T<REAL>(min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z));
}

/// Returns the component-wise maximum of two vectors.
template <typename REAL>
inline Vector3T<REAL> max(const Vector3T<REAL>& v1, const Vector3T<REAL>& v2)
{
    return Vector3T<REAL>(max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z));
}

/// Linear interpolation between two vectors.
template <typename REAL>
inline Vector3T<REAL> lerp(const Vector3T<REAL>& v1, const Vector3T<REAL>& v2, REAL factor)
{
    return Vector3T<REAL>(
                v1.x + factor * (v2.x - v1.x),
                v1.y + factor * (v2.y - v1.y),
                v1.z + factor * (v2.z - v1.z));
}

/// Writes a text representation of the vector to the given stream.
template <typename REAL, typename C>
std::basic_ostream<C, std::char_traits<C>>& operator<<(
        std::basic_ostream<C, std::char_traits<C>>& stream, const Vector3T<REAL>& vec)
{
    stream << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]";
    return stream;
}

// Typedefs --------------------------------------------------------------------

/// 3-component vector of type float
typedef Vector3T<float> Vector3f;

/// 3-component vector of type double
typedef Vector3T<double> Vector3d;

/// 3-component vector of type integer
typedef Vector3T<int32_t> Vector3i;

F_END_NAMESPACE
