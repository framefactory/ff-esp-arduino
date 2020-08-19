/**
 * ESP/Arduino Font Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "Fonts.h"

#include "../fonts/data_dm8_04b24.h"
#include "../fonts/data_dm8_c64.h"
#include "../fonts/data_dm8_c648.h"

F_USE_NAMESPACE

Bitmap Fonts::font04B24(128, 128, data_dm8_04b24);
Bitmap Fonts::fontC64(128, 128, data_dm8_c64);
Bitmap Fonts::fontC648(128, 128, data_dm8_c648);
