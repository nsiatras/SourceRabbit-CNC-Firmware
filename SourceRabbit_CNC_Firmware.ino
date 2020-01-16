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
#include "Arduino.h"
#include "wiring_private.h"
#include "BoardPinout.h"
#include "Config.h"
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

    // Initialize Limit Switch Manager
    fLimitSwitchesManager = new LimitSwitchesManager();
    fLimitSwitchesManager->FireOnLimitSwitchTrigger = Handle_OnLimitSwitchTrigger;
    fLimitSwitchesManager->Initialize();

    // Initialize Stepper Motor Manager
    fStepperMotorManager = new StepperMotorManager();
    fStepperMotorManager->Initialize();
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
void Handle_OnLimitSwitchTrigger()
{
    // A LIMIT SWITCH HAS BEEN TRIGGERED!
}