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

#define MAX_POSITION true
#define MIN_POSITION false

struct PinInfo
{
    volatile uint8_t *PortOutputRegister;
    volatile uint8_t *PortInputRegister;
    uint8_t BITMASK;
    uint8_t PORT;
};

PinInfo fArduinoMegaPinsMatrix[78]; // Arduino Mega Pins

void InitializeCore()
{
    for (uint8_t i = 0; i < 78; i++)
    {
        uint8_t bit = digitalPinToBitMask(i);
        uint8_t port = digitalPinToPort(i);

        volatile uint8_t *out;
        out = portOutputRegister(port);

        if (digitalPinToPort(i) != NOT_A_PIN)
        {
            fArduinoMegaPinsMatrix[i] = {out, portInputRegister(port), bit, port};
        }
    }
}

// CAUTION: This method bypasses the arduino's digitalRead method
// Return's true if a pin is HIGH otherwise it returns false
bool isPinHigh(uint8_t arduinoPinNo)
{
    return !(*fArduinoMegaPinsMatrix[arduinoPinNo].PortInputRegister & fArduinoMegaPinsMatrix[arduinoPinNo].BITMASK);
}

// CAUTION: This method bypasses the arduino's digitalWrite method
void FastDigitalWrite(uint8_t arduinoPinNo, int value)
{
    if (value == LOW)
    {
        *(fArduinoMegaPinsMatrix[arduinoPinNo].PortOutputRegister) &= ~fArduinoMegaPinsMatrix[arduinoPinNo].BITMASK;
    }
    else
    {
        *(fArduinoMegaPinsMatrix[arduinoPinNo].PortOutputRegister) |= fArduinoMegaPinsMatrix[arduinoPinNo].BITMASK;
    }
}

#endif
