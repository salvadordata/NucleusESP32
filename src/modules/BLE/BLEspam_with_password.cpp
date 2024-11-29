#include "BLESpam_with_password.h"
#include "SdFat.h"
#include <esp32_smartdisplay.h>

void BLESpamWithPassword::aj_adv_with_password(int spamChoice, const String& password, const String& username) {
    Serial.println("Starting BLE Spam with Password...");

    // Simulate BLE spam based on choice
    spamBLE(spamChoice);

    // Prepare the data string
    String dataToSave = "Password: " + password;
    if (username.length() > 0) {
        dataToSave += ", Username: " + username;
    }

    // Capture BLE network information
    captureBLEInfo();

    // Save data to SD card
    saveToSD(dataToSave);

    // Display data on screen
    displayToScreen(dataToSave);
}

void BLESpamWithPassword::spamBLE(int choice) {
    Serial.println("Spamming BLE Devices with choice: " + String(choice));
    // Simulated BLE spam logic; replace with actual spam calls.
}

void BLESpamWithPassword::captureBLEInfo() {
    Serial.println("Capturing BLE network information...");

    BLEScan* pBLEScan = BLEDevice::getScan();
    pBLEScan->setActiveScan(true);
    BLEScanResults scanResults = pBLEScan->start(5); // Scan for 5 seconds

    for (int i = 0; i < scanResults.getCount(); ++i) {
        BLEAdvertisedDevice advertisedDevice = scanResults.getDevice(i);
        String deviceInfo = "Device: " + advertisedDevice.getName().c_str() +
                            ", MAC: " + advertisedDevice.getAddress().toString().c_str() +
                            ", RSSI: " + String(advertisedDevice.getRSSI());
        Serial.println(deviceInfo);

        // Save BLE info to SD card
        saveToSD(deviceInfo);

        // Display BLE info to screen
        displayToScreen(deviceInfo);
    }
}

void BLESpamWithPassword::saveToSD(const String& data) {
    SdFat SD;
    if (SD.begin()) {
        File file = SD.open("/BLE_Info.txt", FILE_WRITE);
        if (file) {
            file.println(data);
            file.close();
            Serial.println("Data saved to SD: " + data);
        } else {
            Serial.println("Error opening SD card file.");
        }
    } else {
        Serial.println("SD card initialization failed.");
    }
}

void BLESpamWithPassword::displayToScreen(const String& data) {
    // Assumes a smart display library is being used
    Serial.println("Displaying to screen: " + data);
    // Add actual display update logic here
}
