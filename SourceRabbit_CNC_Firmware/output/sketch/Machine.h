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
    void Reset();
    static Machine ACTIVE_INSTANCE; // Create a static Active Instance for the Machine

    String getMachineStatusReportString();

    void StartHomingSequence();
    void HomeAxis(int axis);
    void MoveAxisToHomePosition(int axis);

    String getCurrentStatusInStringFormat();
    String getMachinePositionStatusString();
};

Machine Machine::ACTIVE_INSTANCE; // Declare the static ACTIVE_INSTANCE

// Initialize Limit Switches Manager
void Machine::Initialize()
{
#ifdef ENABLE_LIMIT_SWITCHES
    // The machine has just been initialized and has Limit Switches Enabled
    // Set the machine into alarm status until the user homes the machine
    fCurrentMachineStatus = MACHINESTATUS_ALARM;
#else
    // The machine has just been initialized and has Limit Switches disabled
    // Set the machine status to idle
    fCurrentMachineStatus = MACHINESTATUS_IDLE;
#endif
}

void Machine::StartHomingSequence()
{
    // HOME THE MACHINE

    // Set machine status to homing
    fCurrentMachineStatus = MACHINESTATUS_HOMING;

    // Home the 3 axis
    HomeAxis(Z_AXIS); // First home the Z Axis
    HomeAxis(X_AXIS);
    HomeAxis(Y_AXIS);

    fWorkXPosition = 0;
    fWorkYPosition = 0;
    fWorkZPosition = 0;

    // Homing sequence finished!
    // Set machine status to idle !
    fCurrentMachineStatus = MACHINESTATUS_IDLE;
}

void Machine::HomeAxis(int axis)
{
    // Call the StepperMotorManager::ACTIVE_INSTANCE.MoveAxisToHomePosition for the given axis
    StepperMotorManager::ACTIVE_INSTANCE.MoveAxisToHomePosition(axis);

    switch (axis)
    {
    case X_AXIS:
        fMachineXPosition = (HOME_X_DIRECTION == MAX_POSITION) ? MAX_X_TRAVEL * -1 : 0;
        break;

    case Y_AXIS:
        fMachineYPosition = (HOME_Y_DIRECTION == MAX_POSITION) ? MAX_Y_TRAVEL * -1 : 0;
        break;

    case Z_AXIS:
        fMachineZPosition = (HOME_Z_DIRECTION == MAX_POSITION) ? MAX_Z_TRAVEL * -1 : 0;
        break;
    }
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

// Generate the status report string
// Notice: The status report string is like the following
// Example: <idle|0.000,0.000,0.000,0.000|0.000,0.000,0.000,0.000|LP>
// L is the limit Switches
// P is the Touch Probe
String Machine::getMachineStatusReportString()
{
    String result = "<";

    // Step 1. Get machine stats status (idle,jog,alarm etc..)
    result += getCurrentStatusInStringFormat() + "|";

    // Step 2. Get machine coordinates
    result += getMachinePositionStatusString() + "|";

    // Step 3. Limit Switches status
    if (LimitSwitchesManager::ACTIVE_INSTANCE.fEndstopIsTriggered)
    {
        result += "L";
    }

    // Step 4. Touch Probe status
    if (TouchProbeManager::ACTIVE_INSTANCE.fIsTouchProbeTriggered)
    {
        result += "P";
    }

    // Send status report string through serial
    result += ">";
    return result;
}

// The Machine::Reset method must reset all managers
// and set the machine status to alarm
void Machine::Reset()
{
    // Reset all managers
    StepperMotorManager::ACTIVE_INSTANCE.Reset();
    LimitSwitchesManager::ACTIVE_INSTANCE.Reset();
    SpindleEncoderManager::ACTIVE_INSTANCE.Reset();
    TouchProbeManager::ACTIVE_INSTANCE.Reset();

    // Always set the machine status to alarm after a reset
    fCurrentMachineStatus = MACHINESTATUS_ALARM;
}

#endif