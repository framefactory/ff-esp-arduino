/**
 * ESP/Arduino Core Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "Application.h"

#ifdef ARDUINO_ESP8266_RELEASE
  #include <ESP8266WiFi.h>
#else
#include <WiFi.h>
  #endif

#include <FS.h>

F_USE_NAMESPACE

Application::Application()
{
}

void Application::setup()
{
    Serial.begin(115200);
    Serial.println();
}

void Application::connectWifi(const char* ssid, const char* password)
{
    Serial.printf("Connecting to WiFi, SSID: %s ", ssid);
    int wifiStatus = WiFi.begin(ssid, password);

    while (wifiStatus != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        
        #ifdef ARDUINO_ESP8266_RELEASE
        wifiStatus = WiFi.status();
        #else
        wifiStatus = WiFi.begin(ssid, password);
        #endif
    }

    IPAddress ip = WiFi.localIP();
    Serial.printf("\nConnected! IP Address: %s\n", ip.toString().c_str());
}