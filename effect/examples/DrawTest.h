/**
 * ESP/Arduino Effect Library
 * Copyright 2025 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#pragma once

#include "../library.h"
#include "../Effect.h"

F_BEGIN_NAMESPACE

class DrawTest : public Effect
{
public:
    void onRender(Bitmap* pBitmap, const Timing& timing) override;
};

F_END_NAMESPACE
