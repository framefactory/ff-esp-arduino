/**
 * ESP/Arduino Matrix Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_MATRIX_SERIALUNIVERSE_H
#define _ESP_MATRIX_SERIALUNIVERSE_H

#include "../library.h"
#include <vector>

F_BEGIN_NAMESPACE

class SerialChain;

class SerialUniverse
{
public:
    typedef std::vector<SerialChain*> chainVec_t;

    SerialUniverse(int clockPin, int loadPin, uint32_t delayMicroseconds = 1);
    virtual ~SerialUniverse();

    virtual void initialize();

    void setClockPinInverted(bool isInverted);
    void setLoadPinInverted(bool isInverted);
    void setSecondClockPin(int clockPin2);
    void setSecondLoadPin(int loadPin2);

    const SerialChain* chain(uint32_t index) { return _chains[index]; }
    const chainVec_t& chains() const { return _chains; }


protected:
    void tick();
    void load();
    void flush();

    uint32_t maxBitCount() const;

    chainVec_t _chains;

private:
    uint32_t _delayMicroseconds;
    int _clockPin;
    int _loadPin;
    int _clockPin2;
    int _loadPin2;
    bool _clockInverted;
    bool _loadInverted;
};

F_END_NAMESPACE

#endif // _ESP_MATRIX_SERIALUNIVERSE_H