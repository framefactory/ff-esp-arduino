/**
 * ESP/Arduino Net Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_NET_MIDILISTENER_H
#define _ESP_NET_MIDILISTENER_H

#include "library.h"
#include "MidiMessage.h"

F_BEGIN_NAMESPACE

class MidiListener
{
public:
    virtual ~MidiListener() {}

    /// Called if a new MIDI message is received.
    virtual void onMidiMessage(const MidiMessage& message) = 0;
    virtual void onRPN(uint16_t param, uint16_t value) = 0;
    virtual void onNRPN(uint16_t param, uint16_t value) = 0;    
};

F_END_NAMESPACE

#endif // _ESP_NET_MIDILISTENER_H