/**
 * ESP/Arduino Core Library
 * Copyright 2025 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "Random.h"

F_USE_NAMESPACE

Random::Random(uint32_t seed /* = 1 */) :
    _seed(seed)
{
}

uint32_t Random::generateInt()
{
    _seed = (_a * _seed + _c) % _m;
    return _seed;
}

void Random::setSeed(uint32_t seed)
{
    _seed = seed;
}