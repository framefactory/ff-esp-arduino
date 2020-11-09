/**
 * ESP/Arduino Net Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "MidiMessage.h"
#include <sstream>

F_USE_NAMESPACE

MidiMessage::MidiMessage(const std::string& data)
{
    size_t size = data.size();
    if (size >= 4) {
        _bytes[0] = data[2];
        _bytes[1] = data[3];
    }
    if (size >= 5) {
        _bytes[2] = data[4];
    }
}

MidiMessage::operator std::string() const
{
    std::ostringstream oss;
    oss << _bytes[0] << ", " << _bytes[1] << ", " << _bytes[2] << std::endl;
    return oss.str();
}
