/**
 * ESP/Arduino Effect Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "Composition.h"
#include "Effect.h"
#include "Timing.h"

#include <time.h>

F_USE_NAMESPACE

Composition::Composition(int width, int height) :
    _pTiming(new Timing()),
    _width(width),
    _height(height)
{
}

Composition::~Composition()
{
    for (auto it : _effects) {
        delete it.second;
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

    for (auto it : _effectQueue) {
        changed = it->render(*_pTiming) || changed;
        if (!it->isRunning()) {
            auto it0 = it++;
            _effectQueue.remove(it0);
        }
    }

    return changed;
}

void Composition::startEffect(const String& name)
{
    auto pEffect = _effects.at(name);
    if (pEffect) {
        pEffect->start(*_pTiming);
        _effectQueue.push_front(pEffect);
    }
}

void Composition::stopEffect(const String& name)
{
    auto pEffect = _effects.at(name);
    if (pEffect) {
        pEffect->stop(*_pTiming);
    }
}

void Composition::addEffect(Effect* pEffect, const String& name)
{
    const String& effectName = name.isEmpty() ? pEffect->effectName() : name;
    _effects.emplace(effectName, pEffect);
}

void Composition::removeEffect(const String& name)
{
    _effects.erase(name);
}