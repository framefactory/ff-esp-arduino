/**
 * ESP/Arduino Net Library
 * Copyright 2025 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#pragma once

#include "../library.h"
#include "MidiListener.h"
#include "MidiMessage.h"

#include <queue>

F_BEGIN_NAMESPACE

class MidiPort
{
public:
    const static size_t QUEUE_MAX_SIZE = 16;

    MidiPort();
    virtual ~MidiPort() {}

    /// To be called in the main loop. Delivers all messages in the queue to the listener.
    void dispatch();
    /// Sets the listener for MIDI messages, implementing the MidiListener interface.
    void setListener(MidiListener* pListener);

    /// Returns the number of messages in the queue.
    size_t count() const { return _messageQueue.size(); }
    /// Returns true if there are no messages in the queue.
    bool empty() const { return _messageQueue.empty(); }

protected:
    void dispatchMessage(const MidiMessage& message);
    void dispatchSysEx(const std::string& sysEx);

    void enqueueMessage(const MidiMessage& message);
    void enqueueSysEx(const std::string& sysEx);

private:
    MidiListener* _pListener = nullptr;

    typedef std::queue<MidiMessage> messageQueue_t;
    messageQueue_t _messageQueue;

    typedef std::queue<std::string> sysExQueue_t;
    sysExQueue_t _sysExQueue;

    uint16_t _rpn_param = 0x8000;
    uint16_t _nrpn_param = 0x8000;
    uint16_t _param_value = 0;

    SemaphoreHandle_t _mutex;
};

F_END_NAMESPACE
