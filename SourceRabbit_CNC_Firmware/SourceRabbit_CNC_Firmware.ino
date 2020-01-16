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
#include "Arduino.h"
#include "BoardPinout.h"
#include "Config.h"
#include "Events.h"
#include "Manager.h"
#include "SerialConnectionManager.h"
#include "LimitSwitchesManager.h"
#include "StepperMotorManager.h"
#include "MotionController.h"

SerialConnectionManager *fSerialConnectionManager;
LimitSwitchesManager *fLimitSwitchesManager;
StepperMotorManager *fStepperMotorManager;

void setup()
{
    // Initialize Serial Communication Manager
    fSerialConnectionManager = new SerialConnectionManager();
    fSerialConnectionManager->fOnMessageReceivedFromSerialConnectionCall = OnMessageReceivedFromSerialConnection;
    fSerialConnectionManager->Initialize();

    // Initialize Stepper Motor Manager
    fStepperMotorManager = new StepperMotorManager();
    fStepperMotorManager->fEventHandlerVoid = EventHandler;
    fStepperMotorManager->Initialize();

    // Initialize Limit Switch Manager
    fLimitSwitchesManager = new LimitSwitchesManager();
    fLimitSwitchesManager->fEventHandlerVoid = EventHandler;
    fLimitSwitchesManager->Initialize();
}

void loop()
{
    fSerialConnectionManager->ReadAvailableDataInSerial();
}

// All incoming messages from the serial connection passes
// through here
void OnMessageReceivedFromSerialConnection(String message)
{
    Serial.println(message);
}

// This method is called only when a limit switch is triggered
void EventHandler(uint8_t eventID)
{
    switch (eventID)
    {
    case EVENT_LIMIT_SWITCH_TRIGGERED:
        // A LIMIT SWITCH HAS BEEN TRIGGERED!
        // This event comes from the LimitSwitchesManager
        // INFORM ALL MANAGERS ABOUT IT
        fStepperMotorManager->OnLimitSwitchTrigger_EventHandler();
        fLimitSwitchesManager->OnLimitSwitchTrigger_EventHandler();
        break;

    case EVENT_TOUCH_PROBE_TOUCH:
        // Touch probe has been touched
        // This event comes from the Touch Probe Manager
        // INFORM ALL MANAGERS ABOUT IT
        fStepperMotorManager->OnTouchProbeTouch_EventHandler();
        fLimitSwitchesManager->OnTouchProbeTouch_EventHandler();
        break;
    }
}