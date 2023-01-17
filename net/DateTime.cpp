/**
 * ESP/Arduino Net Library
 * Copyright 2023 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "DateTime.h"
#include <time.h>

F_USE_NAMESPACE

void DateTime::config(int zoneShiftHours, int dstHours)
{
    configTime(zoneShiftHours * 3600, dstHours * 3600, "pool.ntp.org", "time.nist.gov");
    while (!time(nullptr)) {
        delay(100);
    }
}

void DateTime::now()
{
    _now = time(nullptr);
    _pTime = localtime(&_now);
}

void DateTime::toHourString(char* pHour, int length, char pad)
{
    format(_pTime->tm_hour, pHour, length, pad);
}

void DateTime::toMinuteString(char* pMinute, int length, char pad)
{
    format(_pTime->tm_min, pMinute, length, pad);
}

void DateTime::toSecondString(char* pSecond, int length, char pad)
{
    format(_pTime->tm_sec, pSecond, length, pad);
}

void DateTime::toDayString(char* pDay, int length, char pad)
{
    format(_pTime->tm_mday, pDay, length, pad);
}

void DateTime::toMonthString(char* pMonth, int length, char pad)
{
    format(_pTime->tm_mon, pMonth, length, pad);
}

void DateTime::toYearString(char* pYear, int length, char pad)
{
    int year = _pTime->tm_year % 100;
    format(year, pYear, length, pad);
}

void DateTime::format(int value, char* pString, int length, char pad)
{
    char format[5] { '%', '0', '2', 'd', 0 };
    format[1] = pad;
    format[2] = '0' + (length % 10);
    snprintf(pString, length + 1, format, value);
}