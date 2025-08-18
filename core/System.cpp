/**
 * ESP/Arduino Core Library
 * Copyright 2025 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "System.h"

#include <soc/soc_caps.h>


F_USE_NAMESPACE


int System::getNumCpuCores()
{
    return SOC_CPU_CORES_NUM;
}

bool System::isFpuAvailable()
{
    return SOC_CPU_HAS_FPU;
}