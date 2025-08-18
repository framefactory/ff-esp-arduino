/**
 * ESP/Arduino Core Library
 * Copyright 2025 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#pragma once

#include "../library.h"
#include <math.h>

F_BEGIN_NAMESPACE

#define F_PI		3.1415926535897932384626433832795
#define F_2PI		6.283185307179586476925286766559
#define F_PI2		1.5707963267948966192313216916398
#define F_PI4		0.78539816339744830961566084581988
#define F_INVPI     0.31830988618379067153776752674503
#define F_EULER		2.7182818284590452353602874713526624977572
#define F_R2D		57.295779513082320876798154814114
#define F_D2R		0.017453292519943295769236907684883

class Math
{
private:
    Math();

public:
    /// Mathematical constant pi.
    static const double pi;
    /// Pi times 2.
    static const double pi2;
    /// Pi divided by 2.
    static const double piHalf;
    /// Pi divided by 4.
    static const double piQuarter;

    /// Euler's number.
    static const double e;

    /// Multiplication constant for radian to degree conversion.
    static const double r2d;
    /// Multiplication constant for degree to radian conversion.
    static const double d2r;

    /// Keeps value within the interval [min, max].
    template<typename T>
    static inline const T& clamp(const T& value, const T& min, const T& max) {
        return value < min ? min : (value > max ? max : value);
    }

    /// Returns the smallest of the three values.
    template<typename T>
    static inline const T& tripleMin(const T& a, const T& b, const T& c) {
        return a < b ? (a < c ? a : c) : (b < c ? b : c);
    }

    /// Returns the largest of the three values.
    template<typename T>
    static inline const T& tripleMax(const T& a, const T& b, const T& c) {
        return a > b ? (a > c ? a : c) : (b > c ? b : c);
    }

    template<typename T>
    static inline T easeQuad(T t) {
        return t < T(0.5) ? T(2) * t * t : T(-1) + (T(4.0) - T(2.0) * t) * t;
    }

    template<typename T>
    static inline T easeInQuad(T t) {
        return t * t;
    }

    template<typename T>
    static inline T easeOutQuad(T t) {
        return t * (T(2) - t);
    }

    template<typename T>
    static inline T random(T lower, T upper) {
        return lower + T(std::rand()) / T(RAND_MAX) * (upper - lower);
    }
};

F_END_NAMESPACE
