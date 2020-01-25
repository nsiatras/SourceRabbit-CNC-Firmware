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
#include <AccelStepper.h>
#include <MultiStepper.h>
#include "BoardPinout.h"
#include "Core.h"
#include "Config.h"
#include "EError.h"
#include "EMachineStatus.h"
#include "ECommands.h"
#include "EAxis.h"
#include "Events.h"
#include "Manager.h"
#include "SerialConnectionManager.h"
#include "LimitSwitchesManager.h"
#include "TouchProbeManager.h"
#include "StepperMotorManager.h"
#include "MotionController.h"
#include "SpindleEncoderManager.h"

// MACHINE ALWAYS AT THE END
#include "Machine.h"

void setup()
{
    // Initialize core always at the start of the  Setup() method
    InitializeCore();

    // Initialize Serial Communication Manager
    SerialConnectionManager::ACTIVE_INSTANCE.fOnMessageReceivedFromSerialConnectionCall = ParseReceivedMessageFromSerialConnection;
    SerialConnectionManager::ACTIVE_INSTANCE.Initialize();

    // Initialize Stepper Motor Manager
    StepperMotorManager::ACTIVE_INSTANCE.fEventHandlerVoid = EventHandler;
    StepperMotorManager::ACTIVE_INSTANCE.Initialize();

    // Initialize Limit Switch Manager
    LimitSwitchesManager::ACTIVE_INSTANCE.fEventHandlerVoid = EventHandler;
    LimitSwitchesManager::ACTIVE_INSTANCE.Initialize();

    // Initialize Spindle Encoder Manager
    SpindleEncoderManager::ACTIVE_INSTANCE.fEventHandlerVoid = EventHandler;
    SpindleEncoderManager::ACTIVE_INSTANCE.Initialize();

    // Initialize Touch Probe Manager
    TouchProbeManager::ACTIVE_INSTANCE.fEventHandlerVoid = EventHandler;
    TouchProbeManager::ACTIVE_INSTANCE.Initialize();

    // Initialize the Machine
    Machine::ACTIVE_INSTANCE.Initialize();

    // EVERYTHING IS INITIALIZED
    // Send the welcome message to the PC Client
    SerialConnectionManager::ACTIVE_INSTANCE.SendData(WELCOME_MESSAGE);
}

void loop()
{
    ParseReceivedMessageFromSerialConnection(SerialConnectionManager::ACTIVE_INSTANCE.getFirstIncomingMessageFromQueue());

    delay(1000);
    //StepperMotorManager::ACTIVE_INSTANCE.MoveStepper(AXIS_X, 100, 1500);
    delay(2000);
    //StepperMotorManager::ACTIVE_INSTANCE.MoveStepper(AXIS_X, -100, 1500);
    delay(2000);
}

// This is the asynchronous serial read
void serialEvent()
{
    SerialConnectionManager::ACTIVE_INSTANCE.ReadAllAvailableIncomingSerialData();
}

// All incoming messages from the serial connection passes through here
void ParseReceivedMessageFromSerialConnection(String message)
{
    if (message != "")
    {
        if (message == COMMAND_STATUS_REPORT)
        {
            // Get the status report string from Machine
            // and send it to the PC client
            SerialConnectionManager::ACTIVE_INSTANCE.SendData(Machine::ACTIVE_INSTANCE.getMachineStatusReportString());
        }
        else if (message == COMMAND_HOME_ALL_AXES)
        {
            // Home the machine
            Machine::ACTIVE_INSTANCE.StartHomingSequence();
            SerialConnectionManager::ACTIVE_INSTANCE.ReportOKForIncomingCommand();
            // Send a status report to the PC Client
            SerialConnectionManager::ACTIVE_INSTANCE.SendData(Machine::ACTIVE_INSTANCE.getMachineStatusReportString());
        }
        else if (message == COMMAND_RESET)
        {
            // RESET Machine and Send a status report to the PC Client
            Machine::ACTIVE_INSTANCE.Reset();
            SerialConnectionManager::ACTIVE_INSTANCE.SendData(Machine::ACTIVE_INSTANCE.getMachineStatusReportString());
        }
        else
        {
            // Send Unknown Command error to PC Client
            SerialConnectionManager::ACTIVE_INSTANCE.ReportErrorForIncomingCommand(ERROR_UNKOWN_COMMAND);
        }
    }
}

// This method is called only when a limit switch is triggered
void EventHandler(uint8_t eventID)
{
    switch (eventID)
    {
    case EVENT_LIMIT_SWITCH_ON:
        // A LIMIT SWITCH IS ON !
        // This event comes from the LimitSwitchesManager
        StepperMotorManager::ACTIVE_INSTANCE.OnLimitSwitchOn_EventHandler();
        break;

    case EVENT_LIMIT_SWITCH_OFF:
        // A LIMIT SWITCH IS OFF !
        // This event comes from the LimitSwitchesManager
        StepperMotorManager::ACTIVE_INSTANCE.OnLimitSwitchOff_EventHandler();
        break;

    case EVENT_TOUCH_PROBE_ON:
        // Touch probe has been touched
        // This event comes from the Touch Probe Manager
        StepperMotorManager::ACTIVE_INSTANCE.OnTouchProbeOn_EventHandler();
        break;

    case EVENT_TOUCH_PROBE_OFF:
        // Touch probe has been touched
        // This event comes from the Touch Probe Manager
        StepperMotorManager::ACTIVE_INSTANCE.OnTouchProbeOff_EventHandler();
        break;

    case EVENT_ERROR_SERIAL_BUFFER_OVVERRUN:
        StepperMotorManager::ACTIVE_INSTANCE.OnError_EventHandler(ERROR_SERIAL_BUFFER_OVVERRUN);
        break;
    }

#ifdef SHOW_DEBUG_MESSAGES
    Serial.println("DEBUG:EventHandler::" + getEventNameFromID(eventID));
#endif
}