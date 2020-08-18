/**
 * ESP/Arduino Effect Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "Layer.h"
#include "Composition.h"

F_USE_NAMESPACE

Layer::Layer(Composition* pComposition, MixOp op) :
    Bitmap(pComposition->width(), pComposition->height()),
    _isEnabled(true),
    _pEffect(nullptr),
    _mixOp(op)
{
}

Layer::Layer(int width, int height, MixOp op) :
    Bitmap(width, height),
    _pEffect(nullptr),
    _mixOp(op)
{
}

Layer::~Layer()
{
    F_SAFE_DELETE(_pEffect);
}

void Layer::setEnabled(bool enabled)
{
    _isEnabled = enabled;
}

bool Layer::render(Timing& timing)
{
    if (!_isEnabled) {
        return false;
    }

    return _pEffect->render(timing, this);
}

void Layer::compose(Bitmap* pTarget) 
{
    pTarget->blit(*this, _mixOp);
}

void Layer::setEffect(Effect* pEffect) 
{
    F_SAFE_DELETE(_pEffect);
    _pEffect = pEffect;
}

void Layer::setMixOperation(MixOp op) 
{
    _mixOp = op;
}

