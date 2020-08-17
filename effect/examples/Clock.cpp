/**
 * ESP/Arduino Effect Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "Clock.h"

#include "matrix/Canvas.h"
#include "matrix/Bitmap.h"
#include "fonts/Fonts.h"

#include <time.h>

F_USE_NAMESPACE

const String Clock::name = "clock";

Clock::Clock(Canvas* pCanvas) :
    _pCanvas(pCanvas),
    _lastSecond(-1)
{
}

bool Clock::onRender(const Timing& timing)
{
    if (!isRunning()) {
        return false;
    }

    tm* pTime = timing.localTime();


    if (pTime->tm_sec == _lastSecond) {
        return false;
    }

    _lastSecond = pTime->tm_sec;

    char hrs[3], mins[3], secs[3];
    _format(pTime->tm_hour, hrs, 2);
    _format(pTime->tm_min, mins, 2);
    _format(pTime->tm_sec, secs, 2);

    _pCanvas->set(14, 2);
    _pCanvas->set(14, 5);
    _pCanvas->set(32, 2);
    _pCanvas->set(32, 5);

    _pCanvas->drawText(hrs, &Fonts::fontC64, -1, 0, 7, false);
    _pCanvas->drawText(mins, &Fonts::fontC64, 16, 0, 7, false);
    _pCanvas->drawText(secs, &Fonts::fontC64, 34, 0, 7, false);

    // char text[128];
    // snprintf(text, 128, "%f", timing.delta);
    // _pCanvas->drawText(text, &font04B24, 0, 0, 4);
    return true;
}

void Clock::_format(int value, char* pString, int length, char pad)
{
    char format[5] { '%', '0', '2', 'd', 0 };
    format[1] = pad;
    format[2] = '0' + (length % 10);
    snprintf(pString, length + 1, format, value);
}