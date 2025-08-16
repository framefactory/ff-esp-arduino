/**
 * ESP/Arduino Effect Library
 * Copyright 2025 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "DrawTest.h"

F_USE_NAMESPACE

void DrawTest::onRender(Bitmap* pBitmap, const Timing& timing)
{
    int width = pBitmap->width();
    int height = pBitmap->height();

    int x = (sin(timing.effectSeconds * 2.0) * 0.5 + 0.5) * width;

    pBitmap->clear();
    pBitmap->line(x, 0, width - 1 - x, height - 1);
}
