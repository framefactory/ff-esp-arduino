/**
 * ESP/Arduino Effect Library
 * Copyright 2023 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_EFFECT_COMPOSABLE_H
#define _ESP_EFFECT_COMPOSABLE_H

#include "../library.h"
#include "Bitmap.h"
#include "Timing.h"

F_BEGIN_NAMESPACE

/// Interface for objects that can be rendered onto a bitmap.
class Composable
{
public:
    virtual ~Composable() {}

    /// Renders the composable and draws it onto the given target bitmap.
    virtual void render(Bitmap* pTarget, Timing& timing) = 0;

    /// Enables or disables rendering of this composable.
    void setEnabled(bool enabled);
    /// Returns true if the composable is enabled, i.e. is rendered.
    bool enabled() const { return _isEnabled; }

private:
    bool _isEnabled = true;
};

F_END_NAMESPACE

#endif // _ESP_EFFECT_COMPOSABLE_H