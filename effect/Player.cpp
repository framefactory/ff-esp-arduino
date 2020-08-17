/**
 * ESP/Arduino Effect Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "Player.h"
#include "Effect.h"
#include "Timing.h"

#include <time.h>

F_USE_NAMESPACE

Player::Player()
{
    _pTiming = new Timing();
}

void Player::fetchRealTime(float timezoneOffset, float dstOffset)
{
    configTime(timezoneOffset * 3600, dstOffset * 3600, "pool.ntp.org", "time.nist.gov");
    while (!time(nullptr)) {
        delay(100);
    }
}

bool Player::render()
{
    _pTiming->update();
    bool changed = false;

    for (auto it : _effects) {
        changed = it.second->render(*_pTiming) || changed;
    }

    return changed;
}

void Player::startEffect(const String& name)
{
    auto pEffect = _effects.at(name);
    if (pEffect) {
        pEffect->start(*_pTiming);
    }
}

void Player::stopEffect(const String& name)
{
    auto pEffect = _effects.at(name);
    if (pEffect) {
        pEffect->stop(*_pTiming);
    }
}

void Player::addEffect(Effect* pEffect, const String& name)
{
    const String& effectName = name.isEmpty() ? pEffect->effectName() : name;
    _effects.emplace(effectName, pEffect);
}

void Player::removeEffect(const String& name)
{
    _effects.erase(name);
}