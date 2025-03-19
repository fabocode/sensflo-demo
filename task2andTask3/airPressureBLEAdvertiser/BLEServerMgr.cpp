#include "BLEServerMgr.h"
#include <string.h>

MyServerCallbacks::MyServerCallbacks(BLEServerMgr* mgr) : bleMgr(mgr) {

}

void MyServerCallbacks::onConnect(BLEServer *pServer) {
  bleMgr->deviceConnected = true;

  Serial.println("BLE client connected");
}

void MyServerCallbacks::onDisconnect(BLEServer *pServer) {
  bleMgr->deviceConnected = false;

  Serial.println("BLE client disconnected");
}

BLEServerMgr::BLEServerMgr() :
    pServer(nullptr),
    pSensorCharacteristic(nullptr),
    pCounterCharacteristic(nullptr),
    deviceConnected(false) {
}

void BLEServerMgr::init(const char* deviceName) {
  BLEDevice::init(deviceName);
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks(this));

  BLEService *pService = pServer->createService(SERVICE_UUID);

  pSensorCharacteristic = pService->createCharacteristic(
                          SENSOR_CHARACTERISTIC_UUID,
                          BLECharacteristic::PROPERTY_READ |
                          BLECharacteristic::PROPERTY_NOTIFY
                      );
  pSensorCharacteristic->addDescriptor(new BLE2902());

  pCounterCharacteristic = pService->createCharacteristic(
                              COUNTER_CHARACTERISTIC_UUID,
                              BLECharacteristic::PROPERTY_READ |
                              BLECharacteristic::PROPERTY_NOTIFY
                              );
  pCounterCharacteristic->addDescriptor(new BLE2902());

  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);

  BLEDevice::startAdvertising();
  Serial.println("BLE advertising started");
}

void BLEServerMgr::updatePressureData(const char* value) {
  if (pSensorCharacteristic) {
    // Update the characteristic value and notify connected client
    pSensorCharacteristic->setValue((uint8_t*)value, strlen(value));

    pSensorCharacteristic->notify();
  }
}

void BLEServerMgr::updateCounterData(int counter) {
  if (pCounterCharacteristic) {
    char counterStr[16];

    snprintf(counterStr, sizeof(counterStr), "%d", counter);

    pCounterCharacteristic->setValue((uint8_t*)counterStr, strlen(counterStr));
    pCounterCharacteristic->notify();
  }
}

bool BLEServerMgr::isConnected() {
  return deviceConnected;
}
