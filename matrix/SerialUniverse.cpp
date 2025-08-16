/**
 * ESP/Arduino Matrix Library
 * Copyright 2025 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "SerialUniverse.h"
#include "SerialChain.h"

#include <algorithm>

using namespace std;

F_USE_NAMESPACE

SerialUniverse::SerialUniverse(int clockPin, int loadPin, uint32_t delayMicroseconds /*= 1 */) :
    _delayMicroseconds(delayMicroseconds),
    _clockPin(clockPin),
    _loadPin(loadPin),
    _clockPin2(-1),
    _loadPin2(-1),
    _clockInverted(false),
    _loadInverted(false)
{
}

SerialUniverse::~SerialUniverse()
{
    for (auto it : _chains) {
        delete it;
    }

    _chains.clear();
}

void SerialUniverse::initialize()
{
    pinMode(_clockPin, OUTPUT);
    pinMode(_loadPin, OUTPUT);
}

void SerialUniverse::setClockPinInverted(bool isInverted)
{
    _clockInverted = isInverted;
}

void SerialUniverse::setLoadPinInverted(bool isInverted)
{
    _loadInverted = isInverted;
}

void SerialUniverse::setSecondClockPin(int clockPin2)
{
    _clockPin2 = clockPin2;
    pinMode(clockPin2, OUTPUT);
}

void SerialUniverse::setSecondLoadPin(int loadPin2)
{
    _loadPin2 = loadPin2;
    pinMode(loadPin2, OUTPUT);
}

void SerialUniverse::tick()
{
    digitalWrite(_clockPin, _clockInverted ? LOW : HIGH);
    if (_clockPin2 >= 0) {
        digitalWrite(_clockPin2, _clockInverted ? LOW : HIGH);
    }

    if (_delayMicroseconds > 0) {
        delayMicroseconds(_delayMicroseconds);
    }

    digitalWrite(_clockPin, _clockInverted ? HIGH : LOW);
    if (_clockPin2 >= 0) {
        digitalWrite(_clockPin2, _clockInverted ? HIGH : LOW);
    }

    //if (_delayMicroseconds > 0) {
    //    delayMicroseconds(_delayMicroseconds);
    //}
}

void SerialUniverse::load()
{
    digitalWrite(_loadPin, _loadInverted ? LOW : HIGH);
    if (_loadPin2 >= 0) {
        digitalWrite(_loadPin2, _loadInverted ? LOW : HIGH);
    }

    if (_delayMicroseconds > 0) {
        delayMicroseconds(_delayMicroseconds);
    }

    digitalWrite(_loadPin, _loadInverted ? HIGH : LOW);

    if (_loadPin2 >= 0) {
        digitalWrite(_loadPin2, _loadInverted ? HIGH : LOW);
    }

    //if (_delayMicroseconds > 0) {
    //    delayMicroseconds(_delayMicroseconds);
    //}
}

void SerialUniverse::flush()
{
    uint32_t count = maxBitCount();
    for (auto it : _chains) {
        it->beginFlush(count);
    }

    for (uint32_t i = 0; i < count; ++i) {
        for (auto it : _chains) {
            it->flushBit();
        }

        if (_delayMicroseconds > 0) {
            delayMicroseconds(_delayMicroseconds);
        } 

        tick();
    }

    load();
}

uint32_t SerialUniverse::maxBitCount() const
{
    uint32_t maxBitCount = 0;
    for (auto it : _chains) {
        maxBitCount = std::max(maxBitCount, it->bitCount());
    }

    return maxBitCount;
}
