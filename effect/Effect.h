/**
 * ESP/Arduino Effect Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_EFFECT_EFFECT_H
#define _ESP_EFFECT_EFFECT_H

#include "library.h"
#include "Composable.h"
#include "Timing.h"
#include "Bitmap.h"

F_BEGIN_NAMESPACE

class Effect : public Composable
{
public:
    virtual ~Effect() {}

    /// Starts the effect.
    void start(Timing& timing);
    /// Stops the effect.
    void stop(Timing& timing);

    /// Draws this layer onto the given target bitmap using the layer's blend operation.
    void render(Bitmap* pTarget, Timing& timing) override;

    /// Returns true if the effect is currently running.
    bool isActive() const { return _isActive; }

protected:
    /// Called when the effect is started.
    virtual void onStart(const Timing& timing);
    /// Called when the effect is stopped.
    virtual void onStop(const Timing& timing);
    /// Called when the effect should render itself. Should return true if the bitmap has changed,
    /// i.e. if any rendering has been performed.
    virtual void onRender(Bitmap* pBitmap, const Timing& timing) = 0;

private:
    uint64_t _offsetFrames = 0;
    double _offsetSeconds = 0.0;
    bool _isActive = false;
};

F_END_NAMESPACE

#endif // _ESP_EFFECT_EFFECT_H