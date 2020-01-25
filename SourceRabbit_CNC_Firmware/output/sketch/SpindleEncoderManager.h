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
#ifndef SPINDLEENCODERMANAGER_H
#define SPINDLEENCODERMANAGER_H
class SpindleEncoderManager : public Manager
{

public:
    void Initialize() override;
    void Reset() override;
    static SpindleEncoderManager ACTIVE_INSTANCE; // Create a static Active Instance for the Spindle Encoder Manager
    static void EncoderTicked();                  // THIS HAS TO BE STATIC because it is used from an attachInterrupt
};

SpindleEncoderManager SpindleEncoderManager::ACTIVE_INSTANCE; // Declare the static ACTIVE_INSTANCE

// Initialize Limit Switches Manager
void SpindleEncoderManager::Initialize()
{
    // Call the parent Initialize
    Manager::Initialize();

#ifdef ENABLE_SPINDLE_ENCODER
    pinMode(SPINDLE_ENCODER_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(SPINDLE_ENCODER_PIN), EncoderTicked, FALLING);
#endif
}

// Reset the Spindle Encoder Manager
void SpindleEncoderManager::Reset()
{
    Manager::Reset();
    SpindleEncoderManager::ACTIVE_INSTANCE.Initialize();
}

// This method is called from the interrupt when
// the status encoder pin changes to HIGH
void SpindleEncoderManager::EncoderTicked()
{
#ifdef SHOW_DEBUG_MESSAGES
    Serial.println("DEBUG:SpindleEncoderManager::EncoderTicked");
#endif
}

#endif