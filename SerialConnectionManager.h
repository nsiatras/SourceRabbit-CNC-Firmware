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
class SerialConnectionManager : public Manager
{
private:
    String fMessage;                                              // A temporary variable to keep last full/clear message
    char fIncomingBuffer[SERIAL_CONNECTION_INCOMING_BUFFER_SIZE]; // The buffer to collect incoming data
    uint8_t fBufferIndex;                                         // The incoming data buffer index
public:
    void Initialize();
    void ReadAvailableDataInSerial();
    void (*fOnMessageReceivedFromSerialConnectionCall)(String);
};

void SerialConnectionManager::Initialize()
{
    // Call the parent Initialize
    Manager::Initialize();

    Serial.begin(SERIAL_CONNECTION_BAUD_RATE);
    Serial.println("GRBL 1.1");

    fMessage = "";
    for (uint8_t i = 0; i < SERIAL_CONNECTION_INCOMING_BUFFER_SIZE; i++)
    {
        fIncomingBuffer[i] = 0;
    }
    fBufferIndex = 0;
}

void SerialConnectionManager::ReadAvailableDataInSerial()
{
    if (Serial.available() > 0)
    {
        // Read the available byte
        uint8_t receivedByte = Serial.read();

        switch (receivedByte)
        {
        case SERIAL_CONNECTION_MESSAGE_SPLIT_CHARACTER:
            // Get full/clear message
            fMessage = "";
            for (uint8_t i = 0; i < fBufferIndex; i++)
            {
                fMessage = fMessage + fIncomingBuffer[i];
            }
            fBufferIndex = 0;
            fOnMessageReceivedFromSerialConnectionCall(fMessage);
            break;

        default:
            fIncomingBuffer[fBufferIndex] = receivedByte;
            fBufferIndex++;
            break;
        }
    }
}
