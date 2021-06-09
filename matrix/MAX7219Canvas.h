/**
 * ESP/Arduino Matrix Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_MATRIX_MAX7219CANVAS_H
#define _ESP_MATRIX_MAX7219CANVAS_H

#include "../library.h"
#include "effect/Bitmap.h"

#include <vector>
#include <string>

F_BEGIN_NAMESPACE

class MAX7219Matrix;

class MAX7219Canvas : public Bitmap
{
public:
    struct mapping_t {
        MAX7219Matrix* pMatrix;
        int x;
        int y;
    };

    typedef std::vector<MAX7219Matrix*> matrixVec_t;

    /// Creates a bitmap canvas with the given width and height.
    MAX7219Canvas(int width, int height);

    /// Adds a single matrix to the canvas at the given position.
    void addMatrix(MAX7219Matrix* pMatrix, int x, int y);
    /// Adds a vector of matrices to the canvas at the given position and offsets.
    void addMatrices(const matrixVec_t& matrices, int xPos, int yPos, int xOffset, int yOffset);

    /// Updates all matrices with the mapped content of the canvas.
    void update(int xOffset = 0, int yOffset = 0);

    /// Returns the number of mapped matrices.
    size_t numMappings() { return _mappings.size(); }
    /// Returns the matrix mapping at the given index.
    const mapping_t& mapping(size_t index) { return _mappings[index]; }
    
private:
    typedef std::vector<mapping_t> mappingVec_t;
    mappingVec_t _mappings;
};

F_END_NAMESPACE

#endif // _ESP_MATRIX_MAX7219CANVAS_H