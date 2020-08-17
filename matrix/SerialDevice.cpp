/**
 * ESP/Arduino Matrix Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "SerialDevice.h"

F_USE_NAMESPACE

SerialDevice::SerialDevice(uint32_t bitCount) :
    _bitCount(bitCount),
    _data(0),
    _index(0)
{
}

void SerialDevice::writeData(uint32_t data)
{
    _data = data;
    _index = bitCount();
}