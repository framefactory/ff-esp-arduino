/**
 * ESP/Arduino Net Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_NET_MIDIMESSAGE_H
#define _ESP_NET_MIDIMESSAGE_H

#include "library.h"
#include <string>

F_BEGIN_NAMESPACE

class MidiStatus
{
    enum status_t
    {
        NoteOff         = 0b10000000,
        NoteOn          = 0b10010000,
        KeyPressure     = 0b10100000,
        ControlChange   = 0b10110000,
        ProgramChange   = 0b11000000,
        ChannelPressure = 0b11010000,
        PitchBend       = 0b11100000,

        SystemCommon    = 0b11110000,
        SystemExclusive = 0b11110000,
        MTCQuarterFrame = 0b11110001,
        SongPosition    = 0b11110010,
        SongSelect      = 0b11110011,
        TuneRequest     = 0b11110110,
        EndOfExclusive  = 0b11110111,

        SystemRealtime  = 0b11111000,
        TimingClock     = 0b11111000,
        Start           = 0b11111010,
        Continue        = 0b11111011,
        Stop            = 0b11111100,
        ActiveSensing   = 0b11111110,
        Reset           = 0b11111111,
    };
};

class MidiMessage
{
public:
    MidiMessage(const std::string& data);

    bool isChannelMessage() const { return (_bytes[0] & 0xf0) == 0xf0; }

    uint8_t status() const { return(_bytes[0] & 0xf0) == 0xf0 ? _bytes[0] : _bytes[0] & 0xf0; }
    uint8_t channel() const { return _bytes[0] & 0x0f; }

    uint8_t note() const { return _bytes[1]; }
    uint8_t program() const { return _bytes[1]; }
    uint8_t controller() const { return _bytes[1]; }
    uint8_t velocity() const { return _bytes[2]; }
    uint8_t value() const { return _bytes[2]; }

    operator std::string() const;

private:
    uint8_t _bytes[3];
};

F_END_NAMESPACE

#endif // _ESP_NET_MIDIMESSAGE_H