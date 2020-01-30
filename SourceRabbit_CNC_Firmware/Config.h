/*
MIT License

Copyright (c) 2020 Nikos Siatras

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

// To see debug messages through serial connection uncomment the following line
//#define SHOW_DEBUG_MESSAGES

// This message is sent from the control board to the PC client
// from the SerialConnectionManager after the Serial connection established
#ifndef CONFIG_H
#define CONFIG_H

#define WELCOME_MESSAGE "SourceRabbit CNC Firmware 1.1"

// Serial Connection Parameters
#define SERIAL_CONNECTION_BAUD_RATE 115200               // The baudrate of the serial connection
#define SERIAL_CONNECTION_INCOMING_BUFFER_SIZE 128       // The size of the incoming buffer in bytes
#define SERIAL_CONNECTION_MESSAGE_SPLIT_CHARACTER 10     // Character /n
#define SERIAL_CONNECTION_MAX_INCOMING_MESSAGES_BUFFER 8 // How many incoming messages to store in ram and wait for them to be processed

#define MAX_X_TRAVEL 300
#define MAX_Y_TRAVEL 200
#define MAX_Z_TRAVEL 180

#define STEPPERS_MIN_PULSE_WIDTH_MICROSECONDS 20 // Microseconds

#define STEPPER_X_STEPS_PER_MM 800  // Steps / mm
#define STEPPER_X_ACCELERATION 40   //mm/sec^2
#define STEPPER_X_MAX_FEEDRATE 4000 // mm/min

#define STEPPER_Y_STEPS_PER_MM 200  // Steps / mm
#define STEPPER_Y_ACCELERATION 40   //mm/sec^2
#define STEPPER_Y_MAX_FEEDRATE 4000 // mm/min

#define STEPPER_Z_STEPS_PER_MM 200  // Steps / mm
#define STEPPER_Z_ACCELERATION 40   //mm/sec^2
#define STEPPER_Z_MAX_FEEDRATE 4000 // mm/min

#define STEPPER_A_STEPS_PER_MM 200  // Steps / mm
#define STEPPER_A_ACCELERATION 40   //mm/sec^2
#define STEPPER_A_MAX_FEEDRATE 4000 // mm/min

#define STEPPERS_ALWAYS_ENABLED // Uncomment to set Steppers Always enabled

// Limit switches
// To enable the use of Limit Switches uncomment the '#define ENABLE_LIMIT_SWITCHES'
// For Normally Open (NO) limit switches uncomment the '#define LIMIT_SWITCHES_ARE_NO' line
// For Normally Closed (NC) limit switches uncomment the '#define LIMIT_SWITCHES_ARE_NC' line
// Notice: After defining ENABLE_LIMIT_SWITCHES the machine
// requires a homing cycle to get into idle status.
#define ENABLE_LIMIT_SWITCHES // Uncomment to enable the use of limit switches
//#define LIMIT_SWITCHES_ARE_NC
#define LIMIT_SWITCHES_ARE_NO

// Touch Probe
// For Normally Open (NO) Touch Probe uncomment the '#define TOUCH_PROBE_IS_NO' line
// For Normally Closed (NC) Touch Probe uncomment the '#define TOUCH_PROBE_IS_NC' line
#define TOUCH_PROBE_IS_NO
//#define TOUCH_PROBE_IS_NC

// Homing directions
// Set the following to 1 in order to home the axes to Max or
// set it to 0 in order to home the axes to Min.
#define HOME_X_DIRECTION MIN_POSITION
#define HOME_Y_DIRECTION MIN_POSITION
#define HOME_Z_DIRECTION MAX_POSITION

// Spindle Encoder (SUPPORT FOR SINGLE TICK ENCODERS)
// To enable the use of Spindle Encoder uncomment the following line
#define ENABLE_SPINDLE_ENCODER

#endif
