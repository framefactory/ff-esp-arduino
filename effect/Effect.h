/**
 * ESP/Arduino Effect Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_EFFECT_EFFECT_H
#define _ESP_EFFECT_EFFECT_H

#include "library.h"
#include "Timing.h"

F_BEGIN_NAMESPACE

class Effect
{
public:
    virtual ~Effect() {}

    void start(Timing& timing);
    void stop(Timing& timing);
    bool render(Timing& timing);

    bool isRunning() const { return _isRunning; }

    virtual void onStart(const Timing& timing);
    virtual void onStop(const Timing& timing);
    virtual bool onRender(const Timing& timing) = 0;

    virtual const String& effectName() const = 0;

private:
    bool _isRunning;
    uint64_t _offsetFrames;
    double _offsetSeconds;
};

F_END_NAMESPACE

#endif // _ESP_EFFECT_EFFECT_H