/**
 * ESP/Arduino Effect Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_EFFECT_PLAYER_H
#define _ESP_EFFECT_PLAYER_H

#include "library.h"

#include <map>

F_BEGIN_NAMESPACE

class Effect;
class Timing;

class Player
{
public:
    Player();
    virtual ~Player() {}

    void fetchRealTime(float timezoneOffset, float dstOffset);
    bool render();

    void startEffect(const String& name);
    void stopEffect(const String& name);

    void addEffect(Effect* pEffect, const String& name = "");
    void removeEffect(const String& name);

    const Timing* timing() const { return _pTiming; }

private:
    typedef std::map<String, Effect*> effectMap_t;
    effectMap_t _effects;
    Timing* _pTiming;
};

F_END_NAMESPACE

#endif // _ESP_EFFECT_PLAYER_H