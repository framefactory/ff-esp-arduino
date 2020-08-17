/**
 * ESP/Arduino Matrix Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_MATRIX_BITMAP_H
#define _ESP_MATRIX_BITMAP_H

#include "library.h"

F_BEGIN_NAMESPACE

class Bitmap
{
public:
    Bitmap(int width, int height, const uint8_t* pData = nullptr);
    virtual ~Bitmap();

    void set(int x, int y, bool state = true, bool wrap = true) {
        if (wrap || (x >= 0 && x < _width && y >= 0 && y < _height)) {
            uint32_t i = (y % _height) * _width + (x % _width);
            uint8_t& v = _pData[i / 8];
            v = state ? v | (1 << (i % 8)) : v & ~(1 << (i % 8));
        }
    }

    bool get(int x, int y, bool wrap = true) const {
        if (wrap || (x >= 0 && x < _width && y >= 0 && y < _height)) {
            uint32_t i = (y % _height) * _width + (x % _width);
            return _pData[i / 8] & (1 << (i % 8));
        }
        return false;
    }

    void line(int x0, int y0, int x1, int y1, bool state = true);
    void rect(int x, int y, int width, int height, bool state = true);
    void fill(int x, int y, int width, int height, bool state = true);
    void circle(int cx, int cy, int r, bool state = true);
    void ellipse(int cx, int cy, int rx, int ry, bool state = true);
    void drawText(const char* pText, const Bitmap* pFont, int x, int y, int stride = 8, bool wrap = true);

    void copy(const Bitmap& source, int sx = 0, int sy = 0, int tx = 0, int ty = 0, int w = 0, int h = 0);
    void clear();

    void scrollLeft(bool wrap = false);
    void scrollRight(bool wrap = false);
    void scrollUp(bool wrap = false);
    void scrollDown(bool wrap = false);

    int width() const { return _width; }
    int height() const { return _height; }

    uint8_t* data() { return _pData; }
    const uint8_t* data() const { return _pData; }

private:
    int _width;
    int _height;
    int _size;
    uint8_t* _pData;
};

F_END_NAMESPACE

#endif // _ESP_MATRIX_BITMAP_H