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
    _mixOp(op)
{
}

Layer::Layer(int width, int height, MixOp op) :
    Bitmap(width, height),
    _mixOp(op)
{
}

Layer::~Layer()
{
    clearEffects();
}

void Layer::setEnabled(bool enabled)
{
    _isEnabled = enabled;
}

void Layer::setMixOperation(MixOp op) 
{
    _mixOp = op;
}

void Layer::setAutoClear(bool doAutoClear)
{
    _doAutoClear = doAutoClear;
}

bool Layer::render(Timing& timing)
{
    if (!_isEnabled) {
        return false;
    }

    bool changed = _doAutoClear;
    if (_doAutoClear) {
        clear();
    }

    for (auto pEffect : _effects) {
        changed = pEffect->render(timing, this) | changed;
    }

    return changed;
}

void Layer::compose(Bitmap* pTarget) 
{
    pTarget->blit(*this, _mixOp);
}

void Layer::addEffect(Effect* pEffect) 
{
    _effects.push_back(pEffect);
}

void Layer::removeEffect(Effect* pEffect)
{
    _effects.remove(pEffect);
    delete pEffect;
}

void Layer::clearEffects()
{
    for (auto pEffect : _effects) {
        delete pEffect;
    }

    _effects.clear();
}
