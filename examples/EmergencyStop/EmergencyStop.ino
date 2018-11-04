/*

  EmergencyStop.ino

  Uses the X113647Stepper library, and demonstrates continuous cw/ccw rotation with an emergency stop ISR

  The motor should revolve one revolution in one direction, then
  one revolution in the other direction.

  For info and circuit diagrams see https://github.com/tardate/X113647Stepper

 */

#include <X113647Stepper.h>

static const int STEPS_PER_REVOLUTION = 32 * 64;

static const int PIN_IN1_BLUE         = 8;
static const int PIN_IN2_PINK         = 9;
static const int PIN_IN3_YELLOW       = 10;
static const int PIN_IN4_ORANGE       = 11;

volatile boolean stopped = false;

// initialize the stepper library
tardate::X113647Stepper myStepper(STEPS_PER_REVOLUTION, PIN_IN1_BLUE, PIN_IN2_PINK, PIN_IN3_YELLOW, PIN_IN4_ORANGE);


void setup() {
  // set the speed in rpm:
  myStepper.setSpeed(6.5);

  // put an emergency stop button on pin 2 or 3 (we can attach an interrupt on these pins)
  // the pin uses internal pullup resistors, so button can just ground the pin.
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), handleEmergencyStop, FALLING);
}


void loop() {
  if(!stopped) {
    // step one revolution  in one direction:
    myStepper.step(STEPS_PER_REVOLUTION);
    delay(500);
  }

  if(!stopped) {
    // step one revolution in the other direction:
    myStepper.step(-STEPS_PER_REVOLUTION);
    delay(500);
  }

  if(stopped) {
    // wait a while before starting up again
    delay(2000);
    stopped = false;
  }
}


void handleEmergencyStop() {
  myStepper.emergencyStop(); // stop the motor first
  stopped = true;    // make sure motor won't start on next loop()
}
