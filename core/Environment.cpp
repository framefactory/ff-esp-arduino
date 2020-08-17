/**
 * ESP/Arduino Core Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "Environment.h"
#include <SPIFFS.h>

F_USE_NAMESPACE

Environment::Environment(const String& filePath) :
    _filePath(filePath)
{
}

void Environment::read()
{
    File file = SPIFFS.open(_filePath, FILE_READ);
    if (!file) {
        Serial.printf("Failed to open environment file at '%s'", _filePath.c_str());
        return;
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