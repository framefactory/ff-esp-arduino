/**
 * ESP/Arduino Net Library
 * Copyright 2025 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#pragma once

#include "../library.h"
#include "MidiPort.h"

/*
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

F_BEGIN_NAMESPACE

class BLEMidi : public MidiPort, BLEServerCallbacks, BLECharacteristicCallbacks
{
public:
    BLEMidi(const std::string& deviceName = std::string());
    virtual ~BLEMidi() {}

    void begin();

    std::string deviceName() const { return _deviceName; }

protected:
    virtual void onConnect(BLEServer* pServer) override;
    virtual void onDisconnect(BLEServer* pServer) override;

    virtual void onRead(BLECharacteristic* pCharacteristic) override;
	virtual void onWrite(BLECharacteristic* pCharacteristic) override;
	virtual void onNotify(BLECharacteristic* pCharacteristic) override;
	virtual void onStatus(BLECharacteristic* pCharacteristic, BLECharacteristicCallbacks::Status s, uint32_t code) override;

private:
    std::string _deviceName;
    BLECharacteristic* _pCharacteristic = nullptr;
    bool _deviceConnected = false;
    char _runningStatus = 0;

    char _sysex[128];
    int _sysexPtr;
};

F_END_NAMESPACE
*/
