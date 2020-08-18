/**
 * ESP/Arduino Matrix Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "MAX7219Matrix.h"

F_USE_NAMESPACE

MAX7219Matrix::MAX7219Matrix() :
    SerialDevice(16),
    _rows { 0, 0, 0, 0, 0, 0, 0, 0 },
    _brightness(0x02)
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

void MAX7219Matrix::writeRow(uint32_t index)
{
    writeData(((8 - index) << 8) + _rows[index]);
}

void MAX7219Matrix::writeBrightness()
{
    writeData((Register::INTENSITY << 8) + _brightness);
}

void MAX7219Matrix::writeRegister(uint8_t reg, uint8_t data)
{
    writeData((reg << 8) + data);
}