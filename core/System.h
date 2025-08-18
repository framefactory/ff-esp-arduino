/**
 * ESP/Arduino Core Library
 * Copyright 2025 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#pragma once

#include "../library.h"

F_BEGIN_NAMESPACE

class System
{
public:
    /// Returns the number of CPU cores available on the system.
    static int getNumCpuCores();
    /// Returns true if the system has a floating point unit (FPU).
    static bool isFpuAvailable();
};

F_END_NAMESPACE
