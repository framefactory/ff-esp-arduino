/**
 * ESP/Arduino Effect Library
 * Copyright 2025 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#pragma once

#include "../library.h"
#include "../Effect.h"

F_BEGIN_NAMESPACE

/// Draws a clock with moving digits.
/// Format: 00:00:00 using a 48 x 8 bitmap size.
class Clock16 : public Effect
{
public:
    void onRender(Bitmap* pBitmap, const Timing& timing) override;
    
private:
    double _t[6] { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    int _dc[6] { 0, 0, 0, 0, 0, 0 };
    int _dp[6] { -1, -1, -1, -1, -1, -1 };
    int _yp[6] { 0, 0, 0, 0, 0, 0 };
    int _x[6] { 41, 34, 23, 16, 6, -1 };
};

F_END_NAMESPACE
