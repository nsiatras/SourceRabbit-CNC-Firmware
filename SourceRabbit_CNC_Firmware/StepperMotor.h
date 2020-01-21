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
class StepperMotor
{
private:
  uint8_t fPinStep, fPinDir, fEnablePin;
  uint8_t fPinStep_BitMask, fPinDir_BitMask, fEnablePin_BitMask;
  uint8_t fPinStep_Port, fPinDir_Port, fEnablePin_Port;
  uint8_t fPinStep_Port_Ouput_Register, fPinDir_Port_Ouput_Register, fEnablePin_Port_Ouput_Register;
  int fStepsPerMM, fMaxVelocity;

  volatile uint8_t *fPinStepOutputRegister;
  float fAcceleration;

public:
  StepperMotor();
  void Initialize(byte, byte, byte, int, int, int);

  void Step(int dir);
};

StepperMotor::StepperMotor()
{
}

// Initialize Stepper Manager
/*
 *
 * pinStep is the stepper step pin on the board
 * pinDir is the stepper dir pin on the board
 * enablePin is the stepper enable pin on the board
 * acceleration is acelleration in mm/sec^2
 * max velocity is the stepper's maximum velocity in mm/min
 * 
 * */
void StepperMotor::Initialize(uint8_t pinStep, uint8_t pinDir, uint8_t enablePin, int stepsPerMM, int acceleration, int maxVelocity_mm_per_min)
{
  fPinStep = pinStep;
  fPinDir = pinDir;
  fEnablePin = enablePin;
  fStepsPerMM = stepsPerMM;
  fAcceleration = acceleration / (60 ^ 2);
  fMaxVelocity = maxVelocity_mm_per_min;

  fPinStep_BitMask = ARDUINO_PIN_TO_BITMASK_MATRIX[fPinStep];
  fPinDir_BitMask = ARDUINO_PIN_TO_BITMASK_MATRIX[pinDir];
  fEnablePin_BitMask = ARDUINO_PIN_TO_BITMASK_MATRIX[enablePin];

  fPinStep_Port = ARDUINO_PIN_TO_PORT_MATRIX[fPinStep];
  fPinDir_Port = ARDUINO_PIN_TO_PORT_MATRIX[pinDir];
  fEnablePin_Port = ARDUINO_PIN_TO_PORT_MATRIX[enablePin];

  fPinStep_Port_Ouput_Register = ARDUINO_PIN_TO_PORT_OUTPUT_REGISTER[fPinStep];
  fPinDir_Port_Ouput_Register = ARDUINO_PIN_TO_PORT_OUTPUT_REGISTER[pinDir];
  fEnablePin_Port_Ouput_Register = ARDUINO_PIN_TO_PORT_OUTPUT_REGISTER[enablePin];

#ifdef STEPPERS_ALWAYS_ENABLED
  FastDigitalWrite(fEnablePin_Port_Ouput_Register, fEnablePin_BitMask, HIGH);
#endif
}

void StepperMotor::Step(int dir)
{
#ifndef STEPPERS_ALWAYS_ENABLED
  FastDigitalWrite(fEnablePin_Port_Ouput_Register, fEnablePin_BitMask, HIGH);
#endif

  // Set direction (DIR pin)
  FastDigitalWrite(fPinDir_Port_Ouput_Register, fPinDir_BitMask, dir);

  // HIGH Step Port
  FastDigitalWrite(fPinStep_Port_Ouput_Register, fPinStep_BitMask, HIGH);

  // Delay
  delayMicroseconds(STEPPERS_MIN_PULSE_WIDTH_MICROSECONDS);

  // LOW Step Port
  FastDigitalWrite(fPinStep_Port_Ouput_Register, fPinStep_BitMask, LOW);

  // Delay
  delayMicroseconds(STEPPERS_MIN_PULSE_WIDTH_MICROSECONDS);
}
