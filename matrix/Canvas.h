/**
 * ESP/Arduino Matrix Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_MATRIX_CANVAS_H
#define _ESP_MATRIX_CANVAS_H

#include "library.h"
#include "Bitmap.h"

#include <vector>
#include <string>

F_BEGIN_NAMESPACE

class MAX7219Matrix;

class Canvas : public Bitmap
{
public:
    struct mapping_t {
        MAX7219Matrix* pMatrix;
        uint32_t x;
        uint32_t y;
    };

    typedef std::vector<MAX7219Matrix*> matrixVec_t;
    typedef std::vector<mapping_t> mappingVec_t;

    Canvas(uint32_t width, uint32_t height);
    virtual ~Canvas() {}

    void addMatrix(MAX7219Matrix* pMatrix, uint32_t x, uint32_t y);
    void addMatrices(const matrixVec_t& matrices, uint32_t xPos, uint32_t yPos, uint32_t xOffset, uint32_t yOffset);

    void update(int xOffset = 0, int yOffset = 0);

    size_t numMappings() { return _mappings.size(); }
    const mapping_t& mapping(size_t index) { return _mappings[index]; }
    
private:
    mappingVec_t _mappings;
};

F_END_NAMESPACE

#endif // _ESP_MATRIX_CANVAS_H