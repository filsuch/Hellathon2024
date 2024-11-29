#pragma once 
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define SERVICE_UUID "0421a773-d187-4e1d-b526-141719c52f48"
#define CHARACTERISTIC_UUID "458727d8-721b-4f3e-a5de-295f0501d2d4"

class SmartBluetooth
{
private:
    static inline BLEServer *bleServer = NULL;
    static inline BLECharacteristic *bleCharacteristic = NULL;   
public:

    static void begin();

};

