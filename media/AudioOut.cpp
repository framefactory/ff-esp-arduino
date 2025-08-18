/**
 * ESP/Arduino Media Library
 * Copyright 2025 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "AudioOut.h"


F_USE_NAMESPACE

AudioOut::AudioOut(int bckPin, int wsPin, int dataPin)
{
    _pinConfig = {
        .mck_io_num = I2S_PIN_NO_CHANGE,
        .bck_io_num = bckPin,
        .ws_io_num = wsPin,
        .data_out_num = dataPin,
        .data_in_num = I2S_PIN_NO_CHANGE
    };
}

bool AudioOut::open(uint32_t sampleRate /* = 44100 */, int dmaBufCount /* = 8 */, int dmaBufLen /* = 128 */)
{
    if (_isOpen) {
        return true;
    }

    i2s_config_t config = {
        .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_TX),
        .sample_rate = 44100,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .intr_alloc_flags = 0,
        .dma_buf_count = dmaBufCount,
        .dma_buf_len = dmaBufLen,
        .use_apll = false,
        .tx_desc_auto_clear = true,
        .fixed_mclk = 0
    };

    esp_err_t result = i2s_driver_install(_port, &config, 0, NULL);

    if (result == ESP_OK) {
        result = i2s_set_pin(_port, &_pinConfig);
    }

    if (result == ESP_OK) {
        _isOpen = true;
    }
    else {
        Serial.printf("[AudioOut] I2S driver initialization failed: %s\n", esp_err_to_name(result));
        _isOpen = false;
    }

    return _isOpen;
}

void AudioOut::close()
{
    if (_isOpen) {
        _isOpen = false;
        i2s_driver_uninstall(_port);
    }
}

bool AudioOut::write(const int16_t* pData, size_t length)
{
    if (!_isOpen) {
        return false;
    }

    size_t bytesWritten = 0;
    esp_err_t result = i2s_write(_port, pData, length * sizeof(uint16_t), &bytesWritten, portMAX_DELAY);
    return result == ESP_OK;
}