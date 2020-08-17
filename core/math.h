/**
 * ESP/Arduino CORE Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_CORE_MATH_H
#define _ESP_CORE_MATH_H

#include "library.h"

F_BEGIN_NAMESPACE

template<typename T>
inline const T& limit(const T& value, const T& min, const T& max) {
    return value < min ? min : (value > max ? max : value);
} 

F_END_NAMESPACE

#endif // _ESP_CORE_MATH_H