/**
 * ESP/Arduino Effect Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "Clock.h"

#include "../Bitmap.h"
#include "matrix/Canvas.h"
#include "fonts/Fonts.h"
#include "core/math.h"

#include <time.h>

F_USE_NAMESPACE

bool Clock::onRender(const Timing& timing, Bitmap* pBitmap)
{
    if (!isRunning()) {
        return false;
    }

    tm* pTime = timing.localTime();

    _dc[0] = pTime->tm_sec % 10;
    _dc[1] = pTime->tm_sec / 10;
    _dc[2] = pTime->tm_min % 10;
    _dc[3] = pTime->tm_min / 10;
    _dc[4] = pTime->tm_hour % 10;
    _dc[5] = pTime->tm_hour / 10;

    bool changed = false;

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
                pBitmap->drawText(dpstr, &Fonts::fontC64, x, y + offset, Bitmap::Replace);
                char dcchar = '0' + dc;
                char dcstr[2] { dcchar, 0 };
                pBitmap->drawText(dcstr, &Fonts::fontC64, x, y, Bitmap::Replace);

                yp = y;
                changed = true;
            }
        }
    }

    if (changed) {
        pBitmap->set(15, 2);
        pBitmap->set(15, 5);
        pBitmap->set(32, 2);
        pBitmap->set(32, 5);
    }

    // _lastSecond = pTime->tm_sec;

    // char hrs[3], mins[3], secs[3];
    // _format(pTime->tm_hour, hrs, 2);
    // _format(pTime->tm_min, mins, 2);
    // _format(pTime->tm_sec, secs, 2);

    // pBitmap->drawText(hrs, &Fonts::fontC64, -1, 0, 7);
    // pBitmap->drawText(mins, &Fonts::fontC64, 16, 0, 7);
    // pBitmap->drawText(secs, &Fonts::fontC64, 34, 0, 7);

    return changed;
}

void Clock::_format(int value, char* pString, int length, char pad)
{
    char format[5] { '%', '0', '2', 'd', 0 };
    format[1] = pad;
    format[2] = '0' + (length % 10);
    snprintf(pString, length + 1, format, value);
}