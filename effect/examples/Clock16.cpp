/**
 * ESP/Arduino Effect Library
 * Copyright 2025 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "Clock16.h"

#include "../Bitmap.h"
#include "core/math.h"

#include <time.h>

F_USE_NAMESPACE

extern const uint8_t data_dm8_c648[] asm("_binary_bin_dm8_c648_bin_start");
static const Bitmap fontC648(128, 64, data_dm8_c648, false);


void Clock16::onRender(Bitmap* pBitmap, const Timing& timing)
{
    if (!isActive()) {
        return;
    }

    tm* pTime = timing.localTime();

    _dc[0] = pTime->tm_sec % 10;
    _dc[1] = pTime->tm_sec / 10;
    _dc[2] = pTime->tm_min % 10;
    _dc[3] = pTime->tm_min / 10;
    _dc[4] = pTime->tm_hour % 10;
    _dc[5] = pTime->tm_hour / 10;

    for (int i = 0; i < 6; ++i) {
        double& t = _t[i];
        int dc = _dc[i];
        int& dp = _dp[i];

        if (dc != dp && t == 0.0) {
            t = timing.seconds;
        }

        int x = _x[i];
        int y = 0;
        static const int offset = 10;

        if (t != 0.0) {
            double f = (timing.seconds - t) * 3.0;
            int& yp = _yp[i];

            if (f <= 1.0) {
                y = -offset + f * offset;
            }
            else {
                y = 0;
                t = 0.0;
                dp = dc;
            }

            if (y != yp) {
                pBitmap->fill(x, 0, 8, 8, Bitmap::Clear);
                char dpchar = '0' + dp;
                char dpstr[2] { dpchar, 0 };
                pBitmap->drawText(dpstr, &fontC648, x, y + offset, Bitmap::Replace);
                char dcchar = '0' + dc;
                char dcstr[2] { dcchar, 0 };
                pBitmap->drawText(dcstr, &fontC648, x, y, Bitmap::Replace);

                yp = y;
            }
        }
    }

    pBitmap->set(15, 2);
    pBitmap->set(15, 5);
    pBitmap->set(32, 2);
    pBitmap->set(32, 5);
}
