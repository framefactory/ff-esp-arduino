/**
 * ESP/Arduino Effect Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_EFFECT_TIMING_H
#define _ESP_EFFECT_TIMING_H

#include "library.h"

#include <sys/time.h>
#include <time.h>

F_BEGIN_NAMESPACE

struct Timing
{
    Timing();

    void update();

    timeval now = { 0, 0 };
    double delta = 0.0;

    uint64_t frames = 0;
    double seconds = 0.0;
    uint64_t effectFrames = 0;
    double effectSeconds = 0.0;

    tm* localTime() const { return ::localtime(&now.tv_sec); }

private:
    double _start;
};

F_END_NAMESPACE

#endif // _ESP_EFFECT_TIMING_H