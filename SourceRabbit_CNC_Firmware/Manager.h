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
#ifndef MANAGER_H
#define MANAGER_H

class Manager
{
private:
public:
    virtual void Initialize();

    // Events...
    void (*fEventHandlerVoid)(uint8_t);
    void FireEvent(uint8_t eventID);

    virtual void OnLimitSwitchTrigger_EventHandler();
    virtual void OnTouchProbeTouch_EventHandler();
};

void Manager::Initialize()
{
}

void Manager::OnLimitSwitchTrigger_EventHandler()
{
    // This method is virtual
    // No code required here
}

void Manager::OnTouchProbeTouch_EventHandler()
{
    // This method is virtual
    // No code required here
}

// Fire an eventID
// This will go to void EventHandler inside SourceRabbit_CNC_Firmware.ino
void Manager::FireEvent(uint8_t eventID)
{
    fEventHandlerVoid(eventID);
}

#endif
