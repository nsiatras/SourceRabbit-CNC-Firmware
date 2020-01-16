/*
Copyright 2020 NIKOLAOS SIATRAS

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
class LimitSwitchesManager : public Manager
{

public:
    void Initialize();
    static LimitSwitchesManager ACTIVE_INSTANCE; // Create a static Active Instance for the Limit Switches Manager
    static void LimitSwitchStatusChanged();      // THIS HAS TO BE STATIC because it is using an attachInterrupt
    static void LimitSwitchTriggered();          // THIS HAS TO BE STATIC because it is used from LimitSwitchStatusChanged
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

    // Initialize the static ACTIVE_INSTANCE of the LimitSwitchesManager
    LimitSwitchesManager::ACTIVE_INSTANCE = *this;
}

// This method is called from the interrupt when the status of the limit switches pin is LimitSwitchStatusChanged
void LimitSwitchesManager::LimitSwitchStatusChanged()
{
    // Get the value of the pin and check if the LimitSwitchesManager_LimitSwitchTriggered
    // must be called.
    int val = digitalRead(LIMIT_SWITCHES_PIN);

    if (LIMIT_SWITCHES_ARE_NC == 1 && val == 1)
    {
        // Limit switches are in NC Mode
        // Call the FireOnLimitSwitchTrigger method
        LimitSwitchesManager::ACTIVE_INSTANCE.FireOnLimitSwitchTrigger();
    }
    else if (LIMIT_SWITCHES_ARE_NC == 0 && val == 0)
    {
        // Limit switches are in NO Mode
        // Call the FireOnLimitSwitchTrigger method
        LimitSwitchesManager::ACTIVE_INSTANCE.FireOnLimitSwitchTrigger();
    }
}