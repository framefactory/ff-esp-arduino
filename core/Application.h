/**
 * ESP/Arduino Core Library
 * Copyright 2023 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_CORE_APPLICATION_H
#define _ESP_CORE_APPLICATION_H

#include "../library.h"
#include "Environment.h"

F_BEGIN_NAMESPACE

/// Base class for ESP32/ESP8266 applications.
class Application
{
public:
    Application();
    virtual ~Application() {}

    /// Setup function, called once at the beginning of the application.
    /// The default implementation initializes the serial port.
    virtual void setup();

    /// Main loop function, called repeatedly during the application's lifetime.
    virtual void loop() = 0;

protected:
    Environment env;
    void connectWifi(const char* ssid, const char* password);
};

F_END_NAMESPACE

#endif // _ESP_CORE_APPLICATION_H