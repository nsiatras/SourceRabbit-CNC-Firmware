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
  byte fPinStep, fPinDir, fEnablePin;
  int fStepsPerMM, fMaxVelocity;
  float fAcceleration;

public:
  StepperMotor();
  void Initialize(byte, byte, byte, int, int, int);
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
void StepperMotor::Initialize(byte pinStep, byte pinDir, byte enablePin, int stepsPerMM, int acceleration, int maxVelocity_mm_per_min)
{
  fPinStep = pinStep;
  fPinDir = pinDir;
  fEnablePin = enablePin;
  fStepsPerMM = stepsPerMM;
  fAcceleration = acceleration / (60 ^ 2);
  fMaxVelocity = maxVelocity_mm_per_min;
}
