/**
 * ESP/Arduino CORE Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_CORE_MATH_H
#define _ESP_CORE_MATH_H

#include "library.h"

F_BEGIN_NAMESPACE

class Math
{
private:
    Math();

public:
    template<typename T>
    static inline const T& limit(const T& value, const T& min, const T& max) {
        return value < min ? min : (value > max ? max : value);
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

#endif // _ESP_CORE_MATH_H