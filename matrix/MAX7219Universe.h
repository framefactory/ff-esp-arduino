/**
 * ESP/Arduino Matrix Library
 * Copyright 2025 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#pragma once

#include "../library.h"
#include "SerialUniverse.h"

F_BEGIN_NAMESPACE

class MAX7219Chain;

class MAX7219Universe : public SerialUniverse
{
public:
    typedef std::vector<MAX7219Chain*> chainVec_t;

    MAX7219Universe(int clockPin, int loadPin, uint32_t delayMicroseconds = 1);
    virtual ~MAX7219Universe() {}

    MAX7219Chain* createChain(int dataPin);
    MAX7219Chain* chain(uint32_t index);
 
    virtual void initialize() override;
    void shutdown(bool state);

    void setMaxBrightness(uint8_t value);
    void setGlobalBrightness(float value);

    void write();
    void writeDisplay();
    void writeRow(uint8_t index);
    void writeBrightness();
    void writeRegister(uint8_t reg, uint8_t data);

private:
    uint8_t _maxBrightness = 1;
};

F_END_NAMESPACE
