/**
 * ESP/Arduino Effect Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "Clock22.h"

#include "../Bitmap.h"
#include "core/math.h"

#include <time.h>

F_USE_NAMESPACE

extern const uint8_t data_dm8_c64[] asm("_binary_bin_dm8_c64_bin_start");
static const Bitmap fontC64(128, 64, data_dm8_c64, false);


void Clock22::onRender(Bitmap* pBitmap, const Timing& timing)
{
    if (!isActive()) {
        return;
    }

    tm* pTime = timing.localTime();

    _dc[0] = pTime->tm_min % 10;
    _dc[1] = pTime->tm_min / 10;
    _dc[2] = pTime->tm_hour % 10;
    _dc[3] = pTime->tm_hour / 10;

    for (int i = 0; i < 4; ++i) {
        double& t = _t[i];
        int dc = _dc[i];
        int& dp = _dp[i];

        if (dc != dp && t == 0.0) {
            t = timing.seconds;
        }

        int x = _x[i];
        int y = _y[i];
        int yy = 0;
        static const int offset = 10;

        if (t != 0.0) {
            double f = (timing.seconds - t) * 3.0;
            int& yp = _yp[i];

            if (f <= 1.0) {
                yy = -offset + f * offset;
            }
            else {
                yy = 0;
                t = 0.0;
                dp = dc;
            }

            if (yy != yp) {
                pBitmap->fill(x, 0, 8, 8, Bitmap::Clear);
                char dpchar = '0' + dp;
                char dpstr[2] { dpchar, 0 };
                pBitmap->drawText(dpstr, &fontC64, x, y + yy + offset, Bitmap::Replace);
                char dcchar = '0' + dc;
                char dcstr[2] { dcchar, 0 };
                pBitmap->drawText(dcstr, &fontC64, x, y + yy, Bitmap::Replace);

                yp = yy;
            }
        }
    }

    // if (changed) {
    //     pBitmap->set(15, 2);
    //     pBitmap->set(15, 5);
    //     pBitmap->set(32, 2);
    //     pBitmap->set(32, 5);
    // }
}
