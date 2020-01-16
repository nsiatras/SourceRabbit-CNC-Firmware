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
#ifndef STATUSREPORTMANAGER_H
#define STATUSREPORTMANAGER_H
class StatusReportManager : public Manager
{

public:
    void Initialize();
    static StatusReportManager ACTIVE_INSTANCE; // Create a static Active Instance for the StatusReportManager

    void SendStatusReportToPCClient();
};

StatusReportManager StatusReportManager::ACTIVE_INSTANCE; // Declare the static ACTIVE_INSTANCE

// Initialize Limit Switches Manager
void StatusReportManager::Initialize()
{
    // Call the parent Initialize
    Manager::Initialize();
}

void StatusReportManager::SendStatusReportToPCClient()
{
    // Generate the status report string
    // And send it to the PC Client
    // Notice: The status report string is identical to GRBL v1.1
    // Example: <Idle|MPos:0.000,0.000,0.000|FS:0,0|WCO:0.000,0.000,0.000>

    String result = "<";

    // Step 1. Get machine status
    result += Machine::ACTIVE_INSTANCE.getCurrentStatusInStringFormat() + "|";

    // Step 2. Get machine coordinates
    result += Machine::ACTIVE_INSTANCE.getMachinePositionStatusString();

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