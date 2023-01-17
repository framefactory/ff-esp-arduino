/**
 * ESP/Arduino Net Library
 * Copyright 2023 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_NET_WIFIHUB_H
#define _ESP_NET_WIFIHUB_H

#include "../library.h"
#include "core/Environment.h"

F_BEGIN_NAMESPACE

class WiFiHub
{
public:
    /// Set WiFi to station mode, for connecting to an access point.
    /// Enabling power save will increase latency.
    static bool setStationMode(bool powerSave = false); 

    /// Connect to a WiFi network/access point using the credentials
    /// stored in the "WIFI_SSID" and "WIFI_PASSWORD" environment variables.
    static bool connectWithEnvCredentials(
        const Environment& env, time_t timeoutSeconds = 15);

    WiFiHub();
    virtual ~WiFiHub() {}

private:
};

F_END_NAMESPACE

#endif // _ESP_NET_WIFIHUB_H