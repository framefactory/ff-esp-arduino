/**
 * ESP/Arduino Effect Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "DrawTest.h"

F_USE_NAMESPACE

bool DrawTest::onRender(const Timing& timing, Bitmap* pBitmap)
{
    int width = pBitmap->width();
    int height = pBitmap->height();

    int x = (sin(timing.effectSeconds * 2.0) * 0.5 + 0.5) * width;
    if (x == _oldX) {
        return false;
    }

    _oldX = x;
    pBitmap->clear();
    pBitmap->line(x, 0, width - 1 - x, height - 1);
    return true;


    // int secs = int(timing.seconds) % 4;
    // switch(secs) {
    //     case 0:
    //         _pCanvas->ellipse(width / 2, height / 2, width / 2, height / 2);
    //         break;
    //     case 1:
    //         _pCanvas->line(0, 0, width - 1, height - 1);
    //         break;
    //     case 2:
    //         _pCanvas->circle(width / 2, height / 2, height / 2);
    //         break;
    //     case 3:
    //         _pCanvas->rect(1, 1, width - 3, height - 3);
    //         break;
    // }

}
