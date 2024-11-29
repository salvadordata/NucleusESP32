#ifndef BLESPAM_WITH_PASSWORD_H
#define BLESPAM_WITH_PASSWORD_H

#include <Arduino.h>
#include "BLEDevice.h"
#include "SdFat.h" // For SD card handling

class BLESpamWithPassword {
public:
    void aj_adv_with_password(int spamChoice, const String& password, const String& username = "");
    void captureBLEInfo();
    void saveToSD(const String& data);
    void displayToScreen(const String& data);
private:
    void spamBLE(int choice);
};

#endif
