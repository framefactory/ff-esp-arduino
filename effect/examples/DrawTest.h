/**
 * ESP/Arduino Effect Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_EFFECT_DRAWTEST_H
#define _ESP_EFFECT_DRAWTEST_H

#include "../library.h"
#include "../Effect.h"

F_BEGIN_NAMESPACE

class DrawTest : public Effect
{
public:
    void onRender(Bitmap* pBitmap, const Timing& timing) override;
};

F_END_NAMESPACE

#endif // _ESP_EFFECT_DRAWTEST_H