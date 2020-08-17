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
    Layer(Composition* pComposition, Effect* pEffect, MixOp op = Or);
    virtual ~Layer() {}

    void start(Timing& timing);
    void stop(Timing& timing);
    bool render(Timing& timing);

private:
    Composition* _pComposition;
    Effect* _pEffect;
    MixOp _mixOp;
};

F_END_NAMESPACE

#endif // _ESP_EFFECT_LAYER_H