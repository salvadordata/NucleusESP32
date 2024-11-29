#include "BLEspam_with_password.h"
#include "modules/ETC/SDcard.h"
#include <TFT_eSPI.h>

// Reference to the global SD card handler
extern SDcard& SD_CARD;

// TFT handler for displaying passwords (assumes existing TFT setup)
extern TFT_eSPI tft;

/**
 * Extended BLE spam functionality that handles passwords.
 */
void BLESpamWithPassword::aj_adv_with_password(int ble_choice, const String &password) {
    // Save password to SD card
    if (SD_CARD.append("/passwords.txt", password.c_str())) {
        Serial.println("Password saved to SD card.");
    } else {
        Serial.println("Failed to save password to SD card.");
    }

    // Display the password on the TFT
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 0);
    tft.setTextSize(2);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.println("Password:");
    tft.println(password);

    // Perform BLE spam
    this->aj_adv(ble_choice);
}
