/**
 * ESP/Arduino Matrix Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_MATRIX_MAX7219CHAIN_H
#define _ESP_MATRIX_MAX7219CHAIN_H

#include "../library.h"
#include "SerialChain.h"

F_BEGIN_NAMESPACE

class MAX7219Matrix;

typedef std::vector<MAX7219Matrix*> MAX7219Matrices;

class MAX7219Chain : public SerialChain
{
public:
    MAX7219Chain(uint8_t dataPin);
    virtual ~MAX7219Chain() {}

    MAX7219Matrix* createMatrix();
    MAX7219Matrices createMatrices(uint32_t count);
    MAX7219Matrix* matrix(uint32_t index) const;

    void clear();
    void setBrightness(uint8_t value);

    void writeRow(uint8_t index);
    void writeBrightness(uint8_t maxBrightness);
    void writeRegister(uint8_t reg, uint8_t data);
};

F_END_NAMESPACE

#endif // _ESP_MATRIX_MAX7219CHAIN_H