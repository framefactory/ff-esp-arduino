/**
 * ESP/Arduino Matrix Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_MATRIX_SERIALDEVICE_H
#define _ESP_MATRIX_SERIALDEVICE_H

#include "library.h"

F_BEGIN_NAMESPACE

class SerialDevice
{
public:
    SerialDevice(uint32_t bitCount);
    virtual ~SerialDevice() {}

    inline bool nextBit(bool& done) const {
        done = --_index == 0;
        return (_data & (1 << _index)) != 0;
    }

    inline uint32_t bitCount() const { return _bitCount; }

protected:
    void writeData(uint32_t data);

private:
    uint32_t _bitCount;
    mutable uint32_t _data;
    mutable uint32_t _index;
};

F_END_NAMESPACE

#endif // _ESP_MATRIX_SERIALDEVICE_H