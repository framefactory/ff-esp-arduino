/**
 * ESP/Arduino Effect Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_EFFECT_CLOCK22_H
#define _ESP_EFFECT_CLOCK22_H

#include "../library.h"
#include "../Effect.h"

F_BEGIN_NAMESPACE

/// Draws a clock with moving digits.
/// Format: 00/00 using a 16 x 16 bitmap size.
class Clock22 : public Effect
{
public:
    void onRender(Bitmap* pBitmap, const Timing& timing) override;
    
private:
    double _t[4] { 0.0, 0.0, 0.0, 0.0 };
    int _dc[4] { 0, 0, 0, 0 };
    int _dp[4] { -1, -1, -1, -1 };
    int _yp[4] { 0, 0, 0, 0 };
    int _x[4] { 24, 16, 8, 0 };
    int _y[4] { 1, 1, 0, 0 };
};

F_END_NAMESPACE

#endif // _ESP_EFFECT_CLOCK16_H