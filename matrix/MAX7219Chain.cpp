/**
 * ESP/Arduino Matrix Library
 * Copyright 2023 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "MAX7219Chain.h"
#include "MAX7219Matrix.h"

F_USE_NAMESPACE

MAX7219Chain::MAX7219Chain(uint8_t dataPin) :
    SerialChain(dataPin)
{
}

MAX7219Matrix* MAX7219Chain::createMatrix()
{
    MAX7219Matrix* pMatrix = new MAX7219Matrix();
    _devices.push_back(pMatrix);
    updateBitCount();
    return pMatrix;
}

MAX7219Matrices MAX7219Chain::createMatrices(uint32_t count)
{
    MAX7219Matrices matrices; 

    for (uint32_t i = 0; i < count; ++i) {
        MAX7219Matrix* pMatrix = new MAX7219Matrix();
        _devices.push_back(pMatrix);
        matrices.push_back(pMatrix);
    }

    updateBitCount();
    return matrices;
}

MAX7219Matrix* MAX7219Chain::matrix(uint32_t index) const
{
    return static_cast<MAX7219Matrix*>(_devices[index]);
}

void MAX7219Chain::clear()
{
    for (auto pDevice : _devices) {
        static_cast<MAX7219Matrix*>(pDevice)->clear();
    }
}

void MAX7219Chain::setBrightness(uint8_t value)
{
    for (auto pDevice : _devices) {
        static_cast<MAX7219Matrix*>(pDevice)->setBrightness(value);
    }
}

void MAX7219Chain::writeRow(uint8_t index)
{
    for (auto pDevice : _devices) {
        static_cast<MAX7219Matrix*>(pDevice)->writeRow(index); 
    }
}

void MAX7219Chain::writeBrightness(uint8_t maxBrightness)
{
    for (auto pDevice : _devices) {
        static_cast<MAX7219Matrix*>(pDevice)->writeBrightness(maxBrightness); 
    }
}

void MAX7219Chain::writeRegister(uint8_t reg, uint8_t data)
{
    for (auto pDevice : _devices) {
        static_cast<MAX7219Matrix*>(pDevice)->writeRegister(reg, data); 
    }
}