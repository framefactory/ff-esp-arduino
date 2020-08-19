/**
 * ESP/Arduino Core Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "Environment.h"

#ifdef ARDUINO_ESP8266_RELEASE
#include <FS.h>
#else
#include <SPIFFS.h>
#endif

F_USE_NAMESPACE

Environment::Environment(const String& filePath) :
    _filePath(filePath)
{
}

bool Environment::read()
{
    SPIFFS.begin();
    #ifdef ARDUINO_ESP8266_RELEASE
    File file = SPIFFS.open(_filePath, "r");
    #else
    File file = SPIFFS.open(_filePath, FILE_READ);
    #endif
    
    if (!file) {
        Serial.printf("Failed to open environment file at '%s'", _filePath.c_str());
        return false;
    }

    _variables.clear();

    while(file.available()) {
        String line = file.readStringUntil('\n');
        int sep = line.indexOf('=');

        if (sep > 0) {
            String key = line.substring(0, sep);
            key.trim();

            String value = line.substring(sep + 1);
            value.trim();

            _variables.emplace(key, value);    
        }
    }

    return true;
}

const String& Environment::get(const String& key, const String& preset) const
{
        auto it = _variables.find(key);
    if (it != _variables.end()) {
        return it->second;
    }

    return preset;
}

const char* Environment::getCStr(const String& key, const char* pPreset) const
{
    auto it = _variables.find(key);
    if (it != _variables.end()) {
        return it->second.c_str();
    }

    return pPreset;
}

long Environment::getInt(const String& key, long preset) const
{
    auto it = _variables.find(key);
    if (it != _variables.end()) {
        return it->second.toInt();
    }

    return preset;
}

float Environment::getFloat(const String& key, float preset) const
{
    auto it = _variables.find(key);
    if (it != _variables.end()) {
        return it->second.toFloat();
    }

    return preset;
}

double Environment::getDouble(const String& key, double preset) const
{
    auto it = _variables.find(key);
    if (it != _variables.end()) {
        return it->second.toDouble();
    }

    return preset;
}

String Environment::toString() const
{
    String result;

    for (auto it : _variables) {
        result += it.first + "=" + it.second + "\n";
    }

    return result;
}