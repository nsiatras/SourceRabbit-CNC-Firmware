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
#ifndef TOUCHPROBEMANAGER_H
#define TOUCHPROBEMANAGER_H

#include "Core.h"

class TouchProbeManager : public Manager
{

public:
    void Initialize() override;
    void Reset() override;
    static TouchProbeManager ACTIVE_INSTANCE; // Create a static Active Instance for the Limit Switches Manager
    static void TouchProbeStatusChanged();    // THIS HAS TO BE STATIC because it is using an attachInterrupt

    bool fIsTouchProbeTriggered = true;
};

TouchProbeManager TouchProbeManager::ACTIVE_INSTANCE; // Declare the static ACTIVE_INSTANCE

// Initialize Limit Switches Manager
void TouchProbeManager::Initialize()
{
    // Call the parent Initialize
    Manager::Initialize();

    ////////////////////////////////////////////////////////////////////////////////////////////
    // Add an interrupt to the LIMIT_SWITCHES_PIN.
    // Every time a limit switch is triggered the interrupt will fire the STATIC void LimitSwitchStatusChanged
    pinMode(TOUCH_PROBE_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(TOUCH_PROBE_PIN), TouchProbeStatusChanged, CHANGE);

    ////////////////////////////////////////////////////////////////////////////////////////////
    // After initialize check the limit switches one time to get
    // their initial status
    TouchProbeManager::TouchProbeStatusChanged();
}

// Reset the Touch Probe Manager
void TouchProbeManager::Reset()
{
    Manager::Reset();
    TouchProbeManager::ACTIVE_INSTANCE.Initialize();
}

void TouchProbeManager::TouchProbeStatusChanged()
{
    // Check if the Limit Switches pin is High
    bool isTouchProbePinHIGH = isPinHigh(TOUCH_PROBE_PIN);

#ifdef TOUCH_PROBE_IS_NO
    // TOUCH PROBE IS NO (NORMALLY OPENED)
    TouchProbeManager::ACTIVE_INSTANCE.fIsTouchProbeTriggered = isTouchProbePinHIGH;
    TouchProbeManager::ACTIVE_INSTANCE.FireEvent(isTouchProbePinHIGH ? EVENT_TOUCH_PROBE_ON : EVENT_TOUCH_PROBE_OFF);
#else
    // TOUCH PROBE IS NC (NORMALLY CLOSED)
    TouchProbeManager::ACTIVE_INSTANCE.fIsTouchProbeTriggered = !isTouchProbePinHIGH;
    TouchProbeManager::ACTIVE_INSTANCE.FireEvent(!isTouchProbePinHIGH ? EVENT_TOUCH_PROBE_ON : EVENT_TOUCH_PROBE_OFF);
#endif
}

#endif