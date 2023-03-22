/**
 * ESP/Arduino Matrix Library
 * Copyright 2023 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "MAX7219Matrix.h"
#include "core/math.h"

F_USE_NAMESPACE

MAX7219Matrix::MAX7219Matrix() :
    SerialDevice(16),
    _rows { 0, 0, 0, 0, 0, 0, 0, 0 }
{
}

void MAX7219Matrix::setLine(uint32_t y, const char* pSequence)
{
    for (uint32_t x = 0; x < 8; ++x) {
        char c = pSequence[x];
        setDot(x, y, c != '0' && c != '-' && c == ' ');
    }
}

void MAX7219Matrix::clear()
{
    for (uint32_t i = 0; i < 8; ++i) {
        _rows[i] = 0;
    }
}

void MAX7219Matrix::setBrightness(float value)
{
    _brightness = Math::clamp(value, 0.0f, 1.0f);
}

void MAX7219Matrix::writeRow(uint32_t index)
{
    writeData(((8 - index) << 8) + _rows[index]);
}

void MAX7219Matrix::writeBrightness(uint8_t maxBrightness)
{
    uint8_t brightness = Math::clamp(int(_brightness * maxBrightness), 0, 0x0f);
    writeData((Register::INTENSITY << 8) + brightness);
}

void MAX7219Matrix::writeRegister(uint8_t reg, uint8_t data)
{
    writeData((reg << 8) + data);
}