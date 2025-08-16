/**
 * ESP/Arduino Core Library
 * Copyright 2025 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#pragma once

#include "../library.h"

F_BEGIN_NAMESPACE

class Random
{
public:
    Random(uint32_t seed = 1);
    virtual ~Random() {}

    uint32_t generateInt();
    void setSeed(uint32_t seed);

private:
    static const uint32_t _a = 1103515245;
    static const uint32_t _m = 2147483648;
    static const uint32_t _c = 12345;
    uint32_t _seed;
};

F_END_NAMESPACE
