/**
 * ESP/Arduino Core Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_CORE_APPLICATION_H
#define _ESP_CORE_APPLICATION_H

#include "library.h"
#include "Environment.h"

F_BEGIN_NAMESPACE

class Application
{
public:
    Application();
    virtual ~Application() {}

    virtual void setup();
    virtual void loop() = 0;

protected:
    Environment env;
    void connectWifi(const char* ssid, const char* password);
};

F_END_NAMESPACE

#endif // _ESP_CORE_APPLICATION_H