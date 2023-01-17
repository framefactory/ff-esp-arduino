/**
 * ESP/Arduino Net Library
 * Copyright 2023 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "BLEMidi.h"

F_USE_NAMESPACE
/*
BLEMidi::BLEMidi(const std::string& deviceName) :
    _deviceName(deviceName)
{
}

void BLEMidi::begin()
{
    Serial.println("Initializing ESP32 MIDI");
    BLEDevice::init(_deviceName);

    BLEServer* pServer = BLEDevice::createServer();
    pServer->setCallbacks(this);

    // Create the BLE Service
    BLEService *pService = pServer->createService(BLEUUID("03b80e5a-ede8-4b33-a751-6ce34ec4c700"));

    // Create a BLE Characteristic
    _pCharacteristic = pService->createCharacteristic(
        BLEUUID("7772e5db-3868-4112-a1a9-f2669d106bf3"),
        BLECharacteristic::PROPERTY_READ   |
        BLECharacteristic::PROPERTY_WRITE  |
        BLECharacteristic::PROPERTY_WRITE_NR |
        BLECharacteristic::PROPERTY_NOTIFY |
        BLECharacteristic::PROPERTY_INDICATE
    );

    _pCharacteristic->addDescriptor(new BLE2902());
    _pCharacteristic->setCallbacks(this);

    pService->start();

    // start advertising
    BLEAdvertising *pAdvertising = pServer->getAdvertising();
    pAdvertising->addServiceUUID(pService->getUUID());
    pAdvertising->start();
}

void BLEMidi::onConnect(BLEServer* pServer)
{
    Serial.println("[BLEMidi] onConnect");
    _deviceConnected = true;
    _runningStatus = 0;
}

void BLEMidi::onDisconnect(BLEServer* pServer)
{
    Serial.println("[BLEMidi] onDisconnect");
    _deviceConnected = false;    
}

void BLEMidi::onRead(BLECharacteristic* pCharacteristic)
{
    Serial.println("[BLEMidi] onRead");
}

void BLEMidi::onWrite(BLECharacteristic* pCharacteristic)
{
    const std::string& data = pCharacteristic->getValue();
    size_t i = 1; // start at second byte

    // if (F_DEBUG) {
    //     Serial.print("[BLEMidi] message: ");
    //     for (size_t j = 0; j < data.size(); ++j) {
    //         Serial.printf("%d, ", int(data[j]));
    //     }
    //     Serial.print("\n");
    // }

    while (i < data.size()) {
        // discard timestamp
        if (data[i] & 0x80) {
            ++i;
        }

        // determine status
        char status = 0;
        char v = data[i];

        if (v & 0x80) {
            status = v;
            ++i;
            // channel message, update running status
            if (v < 0xf0) {
                _runningStatus = v;
            }   
        }
        // not a status byte, use running status if available
        else if (_runningStatus > 0) {
            status = _runningStatus;
        }

        // status undetermined, continue with next byte
        if (status == 0) {
            continue;
        }

        size_t length = MidiMessage::lengthFromByte0(status);
        MidiMessage message;

        switch(length) {
        case 0:
            // TODO: system exclusive, do we always get the entire message?
            if (status == 0xf0) {
                size_t pos = i - 1;
                while(data[i++] != 0xf7);
                // enqueue message without EOX
                enqueueSysEx(data.substr(pos, i - pos - 2));
                continue;
            }
            break;
        case 1:
            message.setBytes(status);
            break;
        case 2:
            message.setBytes(status, data[i]);
            i += 1;
            break;
        case 3:
            message.setBytes(status, data[i], data[i+1]);
            i += 2;
            break;    
        }

        if (length > 0) {
            enqueueMessage(message);
        }
    }
}

void BLEMidi::onNotify(BLECharacteristic* pCharacteristic)
{
    Serial.println("[BLEMidi] onNotify");
}

void BLEMidi::onStatus(BLECharacteristic* pCharacteristic, BLECharacteristicCallbacks::Status s, uint32_t code)
{
    Serial.println("[BLEMidi] onStatus");
}
*/