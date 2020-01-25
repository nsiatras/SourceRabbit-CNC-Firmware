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

#include "Queue.h"

class SerialConnectionManager : public Manager
{
private:
    char fIncomingBuffer[SERIAL_CONNECTION_INCOMING_BUFFER_SIZE]; // The buffer to collect incoming bytes
    uint8_t fIncomingBufferIndex;                                 // The incoming data buffer index

    String fTempMessage; // A temporary variable to keep last full/clear message
    Queue<String> *fIncomingMessagesQueue;

public:
    static SerialConnectionManager ACTIVE_INSTANCE; // Create a static Active Instance for the SerialConnectionManager
    void Initialize();

    void ReadAllAvailableIncomingSerialData();

    String getFirstIncomingMessageFromQueue();
    bool QueueHasIncomingMessages();

    void SendData(String dataToSend);
    void ReportOKForIncomingCommand();
    void ReportErrorForIncomingCommand(uint8_t errorID);
    void (*fOnMessageReceivedFromSerialConnectionCall)(String);
};

SerialConnectionManager SerialConnectionManager::ACTIVE_INSTANCE; // Declare the static ACTIVE_INSTANCE

void SerialConnectionManager::Initialize()
{
    // Call the parent Initialize
    Manager::Initialize();

    Serial.begin(SERIAL_CONNECTION_BAUD_RATE);

    fTempMessage = "";

    // Initialize fIncomingBuffer
    for (uint8_t i = 0; i < SERIAL_CONNECTION_INCOMING_BUFFER_SIZE; i++)
    {
        fIncomingBuffer[i] = 0;
    }
    fIncomingBufferIndex = 0;

    // Initialize fIncomingMessagesQueue
    fIncomingMessagesQueue = new Queue<String>(SERIAL_CONNECTION_MAX_INCOMING_MESSAGES_BUFFER);
}

void SerialConnectionManager::ReportOKForIncomingCommand()
{
    Serial.println("ok");
}

void SerialConnectionManager::SendData(String dataToSend)
{
    Serial.println(dataToSend);
}

void SerialConnectionManager::ReportErrorForIncomingCommand(uint8_t errorID)
{
    Serial.print("error:");
    Serial.println(errorID);
}

// This method returns the first incoming message
// from the fIncomingMessagesQueue;
String SerialConnectionManager::getFirstIncomingMessageFromQueue()
{
    if (fIncomingMessagesQueue->count() > 0)
    {
        return fIncomingMessagesQueue->pop();
    }
    return "";
}

bool SerialConnectionManager::QueueHasIncomingMessages()
{
    return fIncomingMessagesQueue->count() > 0;
}

void SerialConnectionManager::ReadAllAvailableIncomingSerialData()
{
    // Read incoming bytes until the buffer is full or until
    // a complete message is read
    while (Serial.available() && fIncomingBufferIndex < SERIAL_CONNECTION_INCOMING_BUFFER_SIZE && fIncomingMessagesQueue->count() < SERIAL_CONNECTION_MAX_INCOMING_MESSAGES_BUFFER)
    {
        uint8_t receivedByte = Serial.read();
        switch (receivedByte)
        {
        case SERIAL_CONNECTION_MESSAGE_SPLIT_CHARACTER:
            // Get full/clear message
            fTempMessage = "";
            for (uint8_t i = 0; i < fIncomingBufferIndex; i++)
            {
                fTempMessage = fTempMessage + fIncomingBuffer[i];
            }
            fIncomingBufferIndex = 0;

            fIncomingMessagesQueue->push(fTempMessage);
            break;

        default:
            fIncomingBuffer[fIncomingBufferIndex] = receivedByte;
            fIncomingBufferIndex++;
            break;
        }
    }

    if (fIncomingBufferIndex >= SERIAL_CONNECTION_INCOMING_BUFFER_SIZE)
    {
        // BUFFER OVERRUN !!!!
        fIncomingBufferIndex = 0;
        Serial.flush();
        FireEvent(EVENT_ERROR_SERIAL_BUFFER_OVVERRUN);
    }
}
