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
class LimitSwitchesManager : public Manager
{

public:
    void Initialize();
    static LimitSwitchesManager ACTIVE_INSTANCE; // Create a static Active Instance for the Limit Switches Manager
    static void LimitSwitchStatusChanged();      // THIS HAS TO BE STATIC because it is using an attachInterrupt

    bool fIsEnstopsTriggered = false;
    // Limit Switches Manager Events
    void OnLimitSwitchTrigger_EventHandler();
};

LimitSwitchesManager LimitSwitchesManager::ACTIVE_INSTANCE; // Declare the static ACTIVE_INSTANCE

// Initialize Limit Switches Manager
void LimitSwitchesManager::Initialize()
{
    // Call the parent Initialize
    Manager::Initialize();

    if (ENABLE_LIMIT_SWITCHES == 1)
    {
        ////////////////////////////////////////////////////////////////////////////////////////////
        // Add an interrupt to the LIMIT_SWITCHES_PIN.
        // Every time a limit switch is triggered the interrupt will fire the STATIC void LimitSwitchStatusChanged
        pinMode(LIMIT_SWITCHES_PIN, INPUT_PULLUP);
        attachInterrupt(digitalPinToInterrupt(LIMIT_SWITCHES_PIN), LimitSwitchStatusChanged, CHANGE);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////
}

// This method is called from the interrupt when the status of the limit switches pin is LimitSwitchStatusChanged
void LimitSwitchesManager::LimitSwitchStatusChanged()
{
    // Get the value of the pin and check if the LimitSwitchesManager_LimitSwitchTriggered
    // must be called.
    int val = digitalRead(LIMIT_SWITCHES_PIN);

    if (LIMIT_SWITCHES_ARE_NC == 1 && val == 1)
    {
        LimitSwitchesManager::ACTIVE_INSTANCE.fIsEnstopsTriggered = true;
        // Limit switches are in NC Mode
        // Fire the EVENT_LIMIT_SWITCH_TRIGGERED
        LimitSwitchesManager::ACTIVE_INSTANCE.FireEvent(EVENT_LIMIT_SWITCH_TRIGGERED);
    }
    else if (LIMIT_SWITCHES_ARE_NC == 0 && val == 0)
    {
        LimitSwitchesManager::ACTIVE_INSTANCE.fIsEnstopsTriggered = true;
        // Limit switches are in NO Mode
        // Fire the EVENT_LIMIT_SWITCH_TRIGGERED
        LimitSwitchesManager::ACTIVE_INSTANCE.FireEvent(EVENT_LIMIT_SWITCH_TRIGGERED);
    }
    else
    {
        LimitSwitchesManager::ACTIVE_INSTANCE.fIsEnstopsTriggered = false;
    }
}

void LimitSwitchesManager::OnLimitSwitchTrigger_EventHandler()
{
#ifdef SHOW_DEBUG_MESSAGES
    Serial.println("DEBUG:LimitSwitchesManager::OnLimitSwitchTrigger_EventHandler");
#endif
}
#endif