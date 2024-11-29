#include "./include/bluetooth.h"


void SmartBluetooth::begin() {
    // Inicializace BLE zařízení
    BLEDevice::init("SmartUmbrella");
    SmartBluetooth::bleServer = BLEDevice::createServer();

    // Vytvoření služby
    BLEService *service = bleServer->createService(SERVICE_UUID);

    // Vytvoření charakteristiky
    SmartBluetooth::bleCharacteristic = service->createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
    );
}