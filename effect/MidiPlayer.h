/**
 * ESP/Arduino Effect Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_EFFECT_MIDIPLAYER_H
#define _ESP_EFFECT_MIDIPLAYER_H

#include "library.h"
#include "../net/MidiListener.h"

F_BEGIN_NAMESPACE

struct MidiPlayerEffect
{
    
};

class MidiPlayer : public MidiListener
{
public:
    MidiPlayer();
    virtual ~MidiPlayer() {}

    virtual void onMidiMessage(const MidiMessage& message) override;
};

F_END_NAMESPACE

#endif // _ESP_EFFECT_MIDIPLAYER_H