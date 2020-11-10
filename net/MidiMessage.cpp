/**
 * ESP/Arduino Net Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "MidiMessage.h"
#include <sstream>

F_USE_NAMESPACE

size_t MidiMessage::lengthFromStatus(uint8_t status)
{
    // channel messages
    if (status < 0xf0) {
        uint8_t msg = status & 0xf0;
        // program and channel pressure: 2 bytes
        if (msg == 0xc0 || msg == 0xd0) {
            return 2;
        }

        // other channel messages: 3 bytes
        return 3;
    }
    // system real time messages, tune request: 1 byte
    if (status & 0x08 || status == 0xf6) {
        return 1;
    }
    // MTC, song select: 2 bytes
    if (status == 0xf1 || status == 0xf3) {
        return 2;
    }
    // SPP: 3 bytes
    if (status == 0xf2) {
        return 3;
    }

    // system exclusive or undefined
    return 0;
}

const char* MidiMessage::nameFromStatus(uint8_t status)
{
    // channel message
    if (status < 0xf0) {
        switch(status & 0xf0) {
            case 0x80: return "Note Off";
            case 0x90: return "Note On";
            case 0xa0: return "Key Pressure";
            case 0xb0: return "Control Change";
            case 0xc0: return "Program Change";
            case 0xd0: return "Channel Pressure";
            case 0xe0: return "Pitch Bend";
        }
    }
    else {
        switch(status) {
            case 0xf0: return "System Exclusive";
            case 0xf1: return "MTC";
            case 0xf2: return "SPP";
            case 0xf3: return "Song Select";
            case 0xf6: return "Tune Request";
            case 0xf7: return "End of Exclusive";

            case 0xf8: return "Timing Clock";
            case 0xfa: return "Start";
            case 0xfb: return "Continue";
            case 0xfc: return "Stop";
            case 0xfe: return "Active Sensing";
            case 0xff: return "System Reset";
        }
    }

    return "Undefined";
}

MidiMessage::MidiMessage(uint8_t status /* = 0 */, uint8_t data0 /* = 0 */, uint8_t data1 /* = 0 */) :
    _bytes { status, data0, data1 }
{
}

void MidiMessage::setBytes(uint8_t status, uint8_t data0 /* = 0 */, uint8_t data1 /* = 0 */)
{
    _bytes[0] = status;
    _bytes[1] = data0;
    _bytes[2] = data1;
}

std::string MidiMessage::toString() const
{
    size_t numBytes = size();
    uint8_t status = _bytes[0];
    std::ostringstream oss;

    oss << nameFromStatus(status);
    if (isChannelMessage()) {
        oss << " C" << (channel() + 1);
    }

    if (numBytes > 1) {
        oss << ", " << data0();
    }
    if (numBytes > 2) {
        oss << ", " << data1();
    }

    return oss.str();
}
