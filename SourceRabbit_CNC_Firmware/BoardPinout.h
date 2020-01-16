///////////////////////////////////////////////////////////////////////////////////////////
// The following pins are for MKS GEN V1.4 Board
///////////////////////////////////////////////////////////////////////////////////////////
// NOTICE ARDUINO MEGA External Interrupt pins: 2,3,18,19,20,21

#define STEPPER_X_STEP_PIN 54
#define STEPPER_X_DIR_PIN 55
#define STEPPER_X_ENABLE_PIN 38

#define STEPPER_Y_STEP_PIN 60
#define STEPPER_Y_DIR_PIN 61
#define STEPPER_Y_ENABLE_PIN 56

#define STEPPER_Z_STEP_PIN 46
#define STEPPER_Z_DIR_PIN 48
#define STEPPER_Z_ENABLE_PIN 62

#define STEPPER_A_STEP_PIN 26   // Stepper A STEP Pin is the Extruder0 DIR pin on Ramps 1.4 board
#define STEPPER_A_DIR_PIN 28    // Stepper A DIR Pin is the Extruder0 DIR pin on Ramps 1.4 board
#define STEPPER_A_ENABLE_PIN 24 // Stepper A ENABLE Pin is the Extruder0 ENABLE on in Ramps 1.4 board

#define LIMIT_SWITCHES_PIN 3 // Limit switches are connected in series in Pin 3. Limit switches are NC (Normaly Closed) . Pin 3 is X- Limit pin on Ramps 1.4 board

#define FAN_PIN 9

#define HEATER_0_PIN 10
#define HEATER_1_PIN 8
#define TEMP_0_PIN 13 // ANALOG NUMBERING
#define TEMP_1_PIN 14 // ANALOG NUMBERING
#define TEMP_2_PIN 15 // ANALOG NUMBERING

/*
// RAMPS 1.4 Pin assignments
// Taken from Marlin pins.h (BOARD_RAMPS_13_EFF) and http://reprap.org/wiki/RAMPS_1.4
#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#define X_MIN_PIN           3
#define X_MAX_PIN           2

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19

#define E0_STEP_PIN        26
#define E0_DIR_PIN         28
#define E0_ENABLE_PIN      24

#define E1_STEP_PIN        36
#define E1_DIR_PIN         34
#define E1_ENABLE_PIN      30

#define SDPOWER            -1
#define SDSS               53
#define LED_PIN            13

#define FAN_PIN             9

#define PS_ON_PIN          12
#define KILL_PIN           -1

#define HEATER_0_PIN       10
#define HEATER_1_PIN        8
#define TEMP_0_PIN         13   // ANALOG NUMBERING
#define TEMP_1_PIN         14   // ANALOG NUMBERING
#define TEMP_2_PIN         15   // ANALOG NUMBERING
*/
