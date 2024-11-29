
#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>

class WiFiManager {
public:
    void init(const char* ssid, const char* password);
    void scanNetworks();
    bool connectToNetwork();
    String getLocalIP();

private:
    const char* ssid;
    const char* password;
};

#endif
