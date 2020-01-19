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

int8_t ARDUINO_PIN_TO_BITMASK_MATRIX[54];
uint8_t ARDUINO_PIN_TO_PORT_MATRIX[54];

void InitializeCore()
{
    for (int8_t i = 0; i < 54; i++)
    {
        ARDUINO_PIN_TO_BITMASK_MATRIX[i] = digitalPinToBitMask(i);
    }

    for (uint8_t i = 0; i < 54; i++)
    {
        ARDUINO_PIN_TO_PORT_MATRIX[i] = digitalPinToPort(i);
    }
}

// CAUTION: This method bypasses the arduino's digitalRead method
// Return's true if a pin is HIGH otherwise it returns false
bool isPinHigh(uint8_t arduinoPinNo)
{
    return !(*portInputRegister(ARDUINO_PIN_TO_PORT_MATRIX[arduinoPinNo]) & ARDUINO_PIN_TO_BITMASK_MATRIX[arduinoPinNo]);
}
