/**
 * ESP/Arduino Effect Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_EFFECT_CLOCK_H
#define _ESP_EFFECT_CLOCK_H

#include "../library.h"
#include "../Effect.h"

F_BEGIN_NAMESPACE

class Canvas;

class Clock : public Effect
{
public:
    static const String name;

    explicit Clock(Canvas* pCanvas);
    bool onRender(const Timing& timing) override;
    const String& effectName() const { return Clock::name; }
    
private:
    void _format(int value, char* pString, int length, char pad = '0');

    Canvas* _pCanvas;
    int _lastSecond;
};

F_END_NAMESPACE

#endif // _ESP_EFFECT_CLOCK_H