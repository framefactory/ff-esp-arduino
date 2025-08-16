/**
 * ESP/Arduino Core Library
 * Copyright 2025 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#pragma once

#include "../library.h"
#include <map>

F_BEGIN_NAMESPACE

/// Reads environment variables from a SPIFFS file and provides methods
/// to access and convert the values.
class Environment
{
public:
    Environment(const String& filePath = "/.env");
    virtual ~Environment() {}

    bool read();
    
    const String& get(const String& key, const String& preset = String()) const;
    const char* getCStr(const String& key, const char* pPreset = nullptr) const;
    long getInt(const String& key, long preset = 0) const;
    float getFloat(const String& key, float preset = 0.0f) const;
    double getDouble(const String& key, double preset = 0.0f) const;

    const String& operator[](const String& key) const { return get(key); }
    operator String() const { return toString(); }
    String toString() const;

private:
    typedef std::map<String, String> stringMap_t;
    stringMap_t _variables;
    String _filePath;

};

F_END_NAMESPACE
