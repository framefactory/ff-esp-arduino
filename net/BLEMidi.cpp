/**
 * ESP/Arduino Net Library
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "BLEMidi.h"

F_USE_NAMESPACE

BLEMidi::BLEMidi()
{
}

void BLEMidi::begin()
{
    Serial.println("Initializing ESP32 MIDI");
    BLEDevice::init("ESP32 MIDI");

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
    Serial.println("ESP32 MIDI onWrite");
    std::string data = pCharacteristic->getValue();
    for (size_t i = 2; i < data.size(); ++i) {
        Serial.printf("#%d: %d\n", i - 2, data[i]);
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
