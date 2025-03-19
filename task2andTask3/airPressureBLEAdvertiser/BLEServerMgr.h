#ifndef BLE_SERVER_MGR_H
#define BLE_SERVER_MGR_H

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// BLE Settings (Custom UUIDs for the service and characteristic)
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define SENSOR_CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define COUNTER_CHARACTERISTIC_UUID "d0e60a51-9e38-41c2-a6ed-ec6ef86b7bb3"

class BLEServerMgr;

class MyServerCallbacks : public BLEServerCallbacks {
public:
  MyServerCallbacks(BLEServerMgr* mgr);
  void onConnect(BLEServer *pServer) override;
  void onDisconnect(BLEServer *pServer) override;
private:
  BLEServerMgr* bleMgr;
};

class BLEServerMgr {
  friend class MyServerCallbacks;  // Updates deviceConnected
public:
  BLEServerMgr();

  // Initializes BLE as a server with the defined service and characteristic.
  void init(const char* deviceName = "AirPressureSensor");
  void updatePressureData(const char* value);
  void updateCounterData(int counter);
  bool isConnected();

private:
  BLEServer* pServer;
  BLECharacteristic* pSensorCharacteristic;
  BLECharacteristic* pCounterCharacteristic;
  bool deviceConnected;
};

#endif // BLE_SERVER_MGR_H
