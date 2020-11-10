/**
 * ESP/Arduino Net Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "BLEMidi.h"

F_USE_NAMESPACE

BLEMidi::BLEMidi() :
    _pCharacteristic(nullptr),
    _deviceConnected(false),
    _pListener(nullptr)
{
}

void BLEMidi::begin()
{
    Serial.println("Initializing ESP32 MIDI");
    BLEDevice::init("DotMatrix");

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

void BLEMidi::setListener(MidiListener* pListener)
{
    _pListener = pListener;
}

MidiMessage BLEMidi::popMessage()
{
    MidiMessage message = _eventQueue.front();
    _eventQueue.pop();
    return message;
}


void BLEMidi::onConnect(BLEServer* pServer)
{
    Serial.println("ESP32 MIDI Connected");
    _deviceConnected = true;
}

void BLEMidi::onDisconnect(BLEServer* pServer)
{
    Serial.println("ESP32 MIDI Disconnected");
    _deviceConnected = false;    
}

void BLEMidi::onRead(BLECharacteristic* pCharacteristic)
{
    Serial.println("ESP32 MIDI onRead");
}

void BLEMidi::onWrite(BLECharacteristic* pCharacteristic)
{
    const std::string& data = pCharacteristic->getValue();
    char rs = 0;
    char s = 0;
    size_t i = 2; // start at third byte, discard timestamp

    while (i < data.size()) {
        // determine status
        char v = data[i];

        if (v & 0x80) {
            s = v;
            ++i;
            // channel message, update running status
            if (v < 0xf0) {
                rs = v;
            }   
        }
        // not a status byte, use running status if available
        else if (rs > 0) {
            s = rs;
        }

        size_t length = MidiMessage::lengthFromStatus(s);
        MidiMessage message;

        switch(length) {
        case 0:
            // system exclusive, read and discard for now
            if (s == 0xf0) {
                while(data[i++] != 0xf7);
            }
            break;
        case 1:
            message.setBytes(s);
            break;
        case 2:
            message.setBytes(s, data[i]);
            i += 1;
            break;
        case 3:
            message.setBytes(s, data[i], data[i+1]);
            i += 2;
            break;    
        }

        if (length > 0) {
            if (_pListener) {
                _pListener->onMidiMessage(message);
            }
            else if (_eventQueue.size() < 256) {
                _eventQueue.push(message);
            }
        }
    }
}

void BLEMidi::onNotify(BLECharacteristic* pCharacteristic)
{
    Serial.println("ESP32 MIDI onNotify");
}

void BLEMidi::onStatus(BLECharacteristic* pCharacteristic, Status s, uint32_t code)
{
    Serial.println("ESP32 MIDI onStatus");
}
