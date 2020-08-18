/**
 * ESP/Arduino Effect Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "Composition.h"
#include "Timing.h"

#include <time.h>

F_USE_NAMESPACE

Composition::Composition(int width, int height) :
    Bitmap(width, height),
    _pTiming(new Timing())
{
}

Composition::~Composition()
{
    for (auto pLayer : _layers) {
        delete pLayer;
    }
}

void Composition::fetchRealTime(float timezoneOffset, float dstOffset)
{
    configTime(timezoneOffset * 3600, dstOffset * 3600, "pool.ntp.org", "time.nist.gov");
    while (!time(nullptr)) {
        delay(100);
    }
}

bool Composition::render()
{
    _pTiming->update();
    bool changed = false;

    for (auto pLayer : _layers) {
        changed = pLayer->render(*_pTiming) || changed;
    }

    if (changed) {
        clear();
        for (auto pLayer : _layers) {
            pLayer->compose(this);
        }
    }

    return changed;    
}

size_t Composition::addLayer(Layer* pLayer) 
{
    _layers.push_back(pLayer);
    return _layers.size() - 1;
}

Layer* Composition::addEffectLayer(Effect* pEffect, MixOp op) 
{
    Layer* pLayer = new Layer(this, op);
    pLayer->setEffect(pEffect);
    addLayer(pLayer);
    pEffect->start(*_pTiming);
    return pLayer;
}

void Composition::insertLayerAt(Layer* pLayer, size_t index) 
{
    _layers.insert(_layers.begin() + index, pLayer);
}

void Composition::removeLayerAt(size_t index) 
{
    auto it = _layers.erase(_layers.begin() + index);
    delete *it;    
}
