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
public:
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
    /// Returns the number of bytes in a MIDI message based on the given status.
    static size_t lengthFromStatus(uint8_t status);
    static const char* nameFromStatus(uint8_t status);

    /// Creates a new MIDI message with the given bytes.
    MidiMessage(uint8_t status = 0, uint8_t data0 = 0, uint8_t data1 = 0);

    /// Sets the message content.
    void setBytes(uint8_t status, uint8_t data0 = 0, uint8_t data1 = 0);

    /// Returns true if this is a channel message.
    bool isChannelMessage() const { return _bytes[0] < 0xf0; }
    /// Returns true if this is a system realtime message.
    bool isSystemRealtime() const { return _bytes[0] & 0xf8; }

    uint32_t status() const { return _bytes[0] < 0xf0 ? _bytes[0] & 0xf0 : _bytes[0]; }
    uint32_t channel() const { return _bytes[0] & 0x0f; }

    uint32_t data0() const { return _bytes[1]; }
    uint32_t data1() const { return _bytes[2]; }
    uint32_t note() const { return data0(); }
    uint32_t program() const { return data0(); }
    uint32_t controller() const { return data0(); }
    uint32_t velocity() const { return data1(); }
    uint32_t value() const { return data1(); }
    size_t size() const { return lengthFromStatus(_bytes[0]); }

    std::string toString() const;
    operator std::string() const { return toString(); }

private:
    uint8_t _bytes[3];
};

F_END_NAMESPACE

#endif // _ESP_NET_MIDIMESSAGE_H