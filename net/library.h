/**
 * ESP/Arduino Net Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_NET_LIBRARY_H
#define _ESP_NET_LIBRARY_H

#include <cstdint>
#include <Arduino.h>

// MACROS
#define F_BEGIN_NAMESPACE namespace ff {
#define F_END_NAMESPACE }
#define F_USE_NAMESPACE using namespace ff;

#define F_SAFE_DELETE(p) if (p) { delete (p); (p) = nullptr; }

#endif // _ESP_NET_LIBRARY_H