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
#ifndef LIMITSWITCHESMANAGER_H
#define LIMITSWITCHESMANAGER_H

#include "Core.h"

class LimitSwitchesManager : public Manager
{

public:
    void Initialize() override;
    void Reset() override;
    static LimitSwitchesManager ACTIVE_INSTANCE; // Create a static Active Instance for the Limit Switches Manager
    static void LimitSwitchStatusChanged();      // THIS HAS TO BE STATIC because it is using an attachInterrupt

    bool fEndstopIsTriggered = true;
};

LimitSwitchesManager LimitSwitchesManager::ACTIVE_INSTANCE; // Declare the static ACTIVE_INSTANCE

// Initialize Limit Switches Manager
void LimitSwitchesManager::Initialize()
{
    // Call the parent Initialize
    Manager::Initialize();

#ifdef ENABLE_LIMIT_SWITCHES
    ////////////////////////////////////////////////////////////////////////////////////////////
    // Add an interrupt to the LIMIT_SWITCHES_PIN.
    // Every time a limit switch is triggered the interrupt will fire the STATIC void LimitSwitchStatusChanged
    pinMode(LIMIT_SWITCHES_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(LIMIT_SWITCHES_PIN), LimitSwitchStatusChanged, CHANGE);

    ////////////////////////////////////////////////////////////////////////////////////////////
    // After initialize check the limit switches one time to get
    // their initial status
    LimitSwitchesManager::LimitSwitchStatusChanged();
#endif
}

// Reset the Limit Switches Manager
void LimitSwitchesManager::Reset()
{
    Manager::Reset();
    LimitSwitchesManager::ACTIVE_INSTANCE.Initialize();
}

// This method is called from the interrupt when the status of the limit switches pin is LimitSwitchStatusChanged
void LimitSwitchesManager::LimitSwitchStatusChanged()
{
    // Check if the Limit Switches pin is High
    bool isLimitSwitchesPinHigh = isPinHigh(LIMIT_SWITCHES_PIN);

#ifdef LIMIT_SWITCHES_ARE_NO
    // LIMIT SWITCHES ARE NO (NORMALLY OPENED)
    LimitSwitchesManager::ACTIVE_INSTANCE.fEndstopIsTriggered = isLimitSwitchesPinHigh;
    LimitSwitchesManager::ACTIVE_INSTANCE.FireEvent(isLimitSwitchesPinHigh ? EVENT_LIMIT_SWITCH_ON : EVENT_LIMIT_SWITCH_OFF);
#else
    // LIMIT SWITCHES ARE NC (NORMALLY CLOSED)
    LimitSwitchesManager::ACTIVE_INSTANCE.fEndstopIsTriggered = !isLimitSwitchesPinHigh;
    LimitSwitchesManager::ACTIVE_INSTANCE.FireEvent(!isLimitSwitchesPinHigh ? EVENT_LIMIT_SWITCH_ON : EVENT_LIMIT_SWITCH_OFF);
#endif
}

#endif