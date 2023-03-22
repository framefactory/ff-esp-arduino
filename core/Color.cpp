/**
 * ESP/Arduino Core Library
 * Copyright 2023 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "Color.h"
#include <algorithm>

F_USE_NAMESPACE

static inline float _hue2rgb(float p, float q, float t) {
    if (t < 0.0f) t += 1;
    if (t > 1.0f) t -= 1;
    if (t < 1.0f / 6.0f) return p + (q - p) * 6.0f * t;
    if (t < 1.0f / 2.0f) return q;
    if (t < 2.0f / 3.0f) return p + (q - p) * (2.0f/3.0f - t) * 6.0f;
    return p;
}

Color& Color::setHSV(float hue, float saturation, float value, float alpha)
{
    float i = floorf(hue / 60.0f);
    float f = hue / 60.0f - i;
    float p = value * (1.0f - saturation);
    float q = value * (1.0f - f * saturation);
    float t = value * (1.0f - (1.0f - f) * saturation);

    int k = int(i);
    switch (k % 6) {
        case 0: r = value; g = t; b = p; break;
        case 1: r = q; g = value; b = p; break;
        case 2: r = p; g = value; b = t; break;
        case 3: r = p; g = q; b = value; break;
        case 4: r = t; g = p; b = value; break;
        case 5: r = value; g = p; b = q; break;
    }

    a = alpha;

    return *this;
}

Color& Color::setHSL(float hue, float saturation, float luminance, float alpha)
{
    if (saturation == 0.0f) {
        r = g = b = luminance;
    }
    else {
        hue /= 360.0f;

        float q = luminance < 0.5f
            ? luminance * (1.0 + saturation)
            : luminance + saturation - luminance * saturation;
        float p = 2.0 * luminance - q;

        r = _hue2rgb(p, q, hue + 1.0f / 3.0f);
        g = _hue2rgb(p, q, hue);
        b = _hue2rgb(p, q, hue - 1.0f / 3.0f);
    }

    a = alpha;

    return *this;
}

ColorHSV Color::toHSV() const
{
    float min = r < g ? (r < b ? r : b) : (g < b ? g : b);
    float max = r > g ? (r > b ? r : b) : (g > b ? g : b);
    float d = max - min;
    float h = 0;
    float s = max == 0.0f ? 0.0f : d / max;
    float v = max;

    if (d != 0.0f) {
        h = (r == max
            ? (g - b) / d + (g < b ? 6.0f : 0.0f)
            : (g == max ? (b - r) / d + 2.0f : (r - g) / d + 4.0f)) * 60.0f;
    }

    return ColorHSV(h, s, v);
}

ColorHSL Color::toHSL() const
{
    float min = r < g ? (r < b ? r : b) : (g < b ? g : b);
    float max = r > g ? (r > b ? r : b) : (g > b ? g : b);
    float d = max - min;
    float h = 0.0f, s = 0.0f;
    float l = (max + min) * 0.5f;

    if (d != 0.0f) {
        s = l > 0.5f ? d / (2.0 - max - min) : d / (max + min);
        h = (r == max
            ? (g - b) / d + (g < b ? 6.0 : 0.0)
            : g == max ? 2.0f + (b - r) / d : 4.0f + (r - g) / d) * 60.0f;
    }

    return ColorHSL(h, s, l);
}