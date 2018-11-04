/*

  FullStepSweep.ino

  Uses the X113647Stepper library, and demonstrates continuous full-step cw/ccw rotation
  with a delay between each change in direction
  (the delay is longer when switching from ccw to cw).

  For info and circuit diagrams see https://github.com/tardate/X113647Stepper

 */

#include <X113647Stepper.h>

static const int STEPS_PER_REVOLUTION = 32 * 64;

static const int PIN_IN1_BLUE         = 8;
static const int PIN_IN2_PINK         = 9;
static const int PIN_IN3_YELLOW       = 10;
static const int PIN_IN4_ORANGE       = 11;

// initialize the stepper library
tardate::X113647Stepper myStepper(
  STEPS_PER_REVOLUTION,
  PIN_IN1_BLUE, PIN_IN2_PINK, PIN_IN3_YELLOW, PIN_IN4_ORANGE
);

void setup() {
  // set the speed in rpm:
  myStepper.setSpeed(4);
}

void loop() {
  // step one revolution in one direction:
  myStepper.step(STEPS_PER_REVOLUTION);
  delay(200);

  // step one revolution in the other direction:
  myStepper.step(-STEPS_PER_REVOLUTION);
  delay(1000);
}
