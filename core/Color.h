/**
 * ESP/Arduino Core Library
 * Copyright 2025 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#pragma once

#include "../library.h"

#include "Math.h"
#include "Vector3T.h"
#include "Vector4T.h"


F_BEGIN_NAMESPACE


struct ColorHSV
{
    ColorHSV() = default;
    ColorHSV(float hue, float saturation, float value) :
        hue(hue), saturation(saturation), value(value) { }

    float hue;
    float saturation;
    float value;
};

struct ColorHSL
{
    ColorHSL() = default;
    ColorHSL(float hue, float saturation, float luminance) :
        hue(hue), saturation(saturation), luminance(luminance) { }

    float hue;
    float saturation;
    float luminance;
};

class Color
{
public:
    static Color fromUint32(uint32_t rgbaColor);

    /// Default constructor. Creates an uninitialized color.
    Color() : r(0.0f), g(0.0f), b(0.0f), a(0.0f)  { };
    Color(float r, float g, float b, float a = 1.0f);
    explicit Color(const float* pValues);

    float* ptr() { return &r; }
    const float* ptr() const { return &r; }

    uint8_t redByte() const { return uint8_t(r * 255.0f); }
    uint8_t greenByte() const { return uint8_t(g * 255.0f); }
    uint8_t blueByte() const { return uint8_t(b * 255.0f); }
    uint8_t alphaByte() const { return uint8_t(a * 255.0f); }

    Color& copy(const Color& other);

    Color& set(float red, float green, float blue, float alpha = 1.0f);
    Color& set(uint8_t redByte, uint8_t greenByte, uint8_t blueByte, uint8_t alpha = 255);

    Color& setHSV(float hue, float saturation, float value, float alpha = 1.0f);
    Color& setHSL(float hue, float saturation, float luminance, float alpha = 1.0f);

    ColorHSV toHSV() const;
    ColorHSL toHSL() const;

    Color& mix(const Color& other, float factor);

    Color& clamp(float lowerLimit = 0.0f, float upperLimit = 1.0f);
    Color clamped(float lowerLimit = 0.0f, float upperLimit = 1.0f) const {
        return Color(*this).clamp();
    };

    uint32_t toUInt32RGBA() const {
        return (uint32_t(r * 255.0) << 24) + (uint32_t(g * 255.0) << 16)
            + (uint32_t(b * 255.0) << 8) + uint32_t(a * 255.0); 
    }
    uint32_t toUInt32BGRA() const {
        return (uint32_t(b * 255.0) << 24) + (uint32_t(g * 255.0) << 16)
            + (uint32_t(r * 255.0) << 8) + uint32_t(a * 255.0); 
    }
    Vector3f toVector3f() const {
        return Vector3f(r, g, b);
    }
    Vector4f toVector4f() const {
        return Vector4f(r, g, b, a);
    }

    float r;
    float g;
    float b;
    float a;    
};

inline Color::Color(float _r, float _g, float _b, float _a /* = 1.0f */) :
    r(_r),
    g(_g),
    b(_b),
    a(_a)
{
}

inline Color::Color(const float* pValues) :
    r(pValues[0]),
    g(pValues[1]),
    b(pValues[2]),
    a(pValues[3])
{
}

inline Color& Color::copy(const Color& other) {
    r = other.r;
    g = other.g;
    b = other.b;
    a = other.a;
    return *this;
}

inline Color& Color::set(float red, float green, float blue, float alpha) {
    r = red;
    g = green;
    b = blue;
    a = alpha;
    return *this;
}

inline Color& Color::set(uint8_t redByte, uint8_t greenByte, uint8_t blueByte, uint8_t alphaByte) {
    r = float(redByte) / 255.0f;
    g = float(greenByte) / 255.0f;
    b = float(blueByte) / 255.0f;
    a = float(alphaByte) / 255.0f;
    return *this;
}

inline Color& Color::mix(const Color& other, float factor) {
    float invFactor = 1.0f - factor;
    r = invFactor * r + factor * other.r;
    g = invFactor * g + factor * other.g;
    b = invFactor * b + factor * other.b;
    a = invFactor * a + factor * other.a;
    return *this;
}

inline Color& Color::clamp(float lowerLimit, float upperLimit) {
    r = Math::clamp(r, lowerLimit, upperLimit);
    g = Math::clamp(g, lowerLimit, upperLimit);
    b = Math::clamp(b, lowerLimit, upperLimit);
    a = Math::clamp(a, lowerLimit, upperLimit);
    return *this;
}


F_END_NAMESPACE
