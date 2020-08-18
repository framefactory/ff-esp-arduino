/**
 * ESP/Arduino Effect Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "Effect.h"

F_USE_NAMESPACE

void Effect::start(Timing& timing)
{
    _isRunning = true;
    _offsetFrames = timing.frames;
    _offsetSeconds = timing.seconds;
    onStart(timing);
}

void Effect::stop(Timing& timing)
{
    onStop(timing);
    _isRunning = false;
}

bool Effect::render(Timing& timing, Bitmap* pBitmap)
{
    timing.effectFrames = timing.frames - _offsetFrames;
    timing.effectSeconds = timing.seconds - _offsetSeconds;
    return onRender(timing, pBitmap);
}

void Effect::onStart(const Timing& timing)
{
}

void Effect::onStop(const Timing& timing)
{
}