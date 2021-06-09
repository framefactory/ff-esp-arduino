/**
 * ESP/Arduino Matrix Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_MATRIX_SERIALCHAIN_H
#define _ESP_MATRIX_SERIALCHAIN_H

#include "../library.h"
#include "SerialDevice.h"
#include <vector>

F_BEGIN_NAMESPACE

class SerialChain
{
public:
    typedef std::vector<SerialDevice*> deviceVec_t;

    SerialChain(uint8_t dataPin);
    virtual ~SerialChain();

    virtual void initialize();
    void setDataPinInverted(bool isInverted);

    void beginFlush(uint32_t totalBitCount);
    inline void flushBit();

    uint32_t deviceCount() const { return _devices.size(); }
    uint32_t bitCount() const { return _bitCount; }

protected:
    void updateBitCount();
    deviceVec_t _devices;

private:
    uint32_t _bitCount;
    uint8_t _dataPin;
    uint8_t _dataInverted;

    mutable uint32_t _deviceIndex;
    mutable uint32_t _bitOffset;
    mutable SerialDevice* _pDevice;
};

F_END_NAMESPACE

////////////////////////////////////////////////////////////////////////////////

void ff::SerialChain::flushBit()
{
    if (_bitOffset > 0) {
        _bitOffset--;
        digitalWrite(_dataPin, _dataInverted ? HIGH : LOW);
        return;
    }

    bool done = false;
    bool bit = _pDevice->nextBit(done);

    if (done) {
        _pDevice = _devices[--_deviceIndex];
    }

    digitalWrite(_dataPin, _dataInverted ^ bit ? HIGH : LOW);
}

#endif // _ESP_MATRIX_SERIALCHAIN_H