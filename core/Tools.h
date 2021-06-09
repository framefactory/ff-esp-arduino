/**
 * ESP/Arduino Core Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_CORE_TOOLS_H
#define _ESP_CORE_TOOLS_H

#include "../library.h"

F_BEGIN_NAMESPACE

class Tools
{
public:
    static void fetchRealTime(float timezoneOffset, float dstOffset);

private:
    Tools() { };
};

F_END_NAMESPACE

#endif // _ESP_CORE_TOOLS_H