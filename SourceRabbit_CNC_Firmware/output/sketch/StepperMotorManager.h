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
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <math.h>
#include "EError.h"
#include "EMachineStatus.h"
#include "EAxis.h"
#include "Events.h"
#include "Manager.h"
#include "BoardPinout.h"
#include "Config.h"

// Declare stepper motors
AccelStepper STEPPER_MOTOR_X(AccelStepper::FULL2WIRE, STEPPER_X_STEP_PIN, STEPPER_X_DIR_PIN);
AccelStepper STEPPER_MOTOR_Y(AccelStepper::FULL2WIRE, STEPPER_Y_STEP_PIN, STEPPER_Y_DIR_PIN);
AccelStepper STEPPER_MOTOR_Z(AccelStepper::FULL2WIRE, STEPPER_Z_STEP_PIN, STEPPER_Z_DIR_PIN);
AccelStepper STEPPER_MOTOR_A(AccelStepper::FULL2WIRE, STEPPER_A_STEP_PIN, STEPPER_A_DIR_PIN);

// Up to 10 steppers can be handled as a group by MultiStepper
//MultiStepper STEPPERS;

class StepperMotorManager : public Manager
{
private:
  bool fLimitSwitchIsOn = false;
  bool fTouchProbeIsOn = false;

  double STEPPER_X_MM_PER_STEP, STEPPER_Y_MM_PER_STEP, STEPPER_Z_MM_PER_STEP, STEPPER_A_MM_PER_STEP;

public:
  static StepperMotorManager ACTIVE_INSTANCE; // Create a static Active Instance for the StepperMotorManager
  //StepperMotor fStepperMotorX, fStepperMotorY, fStepperMotorZ, fStepperMotorA;

  void Initialize() override;
  void Reset() override;

  void MoveAxisToHomePosition(EAxis axis);

  void setStepperSpeed(EAxis axis, double feedRate);
  void MoveSteppers(double positions[]);

  // Stepper Motor Manager Events
  void OnLimitSwitchOn_EventHandler() override;
  void OnLimitSwitchOff_EventHandler() override;
  void OnTouchProbeOn_EventHandler() override;
  void OnTouchProbeOff_EventHandler() override;
};

StepperMotorManager StepperMotorManager::ACTIVE_INSTANCE; // Declare the static ACTIVE_INSTANCE

// Initialize the Stepper Motor Manager
void StepperMotorManager::Initialize()
{
  // Call the parent Initialize
  Manager::Initialize();

  STEPPER_X_MM_PER_STEP = 1.000 / STEPPER_X_STEPS_PER_MM;
  STEPPER_Y_MM_PER_STEP = 1.000 / STEPPER_Y_STEPS_PER_MM;
  STEPPER_Z_MM_PER_STEP = 1.000 / STEPPER_Z_STEPS_PER_MM;
  STEPPER_A_MM_PER_STEP = 1.000 / STEPPER_A_STEPS_PER_MM;

  // Set stepper motors parameters for 4 motors (X,Y,Z and A axis)
  STEPPER_MOTOR_X.setEnablePin(STEPPER_X_ENABLE_PIN);
  STEPPER_MOTOR_X.setMaxSpeed(STEPPER_X_MAX_FEEDRATE / 60.000 / STEPPER_X_MM_PER_STEP);
  STEPPER_MOTOR_X.setSpeed(STEPPER_MOTOR_X.maxSpeed());
  STEPPER_MOTOR_X.setAcceleration(1.000 * STEPPER_X_ACCELERATION * STEPPER_X_STEPS_PER_MM);
  STEPPER_MOTOR_X.setMinPulseWidth(STEPPERS_MIN_PULSE_WIDTH_MICROSECONDS);
  STEPPER_MOTOR_X.setCurrentPosition(0.000);

  STEPPER_MOTOR_Y.setEnablePin(STEPPER_Y_ENABLE_PIN);
  STEPPER_MOTOR_Y.setMaxSpeed(STEPPER_Y_MAX_FEEDRATE / 60.000 / STEPPER_Y_MM_PER_STEP);
  STEPPER_MOTOR_Y.setSpeed(STEPPER_MOTOR_Y.maxSpeed());
  STEPPER_MOTOR_Y.setAcceleration(1.000 * STEPPER_Y_ACCELERATION * STEPPER_Y_STEPS_PER_MM);
  STEPPER_MOTOR_Y.setMinPulseWidth(STEPPERS_MIN_PULSE_WIDTH_MICROSECONDS);
  STEPPER_MOTOR_Y.setCurrentPosition(0.000);

  STEPPER_MOTOR_Z.setEnablePin(STEPPER_Z_ENABLE_PIN);
  STEPPER_MOTOR_Z.setMaxSpeed(STEPPER_Z_MAX_FEEDRATE / 60.000 / STEPPER_Z_MM_PER_STEP);
  STEPPER_MOTOR_Z.setSpeed(STEPPER_MOTOR_Z.maxSpeed());
  STEPPER_MOTOR_Z.setAcceleration(1.000 * STEPPER_Z_ACCELERATION * STEPPER_Z_STEPS_PER_MM);
  STEPPER_MOTOR_Z.setMinPulseWidth(STEPPERS_MIN_PULSE_WIDTH_MICROSECONDS);
  STEPPER_MOTOR_Z.setCurrentPosition(0.000);

  STEPPER_MOTOR_A.setEnablePin(STEPPER_A_ENABLE_PIN);
  STEPPER_MOTOR_A.setMaxSpeed(STEPPER_A_MAX_FEEDRATE / 60.000 / STEPPER_A_MM_PER_STEP);
  STEPPER_MOTOR_A.setSpeed(STEPPER_MOTOR_A.maxSpeed());
  STEPPER_MOTOR_A.setAcceleration(1.000 * STEPPER_A_ACCELERATION * STEPPER_A_STEPS_PER_MM);
  STEPPER_MOTOR_A.setMinPulseWidth(STEPPERS_MIN_PULSE_WIDTH_MICROSECONDS);
  STEPPER_MOTOR_A.setCurrentPosition(0.000);

  // Set the enable pins as output
  pinMode(STEPPER_X_ENABLE_PIN, OUTPUT);
  pinMode(STEPPER_Y_ENABLE_PIN, OUTPUT);
  pinMode(STEPPER_Z_ENABLE_PIN, OUTPUT);
  pinMode(STEPPER_A_ENABLE_PIN, OUTPUT);

#ifdef STEPPERS_ALWAYS_ENABLED
  digitalWrite(STEPPER_X_ENABLE_PIN, LOW);
  digitalWrite(STEPPER_Y_ENABLE_PIN, LOW);
  digitalWrite(STEPPER_Z_ENABLE_PIN, LOW);
  digitalWrite(STEPPER_A_ENABLE_PIN, LOW);
#endif
}

// Reset the stepper motor manager
void StepperMotorManager::Reset()
{
  Manager::Reset();
  StepperMotorManager::ACTIVE_INSTANCE.Initialize();
}

// This method calculates and sets the speed of the stepper in steps/second
// from the feedRate which is in mm/min
void StepperMotorManager::setStepperSpeed(EAxis axis, double feedRate)
{
  long stepsPerSecond = 0;

  switch (axis)
  {
  case AXIS_X:
    STEPPER_MOTOR_X.setSpeed(feedRate / 60.000 / STEPPER_X_MM_PER_STEP);
    break;

  case AXIS_Y:
    STEPPER_MOTOR_Y.setSpeed(feedRate / 60 * STEPPER_Y_STEPS_PER_MM);
    break;

  case AXIS_Z:
    STEPPER_MOTOR_Z.setSpeed(feedRate / 60 * STEPPER_Z_STEPS_PER_MM);
    break;

  case AXIS_A:
    STEPPER_MOTOR_A.setSpeed(feedRate / 60 * STEPPER_A_STEPS_PER_MM);
    break;

  case AXIS_B:
    // STEPPER_MOTOR_B.setSpeed(feedRate / 60 * STEPPER_B_STEPS_PER_MM);
    break;

  case AXIS_C:
    // STEPPER_MOTOR_C.setSpeed(feedRate / 60 * STEPPER_C_STEPS_PER_MM);
    break;
  }
}

void StepperMotorManager::MoveSteppers(double positions[])
{
  // Convert positions to steps and give them to motors
  STEPPER_MOTOR_X.moveTo((long)(positions[0] * STEPPER_X_STEPS_PER_MM));
  STEPPER_MOTOR_Y.moveTo((long)(positions[1] * STEPPER_Y_STEPS_PER_MM));
  STEPPER_MOTOR_Z.moveTo((long)(positions[2] * STEPPER_Z_STEPS_PER_MM));
  STEPPER_MOTOR_A.moveTo((long)(positions[3] * STEPPER_A_STEPS_PER_MM));
}

// The MoveAxisToHomePosition moves the axis to home direction
// until the Limit Switch is triggered.
void StepperMotorManager::MoveAxisToHomePosition(EAxis axis)
{
  // TODO

  switch (axis)
  {
  case AXIS_X:
    break;

  case AXIS_Y:
    break;

  case AXIS_Z:
    break;

  case AXIS_A:
    break;

  case AXIS_B:
    break;

  case AXIS_C:
    break;
  }

  // Wait to touch Limit Switch
  while (!fLimitSwitchIsOn)
  {
    delay(1);
  }

  // Wait to stop touching Limit Switch
  while (fLimitSwitchIsOn)
  {
    delay(1);
  }

#ifdef SHOW_DEBUG_MESSAGES
  Serial.println("DEBUG:StepperMotorManager::MoveAxisToHomePosition:" + String(axis) + " Axis Homed");
#endif
}

void StepperMotorManager::OnLimitSwitchOn_EventHandler()
{
  fLimitSwitchIsOn = true;
}

void StepperMotorManager::OnLimitSwitchOff_EventHandler()
{
  fLimitSwitchIsOn = false;
}

void StepperMotorManager::OnTouchProbeOn_EventHandler()
{
  fTouchProbeIsOn = true;
}

void StepperMotorManager::OnTouchProbeOff_EventHandler()
{
  fTouchProbeIsOn = false;
}

#endif