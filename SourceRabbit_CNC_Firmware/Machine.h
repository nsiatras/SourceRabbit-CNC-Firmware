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
#ifndef MACHINE_H
#define MACHINE_H

#include "EMachineStatus.h"

class Machine
{
private:
    EMachineStatus fCurrentMachineStatus;

    float fMachineXPosition = 0, fMachineYPosition = 0, fMachineZPosition = 0, fMachineAPosition = 0;
    float fWorkXPosition = 0, fWorkYPosition = 0, fWorkZPosition = 0, fWorkAPosition = 0;

public:
    void Initialize();
    static Machine ACTIVE_INSTANCE; // Create a static Active Instance for the Machine

    void SendStatusReportToPCClient();

    void StartHomingSequence();
    void HomeXAxis();
    void HomeYAxis();
    void HomeZAxis();

    String getCurrentStatusInStringFormat();
    String getMachinePositionStatusString();
};

Machine Machine::ACTIVE_INSTANCE; // Declare the static ACTIVE_INSTANCE

// Initialize Limit Switches Manager
void Machine::Initialize()
{
    if (ENABLE_LIMIT_SWITCHES == 1)
    {
        // The machine has just been initialized and has Limit Switches Enabled
        // Set the machine into alarm status until the user homes the machine
        fCurrentMachineStatus = MACHINESTATUS_ALARM;
    }
    else
    {
        // The machine has just been initialized and has Limit Switches disabled
        // Set the machine status to idle
        fCurrentMachineStatus = MACHINESTATUS_IDLE;
    }
}

void Machine::StartHomingSequence()
{
#ifdef SHOW_DEBUG_MESSAGES
    Serial.println("DEBUG:Machine::StartHomingSequence");
#endif
    // HOME THE MACHINE

    // Set machine status to homing
    fCurrentMachineStatus = MACHINESTATUS_HOMING;

    // First Home the Z Axis
    HomeZAxis();
    HomeXAxis();
    HomeYAxis();

    fWorkXPosition = 0;
    fWorkYPosition = 0;
    fWorkZPosition = 0;

    // Homing sequence finished!
    // Set machine status to idle and
    // ask the Status Report Manager to send a new status report to the pc client
    fCurrentMachineStatus = MACHINESTATUS_IDLE;
}

void Machine::HomeXAxis()
{
    // Ask the Stepper Motor Manager to Home the X Axis
    StepperMotorManager::ACTIVE_INSTANCE.HomeXAxis();

#ifdef HOME_X_TO_MAX
    fMachineXPosition = MAX_X_TRAVEL * -1;
#else
    fMachineXPosition = 0;
#endif
}

void Machine::HomeYAxis()
{
    // Ask the Stepper Motor Manager to Home the Y Axis
    StepperMotorManager::ACTIVE_INSTANCE.HomeYAxis();

#ifdef HOME_Y_TO_MAX
    fMachineYPosition = MAX_Y_TRAVEL * -1;
#else
    fMachineYPosition = 0;
#endif
}

void Machine::HomeZAxis()
{
    // Ask the Stepper Motor Manager to Home the X Axis
    StepperMotorManager::ACTIVE_INSTANCE.HomeZAxis();

#ifdef HOME_Z_TO_MAX
    fMachineZPosition = MAX_Z_TRAVEL * -1;
#else
    fMachineZPosition = 0;
#endif
}

String Machine::getCurrentStatusInStringFormat()
{
    switch (fCurrentMachineStatus)
    {
    case MACHINESTATUS_IDLE:
        return "idle";

    case MACHINESTATUS_RUN:
        return "run";

    case MACHINESTATUS_HOLD:
        return "hold";

    case MACHINESTATUS_JOG:
        return "jog";

    case MACHINESTATUS_HOMING:
        return "homing";

    case MACHINESTATUS_ALARM:
        return "alarm";
    }
}

String Machine::getMachinePositionStatusString()
{
    String result = "";
    result += String(fMachineXPosition) + "," + String(fMachineYPosition) + "," + String(fMachineZPosition) + "," + String(fMachineAPosition);
    result += "|";
    result += String(fWorkXPosition) + "," + String(fWorkYPosition) + "," + String(fWorkZPosition) + "," + String(fWorkAPosition);
    return result;
}

void Machine::SendStatusReportToPCClient()
{
    // Generate the status report string
    // And send it to the PC Client
    // Notice: The status report string is like the following
    // Example: <idle|0.000,0.000,0.000,0.000|0.000,0.000,0.000,,0.000|L|P>
    String result = "<";

    // Step 1. Get status
    result += getCurrentStatusInStringFormat() + "|";

    // Step 2. Get machine coordinates
    result += getMachinePositionStatusString();

    // Step 3. Limit Switches status
    if (LimitSwitchesManager::ACTIVE_INSTANCE.fIsEnstopsTriggered)
    {
        result += "|L";
    }

    // Send status report string through serial
    result += ">";
    Serial.println(result);
}

#endif