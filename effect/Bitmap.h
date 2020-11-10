/**
 * ESP/Arduino Matrix Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_MATRIX_BITMAP_H
#define _ESP_MATRIX_BITMAP_H

#include "library.h"

F_BEGIN_NAMESPACE

struct ClipRegion
{
    ClipRegion() :
        x0(0), y0(0), x1(0), y1(0) {}

    ClipRegion(int _x0, int _y0, int _x1, int _y1) :
        x0(_x0), y0(_y0), x1(_x1), y1(_y1) {}

    int x0;
    int y0;
    int x1;
    int y1;
};

class Bitmap
{
public:
    enum DrawOp {
        Set,
        Clear,
        Invert
    };

    enum MixOp {
        Replace,
        And,
        Or,
        Xor
    };

public:
    /// Creates a new bitmap with the given dimensions. If data is given, copies the data to the bitmap.
    Bitmap(int width, int height, const uint8_t* pData = nullptr);
    virtual ~Bitmap();

    /// Sets or clears the pixel at the given position.
    void set(int x, int y, bool state = true) {
        if (x >= _clip.x0 && x < _clip.x1 && y >= _clip.y0 && y < _clip.y1) {
            uint32_t i = y * _width + x;
            uint8_t& v = _pData[i / 8];
            v = state ? v | (1 << (i % 8)) : v & ~(1 << (i % 8));
        }
    }

    /// Sets the pixel at the given position using the given drawing operation.
    void set(int x, int y, DrawOp op) {
        if (x >= _clip.x0 && x < _clip.x1 && y >= _clip.y0 && y < _clip.y1) {
            uint32_t i = y * _width + x;
            uint8_t& v = _pData[i / 8];
            if (op == Set) v |= (1 << (i % 8));
            else if (op == Clear) v &= ~(1 << (i % 8));
            else v ^= (1 << (i % 8));
        }
    }

    /// Returns the value of the pixel at the given position.
    /// Returns false if the position is outside of the bitmap's dimensions.
    bool get(int x, int y) const {
        if (x >= 0 && x < _width && y >= 0 && y < _height) {
            uint32_t i = y * _width + x;
            return _pData[i / 8] & (1 << (i % 8));
        }
        return false;
    }

    /// Blends the given pixel with the pixel at the given position using the given mix operation.
    void mix(int x, int y, bool src, MixOp op) {
        if (x >= _clip.x0 && x < _clip.x1 && y >= _clip.y0 && y < _clip.y1) {
            uint32_t i = y * _width + x;
            uint8_t& v = _pData[i / 8];
            if (op == Replace) v = src ? v | (1 << (i % 8)) : v & ~(1 << (i % 8));
            else if (op == And) v = src ? v : v & ~(1 << (i % 8));
            else if (op == Or) v = src ? v | (1 << (i % 8)) : v;
            else v = src ? v ^ (1 << (i % 8)) : v;
        }
    }

    /// Draws a line.
    void line(int x0, int y0, int x1, int y1, DrawOp op = Set);
    /// Draws a rectangle.
    void rect(int x, int y, int width, int height, DrawOp op = Set);
    /// Fills a rectangular area.
    void fill(int x, int y, int width, int height, DrawOp op = Set);
    /// Draws a circle.
    void circle(int cx, int cy, int r, DrawOp op = Set);
    /// Draws an ellipse
    void ellipse(int cx, int cy, int rx, int ry, DrawOp op = Set);
    /// Draws text using the given bitmap font.
    void drawText(const char* pText, const Bitmap* pFont, int x, int y, int stride = 8, MixOp op = Or);

    /// Copies the source bitmap to this. Source and target offsets and size can be specified.
    void copy(const Bitmap& source, int sx = 0, int sy = 0, int tx = 0, int ty = 0, int w = 0, int h = 0, MixOp op = Replace);
    /// Copies the source bitmap to this. The source must be of the same size as the target.
    void blit(const Bitmap& source, MixOp op = Replace);
    /// Clears the bitmap, i.e. sets all pixels to off.
    void clear();

    /// Moves the bitmap's content one pixel to the left.
    void scrollLeft(MixOp op = Replace);
    /// Moves the bitmap's content one pixel to the right.
    void scrollRight(MixOp op = Replace);
    /// Moves the bitmap's content one pixel up.
    void scrollUp(MixOp op = Replace);
    /// Moves the bitmap's content one pixel down.
    void scrollDown(MixOp op = Replace);

    /// Sets a clipping region. This affects all drawing.
    void setClipRegion(int left, int top, int width, int height);
    /// Clears the clipping region, i.e. sets it to the bitmap's extent.
    void clearClipRegion();

    /// Returns the width of the bitmap.
    int width() const { return _width; }
    /// Returns the height of the bitmap.
    int height() const { return _height; }

    /// Returns a pointer to the bitmap's data.
    uint8_t* data() { return _pData; }
    /// Returns a const pointer to the bitmap's data.
    const uint8_t* data() const { return _pData; }

private:
    int _width;
    int _height;
    int _size;

    uint8_t* _pData;
    ClipRegion _clip;
};

F_END_NAMESPACE

#endif // _ESP_MATRIX_BITMAP_H