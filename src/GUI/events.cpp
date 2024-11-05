#include "GUI/ScreenManager.h"
#include "modules/ETC/SDcard.h"
#include <RCSwitch.h>
#include <Arduino.h>
#include "modules/RF/CC1101.h"
#include "globals.h"
#include <cstring> 
#include <iostream>
#include <unordered_map>
#include "ELECHOUSE_CC1101_SRC_DRV.h"
#include "main.h"
#include "modules/BLE/SourApple.h"
#include "modules/BLE/BLESpam.h"
#include "events.h"
#include "lv_fs_if.h"
#include <cstdio>   // For snprintf
using namespace std;

#define MAX_PATH_LENGTH 256

int SpamDevice = 1;

CC1101_CLASS cc1101;

ScreenManager& screenMgr = ScreenManager::getInstance();


char EVENTS::frequency_buffer[10];
char EVENTS::selected_str[32];  



void EVENTS::btn_event_playZero_run(lv_event_t* e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED) {
        screenMgr.createFileExplorerScreen();
    }
}


void EVENTS::btn_event_Replay_run(lv_event_t* e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED) {          
          screenMgr.createReplayScreen();
    }
}

void EVENTS::btn_event_BruteForce_run(lv_event_t* e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED) {          
          screenMgr.createBruteForceScreen();
    }
}

void EVENTS::btn_event_teslaCharger_run(lv_event_t* e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED) {
     //   teslaScreen();
        // Uncomment and use if needed:
        // if (sendTeslaSignal(433.92)) {
        //     teslaSucessFlag = true;
        // }
        // if (sendTeslaSignal(315.00)) {
        //     teslaSucessFlag = true;
        // }
    }
}


void EVENTS::ta_freq_event_cb(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);
     lv_obj_t * kb = (lv_obj_t *)lv_event_get_user_data(e); 

    lv_obj_t * text_area = screenMgr.getTextArea();
     lv_obj_t * ta = screenMgr.getFreqInput();
    // lv_obj_t * presetDropdown = screenMgr.getPresetDropdown();

    if (code == LV_EVENT_FOCUSED) {
         lv_keyboard_set_textarea(kb, ta);
         lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);  // Show the keyboard
         Serial.println("Keyboard shown");
     } else if (code == LV_EVENT_DEFOCUSED || code == LV_EVENT_READY) {
         lv_keyboard_set_textarea(kb, NULL);
         lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);  // Hide the keyboard

         strncpy(frequency_buffer, lv_textarea_get_text(ta), sizeof(frequency_buffer) - 1);
         frequency_buffer[sizeof(frequency_buffer) - 1] = '\0';  // Ensure null termination
         Serial.print("Frequency set to: \n");
         
         cc1101.CC1101_FREQ = atof(lv_textarea_get_text(ta));
         lv_textarea_add_text(text_area, "Frequency set to: \n");
         Serial.println(frequency_buffer);
         lv_textarea_add_text(text_area, frequency_buffer);
     }    
}

void EVENTS::ta_filename_event_cb(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * kb = static_cast<lv_obj_t *>(lv_event_get_user_data(e));

    lv_obj_t* ta = screenMgr.getFilenameInput();
    lv_obj_t* text_area = screenMgr.getTextArea();

    if (ta && kb && text_area) {
        if (code == LV_EVENT_FOCUSED) {
            lv_keyboard_set_textarea(kb, ta);
            lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);  
            Serial.println("QWERTY Keyboard shown for Filename");
            lv_obj_add_flag(text_area, LV_OBJ_FLAG_HIDDEN); 
        } else if (code == LV_EVENT_DEFOCUSED || code == LV_EVENT_READY) {
            lv_obj_clear_flag(text_area, LV_OBJ_FLAG_HIDDEN);  
            lv_keyboard_set_textarea(kb, NULL);
            lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);  
        }
    } else {
        Serial.println("Error: Filename input, keyboard, or text_area is NULL");
    }
}


void EVENTS::kb_event_cb(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_READY || code == LV_EVENT_CANCEL) {
        Serial.println("Keyboard hidden by confirm/cancel");
    }
}

void EVENTS::kb_qwert_event_cb(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_READY || code == LV_EVENT_CANCEL) {
        Serial.println("QWERTY Keyboard hidden by confirm/cancel");
    }
}


void EVENTS::save_RF_to_sd_event(lv_event_t * e) {
    lv_obj_t* text_area = screenMgr.getTextArea();
    lv_textarea_set_text(text_area, "Moving to SD\n");
   // CC1101.saveToSD();
    lv_textarea_set_text(text_area, "Done.");
}

void EVENTS::saveSignal(lv_event_t * e) {
    Serial.print("event se spustil");
    CC1101.saveSignal();
}




void EVENTS::ProtAnalyzerloop() {
   //
    
}

void EVENTS::replayEvent(lv_event_t * e) {
    lv_obj_t * text_area = screenMgr.getTextArea();
    lv_textarea_set_text(text_area, "Sending signal from buffer");

      Serial.print("event_playback_rec_play");

  if (C1101CurrentState == STATE_IDLE)
  {     
    lv_obj_t *ta = screenMgr.getTextArea();
    float freq = String(lv_textarea_get_text(ta)).toFloat();
    CC1101.setFrequency(freq);

    C1101CurrentState = STATE_PLAYBACK;
  }
  else
  {
    Serial.print("NOT IDLE");
  }
    lv_textarea_add_text(text_area, "Signal has been send");
}

void EVENTS::exitReplayEvent(lv_event_t * e) {
    screenMgr.createRFMenu();
}
void EVENTS::sendCapturedEvent(lv_event_t * e) {
    lv_obj_t * text_area = screenMgr.getTextAreaRCSwitchMethod();
    CC1101.sendRaw();
}

void EVENTS::btn_event_subGhzTools(lv_event_t * e) {
    screenMgr.createRFMenu();
}

 void EVENTS::btn_event_SourApple(lv_event_t * e){
    screenMgr.createSourAppleScreen();
    sourApple sa;
    sa.setup();
 }

  void EVENTS::btn_event_BTSpam(lv_event_t * e){
    screenMgr.createBTSPamScreen();
 }

  void EVENTS::btn_event_SourApple_Start(lv_event_t * e){
    lv_obj_t * ta = screenMgr.getTextAreaSourAple();
    lv_textarea_set_text(ta, "Running");
    BTCurrentState = STATE_SOUR_APPLE;
 }

  void EVENTS::btn_event_SourApple_Stop(lv_event_t * e){
    lv_obj_t * ta = screenMgr.getTextAreaSourAple();
    lv_textarea_set_text(ta, "Not running");
    BTCurrentState = STATE_SOUR_APPLE_IDLE;
 }

   void EVENTS::btn_event_BTSpam_Start(lv_event_t * e){
    //BLEDevice::init("");
    lv_obj_t * ta = screenMgr.getTextAreaBTSpam();
    lv_textarea_set_text(ta, "Running");
    int *SpamDevice = (int *)lv_event_get_user_data(e); 
    BLESpam spam;
    spam.aj_adv(*SpamDevice);
 }

  void EVENTS::btn_event_BTSpam_Stop(lv_event_t * e){
    lv_obj_t * ta = screenMgr.getTextAreaBTSpam();
    lv_textarea_set_text(ta, "Not running");
    BLESpam spam;
    BLEDevice::deinit();
 }

 

void EVENTS::btn_event_BTTools(lv_event_t * e) {
    screenMgr.createBTMenu();
}

void EVENTS::btn_event_mainMenu_run(lv_event_t* e) {   
    screenMgr.createmainMenu();
}

const char* presetStrings[] = {
    "AM650",
    "AM270",
    "FM238",
    "FM476",
    "FM95",
    "FM15k",
    "PAGER",
    "HND1",
    "HND2"
};


CC1101_PRESET EVENTS::stringToCC1101Preset(String presetStr) {
    presetStr.trim();

    for (int i = 0; i < sizeof(presetStrings) / sizeof(presetStrings[0]); i++) {
        if (presetStr == presetStrings[i]) {
            return static_cast<CC1101_PRESET>(i);  
        }
    }

    Serial.println("Invalid preset string: " + presetStr);  
    return AM650; 
}




void EVENTS::ta_preset_event_cb(lv_event_t * e) {
     char selected_text[32];
     lv_event_code_t code = lv_event_get_code(e);
     lv_obj_t* text_area = screenMgr.getTextArea();

    lv_dropdown_get_selected_str(screenMgr.C1101preset_dropdown_, selected_text, sizeof(selected_text));  // Copy selected text to the buffer

    if (code == LV_EVENT_VALUE_CHANGED) {
        C1101preset = stringToCC1101Preset(selected_text);
        lv_textarea_add_text(text_area, "Preset set to: ");
        lv_textarea_add_text(text_area,selected_text);
        lv_textarea_add_text(text_area, "\n");
    }  

    CC1101_PRESET preset = convert_str_to_enum(selected_text);
    C1101preset = preset;
    CC1101.loadPreset();

} 


void EVENTS::ta_rf_type_event_cb(lv_event_t * e) {
     char selected_text[32];
     lv_event_code_t code = lv_event_get_code(e);
     lv_obj_t* text_area = screenMgr.getTextArea();

    lv_dropdown_get_selected_str(screenMgr.C1101type_dropdown_, selected_text, sizeof(selected_text));  // Copy selected text to the buffer

    if (code == LV_EVENT_VALUE_CHANGED) {
        C1101preset = stringToCC1101Preset(selected_text);
        lv_textarea_add_text(text_area, "Type set to: ");
        lv_textarea_add_text(text_area,selected_text);
        lv_textarea_add_text(text_area, "\n");
    }  
}

// void EVENTS::listenRFEvent(lv_event_t * e) {


//     C1101LoadPreset = false;

//     float freq = atof(frequency_buffer);
//     char freq_str[20]; // Buffer to hold the converted float as a string
//     snprintf(freq_str, sizeof(freq_str), "%f", freq);

//     lv_textarea_add_text(text_area, freq_str);
//    // lv_textarea_set_text(text_area, "  " );
//     lv_textarea_set_text(text_area, String("Capture Started..").c_str());

//     ELECHOUSE_cc1101.setSidle();  // Set to idle state
//     ELECHOUSE_cc1101.goSleep();   // Put CC1101 into sleep mode
    
//     // Optionally disable chip select (CS) to fully power down the CC1101
//     digitalWrite(CC1101_CS, HIGH); 

//     CC1101.initrRaw();
//     delay(20);
//     C1101CurrentState = STATE_CAPTURE;

// }



void EVENTS::btn_event_RAW_REC_run(lv_event_t* e)
{
    char selected_text[32];
    char selected_text_type[32];
    char frequency_buffer[10];
    lv_obj_t * text_area = screenMgr.getTextArea();
    lv_obj_t * ta = screenMgr.getFreqInput();
    strncpy(frequency_buffer, lv_textarea_get_text(ta), sizeof(frequency_buffer) - 1);
    frequency_buffer[sizeof(frequency_buffer) - 1] = '\0'; 
    CC1101_MHZ = atof(frequency_buffer);
    lv_dropdown_get_selected_str(screenMgr.C1101preset_dropdown_, selected_text, sizeof(selected_text));  // Copy selected text to the buffer
    lv_dropdown_get_selected_str(screenMgr.C1101type_dropdown_, selected_text_type, sizeof(selected_text_type));  // Copy selected text to the buffer



    lv_textarea_set_text(text_area, "Waiting for signal.\n");

     CC1101.setCC1101Preset(convert_str_to_enum(selected_text));
   //  CC1101.loadPreset();
     if(strcmp(selected_text_type, "Raw") == 0){
     CC1101.enableReceiver();
     } else {

        CC1101.enableRCSwitch();
        lv_textarea_add_text(text_area, "Decoder active.\n");
     }
   //  CC1101.setFrequency(CC1101_MHZ);
     delay(20);
    
    C1101CurrentState = STATE_ANALYZER;
}

void  EVENTS::back_btn_event_cb_sub(lv_event_t* e) {
    Serial.println("Back button clicked.");

    char* last_slash = strrchr(current_dir, '/');
    if (last_slash && last_slash != current_dir) {
        *last_slash = '\0';  // Remove the last directory from the path

        // Ensure the path ends with '/'
        last_slash = strrchr(current_dir, '/');
        if (last_slash) {
            *(last_slash + 1) = '\0';
        } else {
            current_dir[0] = '/';
            current_dir[1] = '\0';
        }
        size_t len = strlen(current_dir); 

    if (strcmp(current_dir, "/") != 0 && len > 0) {  // Ensure it's not root and the string is not empty
        if (current_dir[len - 1] == '/') {
            current_dir[len - 1] = '\0';  // Remove the last character by terminating the string early
        }
    }

    }

        Serial.print("Updated current_dir (after going back): ");
        Serial.println(current_dir);
        screenMgr.updateFileList(current_dir);
}

void  EVENTS::load_btn_event_cb_sub(lv_event_t* e) {
    CC1101_CLASS CC1101;
    Serial.println("Load button clicked.");
    if (strlen(selected_file) > 0) {
    detachInterrupt(CC1101_CCGDO0A);
    CC1101.initrRaw();
    ELECHOUSE_cc1101.setCCMode(0); 
    ELECHOUSE_cc1101.setPktFormat(3);
    ELECHOUSE_cc1101.SetTx();
    pinMode(CC1101_CCGDO0A, OUTPUT);
        Serial.print("Loading file: ");
        Serial.println(selected_file);
        screenMgr.useSelectedFile(selected_file);
    } else {
        Serial.println("No file selected.");
    }
}

void  EVENTS::delete_btn_event_cb_sub(lv_event_t* e) {
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_LONG_PRESSED) {
    const char *path = (const char *)lv_event_get_user_data(e); 
    if(deleteFile(path)){
            lv_label_set_text(selected_label, "File has been deleted");
    }
    screenMgr.updateFileList(current_dir);
    }
}

void EVENTS::file_btn_event_cb_sub(lv_event_t* e) {
    delay(500);
    Serial.println("File button clicked.");
    
 //   lv_obj_t* btn = lv_event_get_target(e);  // Get the button that was clicked THIS NEED TO FIX
    const char* file_or_folder_name = (const char*)lv_event_get_user_data(e);  // Get the file/folder name from user data

    Serial.print("File/Folder selected: ");
    Serial.println(file_or_folder_name);

    if (file_or_folder_name[strlen(file_or_folder_name) - 1] == '/') {  // If it's a folder
        Serial.println("Detected as a folder.");

        size_t dir_len = strlen(current_dir);
        size_t item_len = strlen(file_or_folder_name);

        if (dir_len + item_len < MAX_PATH_LENGTH) {
            // Append folder name to current directory
            // Ensure that the path is relative to the mount point
            strcat(current_dir, file_or_folder_name);
            Serial.print("Updated current_dir (after entering folder): ");
            Serial.println(current_dir);
            size_t length = strlen(current_dir);
            screenMgr.updateFileList(std::string(current_dir, length - 1).c_str());
        } else {
            Serial.println("Directory path too long, can't navigate.");
        }
    } else {  // If it's a file
        Serial.println("Detected as a file.");

        if (selected_btn) {
            lv_obj_set_style_bg_color(selected_btn, lv_color_white(), 0);  // Reset previous selection
            Serial.println("Reset previous selection.");
        }
       // selected_btn = btn;
     //   lv_obj_set_style_bg_color(selected_btn, lv_color_hex(0x88DD88), 0);  // Highlight selected file
        Serial.println("Highlighted selected file.");

        snprintf(selected_file, MAX_PATH_LENGTH, "%s%s", current_dir, file_or_folder_name);
        lv_label_set_text_fmt(selected_label, "Selected: %s", file_or_folder_name);
        Serial.print("Updated selected_file: ");
        Serial.println(selected_file);
    }
}

void EVENTS::btn_event_brute_run(lv_event_t* e) {
    char string[32]; 
    CC1101.setCC1101Preset(AM650);
    lv_obj_t * text_area__BruteForce = screenMgr.getTextAreaBrute();
    lv_dropdown_get_selected_str(screenMgr.brute_dropdown_, string, sizeof(string));    
    lv_textarea_set_text(text_area__BruteForce, "Brute forcing");
    delay(1000);
    if(strcmp(string, "Czech Bells") == 0) {
        Serial.println("czech bells");
    }
    C1101CurrentState = STATE_BRUTE;
}

void EVENTS::confirm_delete_event_handler(lv_event_t * e)
{
lv_obj_t * msgbox = static_cast<lv_obj_t *>(lv_event_get_user_data(e));
    lv_obj_t * yes_btn = static_cast<lv_obj_t *>(lv_obj_get_user_data(msgbox));
    lv_obj_t * clicked_btn = static_cast<lv_obj_t *>(lv_event_get_target(e));

    if (clicked_btn == yes_btn) {
        // The "Yes" button was clicked
        if(deleteFile(selected_file_path)) {
            LV_LOG_USER("File deleted successfully.");

            // Refresh the file explorer to reflect the deletion
            lv_obj_t * file_explorer = static_cast<lv_obj_t *>(lv_event_get_user_data(e));
            const char * cur_path = lv_file_explorer_get_current_path(file_explorer);
            lv_file_explorer_open_dir(file_explorer, cur_path);
        } else {
            LV_LOG_USER("Failed to delete file.");
        }
    }
    // Close the message box regardless of the button clicked
    lv_obj_del(msgbox);
}



void EVENTS::btn_event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = static_cast<lv_obj_t *>(lv_event_get_target(e));
    lv_obj_t * file_explorer = static_cast<lv_obj_t *>(lv_event_get_user_data(e));

    if(code == LV_EVENT_VALUE_CHANGED) {
        if(lv_obj_has_state(btn, LV_STATE_CHECKED))
            lv_obj_add_flag(file_explorer, LV_OBJ_FLAG_HIDDEN);
        else
            lv_obj_clear_flag(file_explorer, LV_OBJ_FLAG_HIDDEN);
    }
}


void EVENTS::dd_event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * dd = static_cast<lv_obj_t *>(lv_event_get_target(e));
    lv_obj_t * file_explorer = static_cast<lv_obj_t *>(lv_event_get_user_data(e));

    if(code == LV_EVENT_VALUE_CHANGED) {
        char buf[32];
        lv_dropdown_get_selected_str(dd, buf, sizeof(buf));
        if(strcmp(buf, "NONE") == 0) {
            lv_file_explorer_set_sort(file_explorer, LV_EXPLORER_SORT_NONE);
        } else if(strcmp(buf, "KIND") == 0) {
            lv_file_explorer_set_sort(file_explorer, LV_EXPLORER_SORT_KIND);
        }
    }
}



bool EVENTS::deleteFile(const char *path)
{
    LV_LOG_USER("Attempting to delete file: %s", path);

    // Use lv_fs_remove to delete the file through the filesystem driver
  //  lv_fs_res_t res = fs_remove(nullptr, path);

    // if(res == LV_FS_RES_OK) {
    //     LV_LOG_USER("File deleted successfully.");
    //     return true;
    // } else {
    //     LV_LOG_USER("Failed to delete file. Error code: %d", res);
    //     return false;
    // }
}

void EVENTS::file_explorer_event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = static_cast<lv_obj_t *>(lv_event_get_target(e));

    if(code == LV_EVENT_VALUE_CHANGED) {
        // Retrieve selected file path and name
        const char * cur_path = lv_file_explorer_get_current_path(obj);
        const char * sel_fn = lv_file_explorer_get_selected_file_name(obj);

        // Construct the full file path
        snprintf(selected_file_path, sizeof(selected_file_path), "%s/%s", cur_path, sel_fn);

        LV_LOG_USER("Selected file: %s", selected_file_path);

        // Create the message box
        lv_obj_t * mbox = lv_msgbox_create(lv_scr_act());
        lv_obj_set_size(mbox, 200, 100);
        lv_obj_align(mbox, LV_ALIGN_CENTER, 0, 0);

        // Add label with confirmation message
        lv_obj_t * label = lv_label_create(mbox);
        lv_label_set_text_fmt(label, "Do you want to delete '%s'?", sel_fn);
        lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 10);

        // Create "Yes" and "No" buttons
        lv_obj_t * yes_btn = lv_btn_create(mbox);
        lv_obj_set_size(yes_btn, 60, 30);
        lv_obj_align(yes_btn, LV_ALIGN_BOTTOM_LEFT, 20, -10);
        lv_obj_t * yes_label = lv_label_create(yes_btn);
        lv_label_set_text(yes_label, "Yes");

        lv_obj_t * no_btn = lv_btn_create(mbox);
        lv_obj_set_size(no_btn, 60, 30);
        lv_obj_align(no_btn, LV_ALIGN_BOTTOM_RIGHT, -20, -10);
        lv_obj_t * no_label = lv_label_create(no_btn);
        lv_label_set_text(no_label, "No");

        // Store "Yes" and "No" buttons as user data in the message box
        lv_obj_set_user_data(mbox, yes_btn);  // Store yes_btn pointer in message box
        lv_obj_add_event_cb(yes_btn, EVENTS::confirm_delete_event_handler, LV_EVENT_CLICKED, mbox);
        lv_obj_add_event_cb(no_btn, EVENTS::confirm_delete_event_handler, LV_EVENT_CLICKED, mbox);
    }
}

