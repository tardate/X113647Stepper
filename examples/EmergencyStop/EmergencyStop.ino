
/*
 X113647 Stepper Motor Control - one revolution with emergency stop ISR

 This program drives a 4-Phase 5-Wire stepper motor using 4 wires
 via an X113647 (ULN2003-based) driver board.

 The motor is attached to digital pins 8 - 11 of the Arduino.

 The motor should revolve one revolution in one direction, then
 one revolution in the other direction.

 */

#include <X113647Stepper.h>

const int stepsPerRevolution = 64 * 32;  // change this to fit the number of steps per revolution for your motor
volatile boolean stopped = FALSE;

// initialize the stepper library on pins 8 through 11:
X113647Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);


void setup() {
  // set the speed in rpm:
  myStepper.setSpeed(6.5);

  // put an emergency stop button on pin 2 or 3 (we can attach an interrupt on these pins)
  // the pin uses internal pullup resistors, so button can just ground the pin.
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), eStop, FALLING);
}

void loop()
{
  // step one revolution  in one direction:
  if(!stopped)
  {
    myStepper.step(stepsPerRevolution);
    delay(500);
  }

  // step one revolution in the other direction:
  if(!stopped)
  {
    myStepper.step(-stepsPerRevolution);
    delay(500);
  }
}

void eStop()
{
  myStepper.estop(); // stop the motor first
  stopped = true;    // make sure motor won't start on next loop()

}
