#ifndef BLE_MANAGER_H
#define BLE_MANAGER_H

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

class BLEManager {
public:
    void init(const char* deviceName);
    void scanDevices();
    void startAdvertising();

private:
    BLEScan* pBLEScan;
};

#endif
