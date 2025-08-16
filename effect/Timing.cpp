/**
 * ESP/Arduino Effect Library
 * Copyright 2025 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "Timing.h"
#include <sys/time.h>

F_USE_NAMESPACE

Timing::Timing() 
{
    gettimeofday(&now, nullptr);
    _start = now.tv_sec + now.tv_usec * 0.000001;
}

void Timing::update()
{
    frames++;
    gettimeofday(&now, nullptr);
    double last = seconds; 
    seconds = now.tv_sec + now.tv_usec * 0.000001 - _start;
    delta = seconds - last;
}
