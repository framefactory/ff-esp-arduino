/**
 * ESP/Arduino Net Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_NET_BLEMIDI_H
#define _ESP_NET_BLEMIDI_H

#include "library.h"

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

F_BEGIN_NAMESPACE

class BLEMidi : public BLEServerCallbacks, BLECharacteristicCallbacks
{
public:
    BLEMidi();
    virtual ~BLEMidi() {}

    void begin();

protected:
    virtual void onConnect(BLEServer* pServer) override;
    virtual void onDisconnect(BLEServer* pServer) override;

    virtual void onRead(BLECharacteristic* pCharacteristic) override;
	virtual void onWrite(BLECharacteristic* pCharacteristic) override;
	virtual void onNotify(BLECharacteristic* pCharacteristic) override;
	virtual void onStatus(BLECharacteristic* pCharacteristic, Status s, uint32_t code) override;

private:
    BLECharacteristic* _pCharacteristic;
    bool _deviceConnected;
};

F_END_NAMESPACE

#endif // _ESP_NET_BLEMIDI_H