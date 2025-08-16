/**
 * ESP/Arduino Core Library
 * Copyright 2025 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#pragma once

#include "../library.h"
#include "Vector2T.h"

F_BEGIN_NAMESPACE

template<typename REAL>
struct Particle2T
{
    Particle2T(REAL posX = REAL(0.0), REAL posY = REAL(0.0));

    Particle2T(
        const Vector2T<REAL>& pos,
        const Vector2T<REAL>& vel = Vector2T<REAL>(REAL(0.0), REAL(0.0)),
        const Vector2T<REAL>& accel = Vector2T<REAL>(REAL(0.0), REAL(0.0)),
        const Vector2T<REAL>& damp = Vector2T<REAL>(REAL(1.0), REAL(1.0))
    );

    void update(REAL delta);

    Vector2T<REAL> position;
    Vector2T<REAL> velocity;
    Vector2T<REAL> acceleration;
    Vector2T<REAL> damping;
};

template<typename REAL>
inline Particle2T<REAL>::Particle2T(REAL posX, REAL posY) :
    position(posX, posY),
    velocity(REAL(0.0), REAL(0.0)),
    acceleration(REAL(0.0), REAL(0.0)),
    damping(REAL(1.0), REAL(1.0))
{
}

template<typename REAL>
inline Particle2T<REAL>::Particle2T(const Vector2T<REAL>& pos, const Vector2T<REAL>& vel, const Vector2T<REAL>& accel, const Vector2T<REAL>& damp) :
    position(pos),
    velocity(vel),
    acceleration(accel),
    damping(damp)
{
}

template<typename REAL>
inline void Particle2T<REAL>::update(REAL delta)
{
    velocity += acceleration * delta;
    velocity.x *= pow (damping.x, delta);
    velocity.y *= pow (damping.y, delta);
    position += velocity * delta;
}

// Typedefs --------------------------------------------------------------------

typedef Particle2T<float> Particle2f;
typedef Particle2T<double> Particle2d;

F_END_NAMESPACE
