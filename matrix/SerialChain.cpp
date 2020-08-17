/**
 * ESP/Arduino Matrix Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "SerialChain.h"
#include "SerialDevice.h"


using namespace std;

F_USE_NAMESPACE


SerialChain::SerialChain(uint8_t dataPin) :
    _bitCount(0),
    _dataPin(dataPin),
    _dataInverted(false)
{
}

SerialChain::~SerialChain()
{
    for(auto it : _devices) {
        delete it;
    }

    _devices.clear();
}

void SerialChain::initialize()
{
    pinMode(_dataPin, OUTPUT);
}

void SerialChain::setDataPinInverted(bool isInverted)
{
    _dataInverted = isInverted;
}

void SerialChain::beginFlush(uint32_t totalBitCount)
{
    _deviceIndex = _devices.size() - 1;
    _bitOffset = totalBitCount - _bitCount;
    _pDevice = _devices[_deviceIndex];
}

void SerialChain::updateBitCount()
{
    uint32_t bitCount = 0;
    for (auto it : _devices) {
        bitCount += it->bitCount();
    }

    _bitCount = bitCount;
}
