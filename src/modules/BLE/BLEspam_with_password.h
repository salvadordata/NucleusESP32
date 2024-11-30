#ifndef BLESPAM_WITH_PASSWORD_H
#define BLESPAM_WITH_PASSWORD_H

#include <Arduino.h>

class BLESpamWithPassword {
public:
    void aj_adv_with_password(int spamChoice, const String& password, const String& username = "");
    void handleTouchInput(int x, int y); // Handle touch input for BLE spam selection
    void drawSpamOptions(); // Display options for BLE spam modes
    void setSpamChoice(int choice); // Set spam choice dynamically
    void setPassword(const String& password); // Set password dynamically

private:
    void spamBLE(int choice);
    void captureBLEInfo();
    void saveToSD(const String& data);
    void displayToScreen(const String& data);

    int currentSpamChoice = 1; // Default spam choice
    String currentPassword = "DefaultPassword"; // Default password
};

#endif
