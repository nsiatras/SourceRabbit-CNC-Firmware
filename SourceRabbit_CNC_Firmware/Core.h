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

#ifndef CORE_H
#define CORE_H

// Axis array index values. Must start with 0 and be continuous.
#define N_AXIS 3 // Number of axes
#define X_AXIS 0 // Axis indexing value.
#define Y_AXIS 1
#define Z_AXIS 2
#define A_AXIS 3

#define MAX_POSITION true
#define MIN_POSITION false

int8_t ARDUINO_PIN_TO_BITMASK_MATRIX[78];
uint8_t ARDUINO_PIN_TO_PORT_MATRIX[78];
uint8_t ARDUINO_PIN_TO_PORT_OUTPUT_REGISTER[78];

void InitializeCore()
{
    for (uint8_t i = 0; i < 78; i++)
    {
        if (digitalPinToPort(i) != NOT_A_PIN)
        {
            ARDUINO_PIN_TO_PORT_MATRIX[i] = digitalPinToPort(i);
        }
        else
        {
            ARDUINO_PIN_TO_PORT_MATRIX[i] = NOT_A_PIN;
        }
    }

    for (int8_t i = 0; i < 78; i++)
    {
        if (ARDUINO_PIN_TO_PORT_MATRIX[i] != NOT_A_PIN)
        {
            ARDUINO_PIN_TO_BITMASK_MATRIX[i] = digitalPinToBitMask(i);
        }
    }

}

// CAUTION: This method bypasses the arduino's digitalRead method
// Return's true if a pin is HIGH otherwise it returns false
bool isPinHigh(uint8_t arduinoPinNo)
{
    return !(*portInputRegister(ARDUINO_PIN_TO_PORT_MATRIX[arduinoPinNo]) & ARDUINO_PIN_TO_BITMASK_MATRIX[arduinoPinNo]);
}

void FastDigitalWrite(uint8_t portOutputReg, uint8_t bit, uint8_t val)
{
    if (val == LOW)
    {
        portOutputReg &= ~bit;
    }
    else
    {
        portOutputReg |= bit;
    }
}

#endif
