/**
 * ESP/Arduino Core Library
 * Copyright 2025 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "Tools.h"
#include <time.h>

F_USE_NAMESPACE

void Tools::fetchRealTime(float timezoneOffset, float dstOffset)
{
    // start async request to time servers
    Serial.print("Fetching time");
    configTime(timezoneOffset * 3600, dstOffset * 3600, "pool.ntp.org", "time.nist.gov");

    // wait until time is adjusted (more than a day away from epoch)
    while (time(nullptr) < 24 * 3600) {
        Serial.print(".");
        delay(500);
    }

    Serial.println();
}