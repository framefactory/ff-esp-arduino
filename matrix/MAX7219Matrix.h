/**
 * BitMatrix - Dot Matrix Display Controller
 * Copyright 2025 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#pragma once

#include "../library.h"
#include "SerialDevice.h"

#include <string>

F_BEGIN_NAMESPACE

class SerialChain;

class MAX7219Matrix : public SerialDevice
{
public:
    enum Register {
        NO_OP       = 0x00,
        DIGIT_0     = 0x01,
        DIGIT_1     = 0x02,
        DIGIT_2     = 0x03,
        DIGIT_3     = 0x04,
        DIGIT_4     = 0x05,
        DIGIT_5     = 0x06,
        DIGIT_6     = 0x07,
        DIGIT_7     = 0x08,
        DECODE_MODE = 0x09,
        INTENSITY   = 0x0a,
        SCAN_LIMIT  = 0x0b,
        SHUTDOWN    = 0x0c,
        TEST        = 0x0f,
    };

    MAX7219Matrix();
    virtual ~MAX7219Matrix() {};

    void setRow(uint32_t index, uint8_t value) { _rows[index] = value; }
    uint8_t row(uint32_t index) const { return _rows[index]; }

    void setDot(uint32_t x, uint32_t y, bool value) {
        _rows[y] = value ? (_rows[y] | (1 << x)) : (_rows[y] & ~(1 << x));
    }
    bool dot(uint32_t x, uint32_t y) const {
        return _rows[y] & (1 << x);
    }

    void setLine(uint32_t y, const char* pLine);
    void clear();

    void setBrightness(float value);
    float brightness() const { return _brightness; }

    void writeRow(uint32_t index);
    void writeBrightness(uint8_t maxBrightness);
    void writeRegister(uint8_t reg, uint8_t data);

private:
    uint8_t _rows[8];
    float _brightness = 1.0f;
};

F_END_NAMESPACE
