#ifndef GLOBALS_H
#define GLOBALS_H

 enum CC1101_PRESET {
     AM650,
     AM270,
     FM238,
     FM476,
     FM95,
     FM15k,
     PAGER,
     HND1,
     HND2,
     CUSTOM
 };

extern CC1101_PRESET  C1101preset;



#include <lvgl.h>
#include <vector>
#include <stdio.h>
#include <string.h>
   //---------------------------------------------------------------------------//
  //-----------------------------SETINGS---------------------------------------//
 //---------------------------------------------------------------------------//
// Pin configuration for CC1101
#define CC1101_CS   16  // Chip Select
#define CC1101_MOSI 4   // Master Out Slave In
#define CC1101_MISO 35  // Master In Slave Out
#define CC1101_SCLK 22  // Serial Clock

#define CCGDO0A 17      // GDO0
//#define CCGDO2A 16      // GDO2

#define CC1101_CCGDO0A 17      // GDO0
//#define CC1101_CCGDO2A 16      // GDO2

#define CMD_READ_Y  0x90 // Command for XPT2046 to read Y position
#define CMD_READ_X  0xD0 // Command for XPT2046 to read X position

// Pin definitions for touchscreen and SD card
#define MOSI_PIN 32
#define MISO_PIN 39
#define CLK_PIN  25
#define CS_PIN   33

#define SD_CS 5 // SD card CS pin

extern bool teslaSucessFlag;
extern uint8_t RFstate;

   //---------------------------------------------------------------------------//
  //-----------------------------ENUMBS----------------------------------------//
 //---------------------------------------------------------------------------//
// C1101 Presets






// C1101 state mashine
enum C1101State
{
  STATE_IDLE,
  STATE_GENERATOR,
  STATE_ANALYZER,
  STATE_RCSWITCH,
  STATE_SCANNER,
  STATE_CAPTURE,
  STATE_PLAYBACK,
  STATE_TESLA_US,
  STATE_TESLA_EU,
  STATE_AUDIO_TEST,
  STATE_SEND_FLIPPER,
  STATE_WIFI_SCAN,
  STATE_SEND_BLESPAM,
  STATE_PULSE_SCAN,
  STATE_DETECT,
};

// Current State
extern uint8_t C1101CurrentState;

extern bool C1101LoadPreset;
extern bool receiverEnabled;
extern float CC1101_MHZ;

enum RFStateMashine {
  GENERAL,
  WARM_UP
};



enum BTState
{
  STATE_SOUR_APPLE_IDLE,
  STATE_SOUR_APPLE,
  STATE_BTSPAM,
  STATE_BT_IDDLE,
};

    typedef struct
{
    std::vector<unsigned long> samples;
    volatile unsigned long lastReceiveTime = 0;
} recievedData;

// Current State
extern uint8_t BTCurrentState;

//////////////////////////////////////////////////////////////////////////
//FLAGS
///////////////////
extern bool CC1101_init; 
extern bool CC1101_RCSwitch_init; 
extern bool CC1101_RCSwitch_listen;
extern bool CC1101_RCSwitch_play;
extern bool bruteIsRunning;

// Function declarations
typedef void (*TouchCallback)();

CC1101_PRESET convert_str_to_enum(const char * selected_str);
const char* presetToString(CC1101_PRESET preset);
const uint8_t* presetTobyteArray(CC1101_PRESET preset);

extern char* current_dir;
//extern char* selected_file;
//extern lv_obj_t* selected_label;
extern lv_obj_t* selected_btn;

extern uint16_t bruteCounter;


//file browser globals

extern char* current_dir;
extern char* selected_file;

const uint8_t AM270_regs[] = {0x02, 0x0D, 0x03, 0x07, 0x08, 0x32, 0x0B, 0x06, 0x14, 0x00, 0x13, 0x00, 0x12, 0x30, 0x11,
                                                                     0x32, 0x10, 0x17, 0x18, 0x18, 0x19, 0x18, 0x1D, 0x91, 0x1C, 0x00, 0x1B, 0x07, 0x20, 0xFB,
                                                                     0x22, 0x11, 0x21, 0xB6, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const uint8_t AM650_regs[] = {0x02, 0x0D, 0x03, 0x07, 0x08, 0x32, 0x0B, 0x06, 0x14, 0x00, 0x13, 0x00, 0x12, 0x30, 0x11,
                                                                     0x32, 0x10, 0x17, 0x18, 0x18, 0x19, 0x18, 0x1D, 0x91, 0x1C, 0x00, 0x1B, 0x07, 0x20, 0xFB,
                                                                     0x22, 0x11, 0x21, 0xB6, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const uint8_t FM238_regs[] = {0x02, 0x0D, 0x03, 0x07, 0x08, 0x32, 0x0B, 0x06, 0x14, 0x00, 0x13, 0x00, 0x12, 0x30, 0x11,
                                                                          0x32, 0x10, 0x17, 0x18, 0x18, 0x19, 0x18, 0x1D, 0x91, 0x1C, 0x00, 0x1B, 0x07, 0x20, 0xFB,
                                                                          0x22, 0x11, 0x21, 0xB6, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const uint8_t FM476_regs[] = {0x02, 0x0D, 0x03, 0x07, 0x08, 0x32, 0x0B, 0x06, 0x14, 0x00, 0x13, 0x00, 0x12, 0x30, 0x11,
                                                                          0x32, 0x10, 0x17, 0x18, 0x18, 0x19, 0x18, 0x1D, 0x91, 0x1C, 0x00, 0x1B, 0x07, 0x20, 0xFB,
                                                                          0x22, 0x11, 0x21, 0xB6, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const uint8_t FM95_regs[] = {0x02, 0x0D, 0x03, 0x07, 0x08, 0x32, 0x0B, 0x06, 0x14, 0x00, 0x13, 0x00, 0x12, 0x30, 0x11,
                                                                      0x32, 0x10, 0x17, 0x18, 0x18, 0x19, 0x18, 0x1D, 0x91, 0x1C, 0x00, 0x1B, 0x07, 0x20, 0xFB,
                                                                      0x22, 0x11, 0x21, 0xB6, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const uint8_t FM15k_regs[] = {0x02, 0x0D, 0x03, 0x07, 0x08, 0x32, 0x0B, 0x06, 0x14, 0x00, 0x13, 0x00, 0x12, 0x30, 0x11,
                                                                      0x32, 0x10, 0x17, 0x18, 0x18, 0x19, 0x18, 0x1D, 0x91, 0x1C, 0x00, 0x1B, 0x07, 0x20, 0xFB,
                                                                      0x22, 0x11, 0x21, 0xB6, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const uint8_t HONDA1[] =    {0x02, 0x0D, 0x0B, 0x06, 0x08, 0x32, 0x07, 0x04, 0x14, 0x00, 0x13, 0x02, 0x12, 0x04, 0x11, 0x36,
                                                                       0x10, 0x69, 0x15, 0x32, 0x18, 0x18, 0x19, 0x16, 0x1D, 0x91, 0x1C, 0x00, 0x1B, 0x07, 0x20,
                                                                       0xFB, 0x22, 0x10, 0x21, 0x56, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,};

const uint8_t HONDA2[] =  {0x02, 0x0D, 0x0B, 0x06, 0x08, 0x32, 0x07, 0x04, 0x14, 0x00, 0x13, 0x02, 0x12, 0x07, 0x11, 0x36, 0x10, 0xE9, 0x15, 0x32, 0x18, 0x18, 0x19, 0x16, 0x1D, 0x92, 0x1C, 0x40, 0x1B, 0x03, 0x20, 0xFB, 0x22, 0x10, 0x21, 0x56, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};


#endif // GLOBALS_H
