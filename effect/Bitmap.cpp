/**
 * ESP/Arduino Matrix Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "Bitmap.h"
#include "core/math.h"

F_USE_NAMESPACE

Bitmap::Bitmap(int width, int height, const uint8_t *pData /* = nullptr */, bool copy /* = true */) :
    _width(width),
    _height(height),
    _size(width * height / 8),
    _isDataOwner(copy),
    _clip(0, 0, width, height)
{
    if (copy) {
        _pData = new uint8_t[_size];

        if (pData) {
            for (int32_t i = 0; i < _size; ++i) {
                _pData[i] = pData[i];
            }
        }
        else {
            clear();
        }
    }
    else {
        _pData = const_cast<uint8_t*>(pData);
    }
}

Bitmap::~Bitmap()
{
    if (_isDataOwner) {
        F_SAFE_DELETE(_pData);
    }
}

void Bitmap::line(int x0, int y0, int x1, int y1, DrawOp op)
{
    // source: https://github.com/ArashPartow/bitmap
    // alternative: https://github.com/wernsey/bitmap/blob/master/bmp.c
    int steep = 0;
    int sx = ((x1 - x0) > 0) ? 1 : -1;
    int sy = ((y1 - y0) > 0) ? 1 : -1;
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    if (dy > dx) {
        std::swap(x0, y0);
        std::swap(dx, dy);
        std::swap(sx, sy);

        steep = 1;
    }

    int e = 2 * dy - dx;

    for (int i = 0; i < dx; ++i) {
        if (steep) {
            set(y0, x0, op);
        }
        else {
            set(x0, y0, op);
        }
        while (e >= 0) {
            y0 += sy;
            e -= (dx << 1);
        }

        x0 += sx;
        e += (dy << 1);
    }

    set(x1, y1, op);
}

void Bitmap::rect(int x, int y, int width, int height, DrawOp op)
{
    int x1 = x + width - 1;
    int y1 = y + height - 1;
    line(x, y, x1 - 1, y, op);
    line(x1, y, x1, y1 - 1, op);
    line(x + 1, y1, x1, y1, op);
    line(x, y + 1, x, y1, op);
}

void Bitmap::fill(int x, int y, int width, int height, DrawOp op)
{
    for (int iy = y; iy < y + height; ++iy) {
        for (int ix = x; ix < x + width; ++ix) {
            set(ix, iy, op);
        }
    }
}

void Bitmap::circle(int cx, int cy, int r, DrawOp op)
{
    int x = 0;
    int d = (1 - r) << 1;

    while (r >= 0)
    {
        set(cx + x, cy + r, op);
        set(cx + x, cy - r, op);
        set(cx - x, cy + r, op);
        set(cx - x, cy - r, op);

        if ((d + r) > 0) {
           d -= ((--r) << 1) - 1;
        }
        if (x > d) {
           d += ((++x) << 1) + 1;
        }
    }
}

void Bitmap::ellipse(int cx, int cy, int rx, int ry, DrawOp op)
{
    int t1 = rx * rx;
    int t2 = t1 << 1;
    int t3 = t2 << 1;
    int t4 = ry * ry;
    int t5 = t4 << 1;
    int t6 = t5 << 1;
    int t7 = rx * t5;
    int t8 = t7 << 1;
    int t9 = 0;

    int d1 = t2 - t7 + (t4 >> 1);
    int d2 = (t1 >> 1) - t8 + t5;
    int x = rx;
    int y = 0;

    int negative_tx = cx - x;
    int positive_tx = cx + x;
    int negative_ty = cy - y;
    int positive_ty = cy + y;

    while (d2 < 0) {
        set(positive_tx, positive_ty, op);
        set(positive_tx, negative_ty, op);
        set(negative_tx, positive_ty, op);
        set(negative_tx, negative_ty, op);

        ++y;

        t9 = t9 + t3;

        if (d1 < 0) {
            d1 = d1 + t9 + t2;
            d2 = d2 + t9;
        }
        else {
            x--;
            t8 = t8 - t6;
            d1 = d1 + (t9 + t2 - t8);
            d2 = d2 + (t9 + t5 - t8);
            negative_tx = cx - x;
            positive_tx = cx + x;
        }

        negative_ty = cy - y;
        positive_ty = cy + y;
    }

    do {
        set(positive_tx, positive_ty, op);
        set(positive_tx, negative_ty, op);
        set(negative_tx, positive_ty, op);
        set(negative_tx, negative_ty, op);

        x--;
        t8 = t8 - t6;

        if (d2 < 0) {
            ++y;
            t9 = t9 + t3;
            d2 = d2 + (t9 + t5 - t8);
            negative_ty = cy - y;
            positive_ty = cy + y;
        }
        else {
            d2 = d2 + (t5 - t8);
        }

        negative_tx = cx - x;
        positive_tx = cx + x;
    } while (x >= 0);
}

void Bitmap::drawText(const char *pText, const Bitmap *pFont, int x, int y, int stride, BlendOp op)
{
    for (int ic = 0; pText[ic] != 0; ++ic) {
        int dx = x + ic * stride;

        if (dx >= -8 && dx < width() && y >= -8 && y < height()) {
            uint8_t c = pText[ic];
            int cx = (c % 16) * 8;
            int cy = (c / 16) * 8;

            for (int iy = 0; iy < 8; ++iy) {
                for (int ix = 0; ix < 8; ++ix) {
                    blend(dx + ix, y + iy, pFont->get(cx + ix, cy + iy), op);
                }
            }
        }
    }
}

void Bitmap::copy(const Bitmap& source, BlendOp op)
{
    int size = std::min(_size, source._size);

    switch(op) {
        case Replace:
            for (int i = 0; i < size; ++i) {
                _pData[i] = source._pData[i];
            }
            break;
        case And:
            for (int i = 0; i < size; ++i) {
                _pData[i] &= source._pData[i];
            }
            break;
        case Or:
            for (int i = 0; i < size; ++i) {
                _pData[i] |= source._pData[i];
            }
            break;
        case Xor:
            for (int i = 0; i < size; ++i) {
                _pData[i] ^= source._pData[i];
            }
            break;
    }
}

void Bitmap::copy(const Bitmap &source, int sx, int sy, int tx, int ty, int w, int h, BlendOp op)
{
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            blend(tx + x, ty + y, source.get(sx + x, sy + y), op);
        }
    }
}

void Bitmap::clear()
{
    for (int i = 0; i < _size; ++i) {
        _pData[i] = 0;
    }
}

void Bitmap::scrollLeft(BlendOp op)
{
    for (int y = 0; y < _height; ++y) {
        for (int x = 1; x < _width; ++x) {
            blend(x - 1, y, get(x, y), op);
        }
    }
}

void Bitmap::scrollRight(BlendOp op)
{
    for (int y = 0; y < _height; ++y) {
        for (int x = _width - 1; x > 0; --x) {
            blend(x, y, get(x - 1, y), op);
        }
    }
}

void Bitmap::scrollUp(BlendOp op)
{
    for (int y = 0; y < _height; ++y) {
        for (int x = 0; x < _width; ++x) {
            blend(x, y - 1, get(x, y), op);
        }
    }
}

void Bitmap::scrollDown(BlendOp op)
{
    for (int y = _height - 1; y > 0; --y) {
        for (int x = 0; x < _width; ++x) {
            blend(x, y, get(x, y - 1), op);
        }
    }
}

void Bitmap::setClipRegion(int left, int top, int width, int height)
{
    _clip.x0 = Math::limit(left, 0, _width);
    _clip.y0 = Math::limit(top, 0, _height);
    _clip.x1 = Math::limit(left + width, 0, _width);
    _clip.y1 = Math::limit(top + height, 0, _height); 
}

void Bitmap::clearClipRegion()
{
    _clip = { 0, 0, _width, _height };
}