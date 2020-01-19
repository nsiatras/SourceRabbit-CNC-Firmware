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
#ifndef STEPPERMOTORMANAGER_H
#define STEPPERMOTORMANAGER_H
#include "StepperMotor.h"

class StepperMotorManager : public Manager
{
private:
  boolean fLimitSwitchIsOn = false;

public:
  static StepperMotorManager ACTIVE_INSTANCE; // Create a static Active Instance for the StepperMotorManager
  StepperMotor fStepperMotorX, fStepperMotorY, fStepperMotorZ, fStepperMotorA;
  void Initialize();

  void HomeXAxis();
  void HomeYAxis();
  void HomeZAxis();

  // Stepper Motor Manager Events
  void OnLimitSwitchOn_EventHandler() override;
  void OnLimitSwitchOff_EventHandler() override;
};

StepperMotorManager StepperMotorManager::ACTIVE_INSTANCE; // Declare the static ACTIVE_INSTANCE

// Initialize the Stepper Motor Manager
void StepperMotorManager::Initialize()
{
  // Call the parent Initialize
  Manager::Initialize();

  // Initialize 4 Stepper motors (X,Y,Z and A axis)
  fStepperMotorX.Initialize(STEPPER_X_STEP_PIN, STEPPER_X_DIR_PIN, STEPPER_X_ENABLE_PIN, STEPPER_X_STEPS_PER_MM, STEPPER_X_ACCELERATION, STEPPER_X_MAX_VELOCITY);
  fStepperMotorY.Initialize(STEPPER_Y_STEP_PIN, STEPPER_Y_DIR_PIN, STEPPER_Y_ENABLE_PIN, STEPPER_Y_STEPS_PER_MM, STEPPER_Y_ACCELERATION, STEPPER_Y_MAX_VELOCITY);
  fStepperMotorY.Initialize(STEPPER_Z_STEP_PIN, STEPPER_Z_DIR_PIN, STEPPER_Z_ENABLE_PIN, STEPPER_Z_STEPS_PER_MM, STEPPER_Z_ACCELERATION, STEPPER_Z_MAX_VELOCITY);
  fStepperMotorY.Initialize(STEPPER_A_STEP_PIN, STEPPER_A_DIR_PIN, STEPPER_A_ENABLE_PIN, STEPPER_A_STEPS_PER_MM, STEPPER_A_ACCELERATION, STEPPER_A_MAX_VELOCITY);
}

void StepperMotorManager::HomeXAxis()
{
  // Move x motor until the Limit Switch is clicked
  while (!fLimitSwitchIsOn)
  {
    delay(100);
  }

#ifdef SHOW_DEBUG_MESSAGES
  Serial.println("DEBUG:StepperMotorManager::HomeXAxis Finished!");
#endif
}

void StepperMotorManager::HomeYAxis()
{
  while (!fLimitSwitchIsOn)
  {
    delay(100);
  }

#ifdef SHOW_DEBUG_MESSAGES
  Serial.println("DEBUG:StepperMotorManager::HomeYAxis Finished!");
#endif
}

void StepperMotorManager::HomeZAxis()
{
  while (!fLimitSwitchIsOn)
  {
    delay(100);
  }

#ifdef SHOW_DEBUG_MESSAGES
  Serial.println("DEBUG:StepperMotorManager::HomeZAxis Finished!");
#endif
}

void StepperMotorManager::OnLimitSwitchOn_EventHandler()
{
  fLimitSwitchIsOn = true;
#ifdef SHOW_DEBUG_MESSAGES
  Serial.println("DEBUG:StepperMotorManager::OnLimitSwitchOn_EventHandler");
#endif
}

void StepperMotorManager::OnLimitSwitchOff_EventHandler()
{
  fLimitSwitchIsOn = false;
#ifdef SHOW_DEBUG_MESSAGES
  Serial.println("DEBUG:StepperMotorManager::OnLimitSwitchOff_EventHandler");
#endif
}

#endif