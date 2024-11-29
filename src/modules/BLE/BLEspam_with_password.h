#ifndef BLESPAM_WITH_PASSWORD_H
#define BLESPAM_WITH_PASSWORD_H

#include "modules/BLE/BLESpam.h"

class BLESpamWithPassword : public BLESpam {
public:
    void aj_adv_with_password(int ble_choice, const String &password);
};

#endif
