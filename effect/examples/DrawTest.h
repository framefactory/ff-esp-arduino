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
    static const String name;

    DrawTest(Canvas* pCanvas);
    virtual bool onRender(const Timing& timing);
    const String& effectName() const { return DrawTest::name; }

private:
    Canvas* _pCanvas;
};

F_END_NAMESPACE

#endif // _ESP_EFFECT_DRAWTEST_H