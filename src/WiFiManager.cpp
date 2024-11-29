#include "WiFiManager.h"

void WiFiManager::init(const char* ssid, const char* password) {
    this->ssid = ssid;
    this->password = password;
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
}

void WiFiManager::scanNetworks() {
    Serial.println("Scanning for Wi-Fi networks...");
    int n = WiFi.scanNetworks();
    for (int i = 0; i < n; i++) {
        Serial.printf("%d: %s, Signal Strength: %d dBm\n", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
    }
}

bool WiFiManager::connectToNetwork() {
    Serial.println("Connecting to Wi-Fi...");
    WiFi.begin(ssid, password);
    unsigned long startAttemptTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
        delay(500);
        Serial.print(".");
    }
    return WiFi.status() == WL_CONNECTED;
}

String WiFiManager::getLocalIP() {
    return WiFi.localIP().toString();
}
