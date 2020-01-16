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
#include "EMachineStatus.h"
#include "Events.h"
#include "Manager.h"
#include "SerialConnectionManager.h"
#include "LimitSwitchesManager.h"
#include "StepperMotorManager.h"
#include "MotionController.h"

// MACHINE ALWAYS AT THE END
#include "Machine.h"

SerialConnectionManager *fSerialConnectionManager;

void setup()
{
    // Initialize Serial Communication Manager
    fSerialConnectionManager = new SerialConnectionManager();
    fSerialConnectionManager->fOnMessageReceivedFromSerialConnectionCall = OnMessageReceivedFromSerialConnection;
    fSerialConnectionManager->Initialize();

    // Initialize Stepper Motor Manager
    StepperMotorManager::ACTIVE_INSTANCE.fEventHandlerVoid = EventHandler;
    StepperMotorManager::ACTIVE_INSTANCE.Initialize();

    // Initialize Limit Switch Manager
    LimitSwitchesManager::ACTIVE_INSTANCE.fEventHandlerVoid = EventHandler;
    LimitSwitchesManager::ACTIVE_INSTANCE.Initialize();

    // Initialize the Machine
    Machine::ACTIVE_INSTANCE.Initialize();

    // EVERYTHING IS INITIALIZED
    // Send the welcome message to the PC Client
    Serial.println(WELCOME_MESSAGE);
}

void loop()
{
    fSerialConnectionManager->ReadAvailableDataInSerial();
}

// All incoming messages from the serial connection passes
// through here
void OnMessageReceivedFromSerialConnection(String message)
{
    if (message == "?")
    {
        // Ask Machine to send a status report to the PC Client
        Machine::ACTIVE_INSTANCE.SendStatusReportToPCClient();
    }
    else if (message == "$H")
    {
        // Home the machine
        Machine::ACTIVE_INSTANCE.StartHomingSequence();
    }
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
        StepperMotorManager::ACTIVE_INSTANCE.OnLimitSwitchTrigger_EventHandler();
        LimitSwitchesManager::ACTIVE_INSTANCE.OnLimitSwitchTrigger_EventHandler();
        break;

    case EVENT_TOUCH_PROBE_TOUCH:
        // Touch probe has been touched
        // This event comes from the Touch Probe Manager
        // INFORM ALL MANAGERS ABOUT IT
        StepperMotorManager::ACTIVE_INSTANCE.OnTouchProbeTouch_EventHandler();
        LimitSwitchesManager::ACTIVE_INSTANCE.OnTouchProbeTouch_EventHandler();
        break;
    }
}