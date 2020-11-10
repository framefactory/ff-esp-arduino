/**
 * ESP/Arduino Effect Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_EFFECT_LAYER_H
#define _ESP_EFFECT_LAYER_H

#include "library.h"
#include "Bitmap.h"
#include "Effect.h"

#include <list>

F_BEGIN_NAMESPACE

class Composition;

class Layer : public Bitmap
{
public:
    Layer(Composition* pComposition, MixOp op = Or);
    Layer(int width, int height, MixOp = Or);
    virtual ~Layer();

    /// Enables or disables rendering of this layer.
    void setEnabled(bool enabled);
    /// Returns true if the layer is enabled, i.e. is rendered.
    bool enabled() const { return _isEnabled; }

    /// Sets the mix operation used when composing this layer.
    void setMixOperation(MixOp op);
    /// Returns the mix operation used when composing this layer.
    MixOp mixOperation() const { return _mixOp; }

    /// Clears the layer before rendering. Default is true.
    void setAutoClear(bool doAutoClear);
    /// Returns true if the layer is cleared before rendering.
    bool autoClear() const { return _doAutoClear; }

    /// Renders all effects to this layer's bitmap.
    bool render(Timing& timing);
    /// Draws this layer onto the given target bitmap using the layer's mix operation.
    void compose(Bitmap* pTarget);

    /// Adds the given effect to the effect list. Takes ownership of the effect.
    void addEffect(Effect* pEffect);
    /// Removes the effect from the effect list and deletes it.
    void removeEffect(Effect* pEffect);
    /// Removes and deletes all effects.
    void clearEffects();

private:
    typedef std::list<Effect*> effectList_t;
    effectList_t _effects;
    
    MixOp _mixOp;

    bool _isEnabled = true;
    bool _doAutoClear = true;
};

F_END_NAMESPACE

#endif // _ESP_EFFECT_LAYER_H