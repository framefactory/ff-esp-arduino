/**
 * ESP/Arduino Effect Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_EFFECT_EFFECT_H
#define _ESP_EFFECT_EFFECT_H

#include "library.h"
#include "Timing.h"
#include "Bitmap.h"

F_BEGIN_NAMESPACE

class Effect
{
public:
    virtual ~Effect() {}

    /// Starts the effect.
    void start(Timing& timing);
    /// Stops the effect.
    void stop(Timing& timing);
    /// Renders the effect to the given bitmap.
    bool render(Timing& timing, Bitmap* pBitmap);

    /// Returns true if the effect is currently running.
    bool isRunning() const { return _isRunning; }

protected:
    /// Called when the effect is started.
    virtual void onStart(const Timing& timing);
    /// Called when the effect is stopped.
    virtual void onStop(const Timing& timing);
    /// Called when the effect should render itself. Should return true if the bitmap has changed,
    /// i.e. if any rendering has been performed.
    virtual bool onRender(const Timing& timing, Bitmap* pBitmap) = 0;

private:
    uint64_t _offsetFrames;
    double _offsetSeconds;
    bool _isRunning;
};

F_END_NAMESPACE

#endif // _ESP_EFFECT_EFFECT_H