/**
 * ESP/Arduino Media Library
 * Copyright 2021 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_NATIVE_MEDIA_AUDIOOUT_H
#define _ESP_NATIVE_MEDIA_AUDIOOUT_H

#include "../library.h"
#include "driver/i2s.h"

F_BEGIN_NAMESPACE

class AudioOut
{
public:
    AudioOut(int bckPin, int wsPin, int dataPin);
    virtual ~AudioOut() { }

    bool open();
    void close();

    bool write(const int16_t* pData, size_t length);

private:
    bool _isOpen = false;
    i2s_pin_config_t _pinConfig;
    i2s_port_t _port = I2S_NUM_1;
};

F_END_NAMESPACE

#endif // _ESP_NATIVE_MEDIA_AUDIOOUT_H