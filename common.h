/**
 * ESP/Arduino Core Library
 * Copyright 2025 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#pragma once

#include <cstdint>
#include <Arduino.h>

// MACROS
#define F_BEGIN_NAMESPACE namespace ff {
#define F_END_NAMESPACE }
#define F_USE_NAMESPACE using namespace ff;

#define F_SAFE_DELETE(p) if (p) { delete (p); (p) = nullptr; }

#define F_DISABLE_COPY(Class) private: Class(const Class& other); Class& operator=(const Class& other);
