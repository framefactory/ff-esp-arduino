/**
 * ESP/Arduino Matrix Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "MAX7219Universe.h"
#include "MAX7219Chain.h"
#include "MAX7219Matrix.h"

F_USE_NAMESPACE

MAX7219Universe::MAX7219Universe(int clockPin, int loadPin, uint32_t delayMicroseconds /* = 1 */) :
    SerialUniverse(clockPin, loadPin, delayMicroseconds)
{
}

MAX7219Chain* MAX7219Universe::createChain(int dataPin)
{
    MAX7219Chain* pChain = new MAX7219Chain(dataPin);
    _chains.push_back(pChain);
    return pChain;
}

MAX7219Chain* MAX7219Universe::chain(uint32_t index)
{
    return static_cast<MAX7219Chain*>(_chains[index]);
}

void MAX7219Universe::initialize()
{
    SerialUniverse::initialize();

    for (auto pChain : _chains) {
        pChain->initialize();
    }

    writeRegister(MAX7219Matrix::Register::TEST, 0x00);
    writeRegister(MAX7219Matrix::Register::SHUTDOWN, 0x01);
    writeRegister(MAX7219Matrix::Register::DECODE_MODE, 0x00);
    writeRegister(MAX7219Matrix::Register::SCAN_LIMIT, 0x07);
    writeBrightness();
    writeDisplay();
}

void MAX7219Universe::setBrightness(uint8_t value)
{
    for (auto pChain : _chains) {
        static_cast<MAX7219Chain*>(pChain)->setBrightness(value);
    }
}

void MAX7219Universe::shutdown(bool state)
{
    writeRegister(MAX7219Matrix::Register::SHUTDOWN, state ? 0x00 : 0x01);
}

void MAX7219Universe::write()
{
    writeBrightness();
    writeDisplay();
}

void MAX7219Universe::writeDisplay()
{
    for (uint8_t i = 0; i < 8; ++i) {
        writeRow(i);
    }
} 

void MAX7219Universe::writeRow(uint8_t index)
{
    for (auto pChain : _chains) {
        static_cast<MAX7219Chain*>(pChain)->writeRow(index);
    }

    flush();
}

void MAX7219Universe::writeBrightness()
{
    for (auto pChain : _chains) {
        static_cast<MAX7219Chain*>(pChain)->writeBrightness();
    }

    flush();
}

void MAX7219Universe::writeRegister(uint8_t reg, uint8_t data)
{
    for (auto pChain : _chains) {
        static_cast<MAX7219Chain*>(pChain)->writeRegister(reg, data);
    }

    flush();
}
