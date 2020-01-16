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

#define SERIAL_CONNECTION_BAUD_RATE 115200
#define SERIAL_CONNECTION_INCOMING_BUFFER_SIZE 128   // The size of the incoming buffer in bytes
#define SERIAL_CONNECTION_MESSAGE_SPLIT_CHARACTER 10 // Character /n

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

#define ENABLE_LIMIT_SWITCHES 1 // If you have limit switches installed then set it to 1 otherwise set it to zero
#define LIMIT_SWITCHES_ARE_NC 0 // If limit switches are Normally Closed (NC) then set this to 1, otherwise set it to 0
