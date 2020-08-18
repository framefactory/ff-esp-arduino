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

F_BEGIN_NAMESPACE

class Composition;

class Layer : public Bitmap
{
public:
    Layer(Composition* pComposition, MixOp op = Or);
    Layer(int width, int height, MixOp = Or);
    virtual ~Layer();

    void setEnabled(bool enabled);
    bool enabled() const { return _isEnabled; }

    bool render(Timing& timing);
    void compose(Bitmap* pTarget);

    void setEffect(Effect* pEffect);
    Effect* effect() { return _pEffect; }

    void setMixOperation(MixOp op);
    MixOp mixOperation() const { return _mixOp; }

private:
    bool _isEnabled;
    Effect* _pEffect;
    MixOp _mixOp;
};

F_END_NAMESPACE

#endif // _ESP_EFFECT_LAYER_H