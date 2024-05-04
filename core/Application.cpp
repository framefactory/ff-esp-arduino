/**
 * ESP/Arduino Core Library
 * Copyright 2023 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "Application.h"

#include <WiFi.h>

F_USE_NAMESPACE

Application::Application()
{
}

void Application::setup()
{
    Serial.begin(115200);
    Serial.println("[Application.setup] serial port initialized");
}

void Application::connectWifi(const char* ssid, const char* password)
{
     // switch to station mode
    WiFi.mode(WIFI_STA);

    Serial.printf("[Application.connectWifi] Connecting to SSID: %s ", ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    IPAddress ip = WiFi.localIP();
    Serial.printf("\nConnected! IP Address: %s\n", ip.toString().c_str());
}