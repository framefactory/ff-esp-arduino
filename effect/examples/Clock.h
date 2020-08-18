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

class Clock : public Effect
{
public:
    virtual bool onRender(const Timing& timing, Bitmap* pBitmap);
    
private:
    void _format(int value, char* pString, int length, char pad = '0');

    double _t[6] { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    int _dc[6] { 0, 0, 0, 0, 0, 0 };
    int _dp[6] { 0, 0, 0, 0, 0, 0 };
    int _yp[6] { 0, 0, 0, 0, 0, 0 };
    int _x[6] { 41, 34, 23, 16, 6, -1 };
};

F_END_NAMESPACE

#endif // _ESP_EFFECT_CLOCK_H