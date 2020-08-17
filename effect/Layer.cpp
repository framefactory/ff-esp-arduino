/**
 * ESP/Arduino Effect Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "Layer.h"
#include "Composition.h"

F_USE_NAMESPACE

Layer::Layer(Composition* pComposition, Effect* pEffect, MixOp op) :
    Bitmap(pComposition->width(), pComposition->height()),
    _pComposition(pComposition),
    _pEffect(pEffect),
    _mixOp(op)
{
}

void Layer::start(Timing& timing)
{
    _pEffect->start(timing);
}

void Layer::stop(Timing& timing)
{
    _pEffect->stop(timing);
}

bool Layer::render(Timing& timing)
{
    return _pEffect->render(timing);
}
