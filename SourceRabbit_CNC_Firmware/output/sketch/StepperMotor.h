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
  int fStepsPerMM, fMaxVelocity;
  float fMMPerStep;

  volatile uint8_t *fPinStepOutputRegister;
  float fAcceleration;
  void Step();

public:
  StepperMotor();
  void Initialize(uint8_t, uint8_t, uint8_t, int, int, int);

  void Move(float mm);
};

StepperMotor::StepperMotor()
{
}

// Initialize Stepper Manager
/*
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
  fAcceleration = acceleration;
  fMaxVelocity = maxVelocity_mm_per_min;

  fMMPerStep = (float)((float)1 / (float)fStepsPerMM);

  pinMode(fPinStep, OUTPUT);
  pinMode(fPinDir, OUTPUT);
  pinMode(fEnablePin, OUTPUT);

#ifdef STEPPERS_ALWAYS_ENABLED
  FastDigitalWrite(fEnablePin, LOW);
#endif
}

void StepperMotor::Step()
{
#ifndef STEPPERS_ALWAYS_ENABLED
  FastDigitalWrite(fEnablePin, LOW);
#endif

  // HIGH Step Port
  FastDigitalWrite(fPinStep, HIGH);

  // Delay
  delayMicroseconds(STEPPERS_MIN_PULSE_WIDTH_MICROSECONDS);

  // LOW Step Port
  FastDigitalWrite(fPinStep, LOW);

  // Delay
  delayMicroseconds(STEPPERS_MIN_PULSE_WIDTH_MICROSECONDS);
}

void StepperMotor::Move(float mm)
{
  // Calculate number of steps
  float steps = abs(mm * fStepsPerMM);
  int dir = (mm < 0) ? LOW : HIGH;

  // Set direction (DIR pin)
  FastDigitalWrite(fPinDir, dir);

  for (int i = 0; i < steps; i++)
  {
    // HIGH Step Port
    FastDigitalWrite(fPinStep, HIGH);

    // Delay
    delayMicroseconds(STEPPERS_MIN_PULSE_WIDTH_MICROSECONDS);

    // LOW Step Port
    FastDigitalWrite(fPinStep, LOW);

    // Delay
    delayMicroseconds(STEPPERS_MIN_PULSE_WIDTH_MICROSECONDS);
  }
}
