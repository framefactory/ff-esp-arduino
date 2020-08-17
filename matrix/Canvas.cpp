/**
 * ESP/Arduino Matrix Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "Canvas.h"
#include "MAX7219Matrix.h"

F_USE_NAMESPACE

Canvas::Canvas(uint32_t width, uint32_t height) :
    Bitmap(width, height)
{
}

void Canvas::addMatrix(MAX7219Matrix* pMatrix, uint32_t x, uint32_t y)
{
   _mappings.push_back({ pMatrix, x, y });
}

void Canvas::addMatrices(const matrixVec_t& matrices, uint32_t xPos, uint32_t yPos, uint32_t xOffset, uint32_t yOffset)
{
    for (size_t i = 0; i < matrices.size(); ++i) {
       _mappings.push_back({ matrices[i], xPos + xOffset * i, yPos + yOffset * i });
    }
}

void Canvas::update(int xOffset /* = 0 */, int yOffset /* = 0 */)
{
   for (auto& mapping : _mappings) {
      int x = mapping.x;
      int y = mapping.y;
      for (int iy = 0; iy < 8; ++iy) {
         for (int ix = 0; ix < 8; ++ix) {
            mapping.pMatrix->setDot(ix, iy, get(x + ix + xOffset, y + iy + yOffset));            
         }
      }
   }
}