/**
 * ESP/Arduino Net Library
 * Copyright 2025 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "WiFiHub.h"

#include <WiFi.h>
#include <time.h>

F_USE_NAMESPACE

bool WiFiHub::setStationMode(bool powerSave /* = false */)
{
    if (!WiFi.mode(WIFI_STA)) {
        return false;
    }
    if (!WiFi.setSleep(powerSave ? WIFI_PS_MIN_MODEM : WIFI_PS_NONE)) {
        return false;
    }

    return true;
}

bool WiFiHub::connectWithEnvCredentials(
    const Environment& env, time_t timeoutSeconds /* = 15 */)
{
    const char* pSSID = env.getCStr("WIFI_SSID");
    Serial.printf("Connecting to WiFi '%s' ...", pSSID);
    WiFi.begin(pSSID, env.getCStr("WIFI_PASSWORD"));

    time_t start = time(NULL);
    time_t current = start;

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");

        time_t current = time(NULL);
        if (current - start >= timeoutSeconds) {
            Serial.println(" timeout.\nFailed to connect.");
            return false;
        }
    }
    Serial.printf(" done.\nConnected with IP: %s\n", WiFi.localIP().toString());
    return true;
}

WiFiHub::WiFiHub()
{

}