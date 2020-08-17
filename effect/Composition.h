/**
 * ESP/Arduino Effect Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_EFFECT_COMPOSITION_H
#define _ESP_EFFECT_COMPOSITION_H

#include "library.h"
#include "Bitmap.h"

#include <map>
#include <list>

F_BEGIN_NAMESPACE

class Effect;
class Timing;

class Composition
{
public:
    Composition(int width, int height);
    virtual ~Composition();

    void fetchRealTime(float timezoneOffset, float dstOffset);
    bool render();

    void startEffect(const String& name);
    void stopEffect(const String& name);

    void addEffect(Effect* pEffect, const String& name = "");
    void removeEffect(const String& name);

    const Timing* timing() const { return _pTiming; }
    int width() const { return _width; }
    int height() const { return _height; }

private:
    typedef std::map<String, Effect*> effectMap_t;
    typedef std::list<Effect*> effectQueue_t;
    effectMap_t _effects;
    effectQueue_t _effectQueue;
    Timing* _pTiming;
    int _width;
    int _height;
};

F_END_NAMESPACE

#endif // _ESP_EFFECT_COMPOSITION_H