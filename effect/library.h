/**
 * ESP/Arduino Effect Library
 * Copyright 2023 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_EFFECT_LIBRARY_H
#define _ESP_EFFECT_LIBRARY_H

#include <Arduino.h>
#include <cstdint>

// MACROS
#define F_BEGIN_NAMESPACE namespace ff {
#define F_END_NAMESPACE }
#define F_USE_NAMESPACE using namespace ff;

#define F_SAFE_DELETE(p) if (p) { delete (p); (p) = nullptr; }

#endif // _ESP_EFFECT_LIBRARY_H