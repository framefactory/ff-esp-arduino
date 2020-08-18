/**
 * ESP/Arduino Effect Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_EFFECT_DRAWTEST_H
#define _ESP_EFFECT_DRAWTEST_H

#include "../library.h"
#include "../Effect.h"

#include "matrix/Canvas.h"

F_BEGIN_NAMESPACE

class DrawTest : public Effect
{
public:
    virtual bool onRender(const Timing& timing, Bitmap* pBitmap);

private:
    int _oldX = 0;
};

F_END_NAMESPACE

#endif // _ESP_EFFECT_DRAWTEST_H