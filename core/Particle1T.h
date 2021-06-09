/**
 * ESP/Arduino Core Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_CORE_PARTICLE1T_H
#define _ESP_CORE_PARTICLE1T_H

#include "../library.h"
#include <cmath>

F_BEGIN_NAMESPACE

template<typename REAL>
struct Particle1T
{
    Particle1T(REAL pos = REAL(0.0), REAL vel = REAL(0.0), REAL accel = REAL(0.0), REAL damp = REAL(1.0));

    void update(REAL delta);

    REAL position;
    REAL velocity;
    REAL acceleration;    
    REAL damping;
};

template<typename REAL>
inline Particle1T<REAL>::Particle1T(REAL pos, REAL vel, REAL accel, REAL damp) :
    position(pos),
    velocity(vel),
    acceleration(accel),
    damping(damp)
{
}

template<typename REAL>
inline void Particle1T<REAL>::update(REAL delta)
{
    velocity += acceleration * delta;
    velocity *= pow(damping, delta);
    position += velocity * delta;
}

// Typedefs --------------------------------------------------------------------

typedef Particle1T<float> Particle1f;
typedef Particle1T<double> Particle1d;

F_END_NAMESPACE

#endif // _ESP_CORE_PARTICLE1T_H