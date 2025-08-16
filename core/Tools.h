/**
 * ESP/Arduino Core Library
 * Copyright 2025 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#pragma once

#include "../library.h"

F_BEGIN_NAMESPACE

class Tools
{
public:
    static void fetchRealTime(float timezoneOffset, float dstOffset);

private:
    Tools() { };
};

F_END_NAMESPACE
