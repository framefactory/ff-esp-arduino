/**
 * ESP/Arduino Net Library
 * Copyright 2023 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_NET_DATETIME_H
#define _ESP_NET_DATETIME_H

#include "../library.h"

struct tm;

F_BEGIN_NAMESPACE

class DateTime
{
public:
    void config(int zoneShiftHours, int dstHours);
    void now();

    void toHourString(char* pHour, int length = 2, char pad = '0');
    void toMinuteString(char* pMinute, int length = 2, char pad = '0');
    void toSecondString(char* pSecond, int length = 2, char pad = '0');

    void toDayString(char* pDay, int length = 2, char pad = '0');
    void toMonthString(char* pMonth, int length = 2, char pad = '0');
    void toYearString(char* pYear, int length = 2, char pad = '0');

private:
    void format(int value, char* pString, int length, char pad);

    long _now;
    tm* _pTime;
};

F_END_NAMESPACE

#endif // _ESP_NET_DATETIME_H