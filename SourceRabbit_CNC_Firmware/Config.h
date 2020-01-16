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
#define SHOW_DEBUG_MESSAGES

// This message is sent from the control board to the PC client
// from the SerialConnectionManager after the Serial connection established
#define WELCOME_MESSAGE "SourceRabbit CNC Firmware 1.1"

// Serial Connection Parameters
#define SERIAL_CONNECTION_BAUD_RATE 115200           // The baudrate of the serial connection
#define SERIAL_CONNECTION_INCOMING_BUFFER_SIZE 128   // The size of the incoming buffer in bytes
#define SERIAL_CONNECTION_MESSAGE_SPLIT_CHARACTER 10 // Character /n

#define MAX_X_TRAVEL 300
#define MAX_Y_TRAVEL 200
#define MAX_Z_TRAVEL 180

#define STEPPERS_MIN_PULSE_WIDTH_MICROSECONDS 20 // Microseconds

#define STEPPER_X_STEPS_PER_MM 200  // Steps / mm
#define STEPPER_X_ACCELERATION 40   //mm/sec^2
#define STEPPER_X_MAX_VELOCITY 1500 // mm/min

#define STEPPER_Y_STEPS_PER_MM 200  // Steps / mm
#define STEPPER_Y_ACCELERATION 40   //mm/sec^2
#define STEPPER_Y_MAX_VELOCITY 1500 // mm/min

#define STEPPER_Z_STEPS_PER_MM 200  // Steps / mm
#define STEPPER_Z_ACCELERATION 40   //mm/sec^2
#define STEPPER_Z_MAX_VELOCITY 1500 // mm/min

#define STEPPER_A_STEPS_PER_MM 200  // Steps / mm
#define STEPPER_A_ACCELERATION 40   //mm/sec^2
#define STEPPER_A_MAX_VELOCITY 1500 // mm/min

#define STEPPERS_ALWAYS_ENABLED 1 // Set to 1 if you want steppers to be always enabled

// Limit switches
// To enable the use of Limit Switches set the ENABLE_LIMIT_SWITCHES to 1
// For Normally Closed limit switches (NC) set the ENABLE_LIMIT_SWITCHES to 1
// For Normally Open (NO) limit switches set the ENABLE_LIMIT_SWITCHES to 0
// Notice: After setting ENABLE_LIMIT_SWITCHES to 1 the machine
// will require a homing cycle to get into idle status
#define ENABLE_LIMIT_SWITCHES 1
#define LIMIT_SWITCHES_ARE_NC 0

// Homing directions
//#define HOME_X_TO_MAX ;   // Uncomment to home X Axis to Max
#define HOME_X_TO_MIN ; // Uncomment to home X Axis to 0
//#define HOME_Y_TO_MAX ;   // Uncomment to home Y Axis to Max
#define HOME_Y_TO_MIN ; // Uncomment to home X Axis to 0
#define HOME_Z_TO_MAX ; // Uncomment to home Z Axis to Max
//#define HOME_Z_TO_MIN;    // Uncomment to home X Axis to 0
