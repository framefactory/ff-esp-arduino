/**
 * ESP/Arduino Core Library
 * Copyright 2025 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#pragma once

#include "../library.h"
#include "core/Math.h"

F_BEGIN_NAMESPACE

class FastMath
{
public:
    /// Fast polynomial approximation of sine function in [-0.5, 0.5], returns value in [-0.25, 0.25].
    template<typename T>
    static inline T normSin(T x)
    {
    // Source: https://bmtechjournal.wordpress.com/2020/05/27/super-fast-quadratic-sinusoid-approximation/
        x = x - floor(x) - T(0.5);
        T x2 = T(2.0) * x;
        return x2 * (T(1.0) - abs(x2));
    }

    template<typename T>
    static inline T sin(T x)
    {
        return T(4.0) * normSin(x * T(F_INVPI));
    }

    template<typename T>
    static inline T cos(T x)
    {
        constexpr T tp = T(1) / T(2.0 * F_PI);
        x *= tp;
        x -= T(.25) + std::floor(x + T(.25));
        x *= T(16.) * (std::abs(x) - T(.5));
    
        return x;
    }
};

F_END_NAMESPACE