/**
 * ESP/Arduino Effect Library
 * Copyright 2025 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "Composable.h"

F_USE_NAMESPACE

void Composable::setEnabled(bool isEnabled)
{
    _isEnabled = isEnabled;
}