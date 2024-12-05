#ifndef IR_H
#define IR_H

#include <stdint.h>

// IR TX and RX Pins
#define IR_TX 4        // The IR sender LED
#define IR_RX 34       // The IR receiver (if used)

// EU/NA region settings
#define EU 1  // Set by a HIGH on REGIONSWITCH pin
#define NA 0  // Set by a LOW on REGIONSWITCH pin

// Macro to calculate the size of the NA/EU databases
#define NUM_ELEM(x) (sizeof(x) / sizeof(*(x)))

// Debugging
#define DEBUG 0
#define DEBUGP(x) if (DEBUG == 1) { x ; }

// Frequency to timer value conversion (in milliseconds)
#define freq_to_timerval(x) (x / 1000)

// IR code structure definition
struct IrCode {
  uint8_t timer_val;
  uint8_t numpairs;
  uint8_t bitcompression;
  uint16_t const *times;
  uint8_t const *codes;
};

#endif // IR_H
