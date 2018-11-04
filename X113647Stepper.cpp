/*
  X113647Stepper - a X113647/ULN2003A Stepper Motor library for Arduino
  See X113647Stepper.h for notes
 */


#include "Arduino.h"
#include "X113647Stepper.h"

namespace tardate {


X113647Stepper::X113647Stepper(int steps_per_revolution, int pin_in1, int pin_in2, int pin_in3, int pin_in4, StepMode step_mode) {

  this->step_mode = step_mode;
  this->steps_per_revolution = steps_per_revolution;

  // Arduino pins for the motor control connection:
  this->pin_in1 = pin_in1;
  this->pin_in2 = pin_in2;
  this->pin_in3 = pin_in3;
  this->pin_in4 = pin_in4;

  ignition();

}


void X113647Stepper::emergencyStop() {
  this->steps_remaining = 0;
}


void X113647Stepper::ignition() {
  // set steps_remaining to zero
  this->steps_remaining = 0;

  // common instance variable initialisation
  this->step_number = 0;

  // Encode the the clockwise sequence of control signals:
  switch(this->step_mode) {
  case StepMode::SingleStep:
    this->steps_per_cycle = 4;
    this->step_codes[0] = B00001;
    this->step_codes[1] = B00010;
    this->step_codes[2] = B00100;
    this->step_codes[3] = B01000;
    break;
  case StepMode::FullStep:
    this->steps_per_cycle = 4;
    this->step_codes[0] = B00011;
    this->step_codes[1] = B00110;
    this->step_codes[2] = B01100;
    this->step_codes[3] = B01001;
    break;
  case StepMode::HalfStep:
    this->steps_per_cycle = 8;
    this->steps_per_revolution = this->steps_per_revolution * 2;
    this->step_codes[0] = B00001;
    this->step_codes[1] = B00011;
    this->step_codes[2] = B00010;
    this->step_codes[3] = B00110;
    this->step_codes[4] = B00100;
    this->step_codes[5] = B01100;
    this->step_codes[6] = B01000;
    this->step_codes[7] = B01001;
    break;
  }
  this->signals_per_step = this->steps_per_cycle / 4;
  this->minimum_delay = this->signals_per_step + 1;

  // setup the pins on the microcontroller:
  pinMode(this->pin_in1, OUTPUT);
  pinMode(this->pin_in2, OUTPUT);
  pinMode(this->pin_in3, OUTPUT);
  pinMode(this->pin_in4, OUTPUT);

  // set a default speed 1rpm
  setSpeed(1);
}


void X113647Stepper::setSpeed(float whatSpeed) {
  this->step_delay = 60L * 1000L / this->steps_per_revolution / whatSpeed / this->signals_per_step;
  if(this->step_delay < this->minimum_delay)
    this->step_delay = this->minimum_delay;
}


void X113647Stepper::step(int steps_to_move) {
  this->steps_remaining = abs(steps_to_move) * this->signals_per_step;  // how many steps to take

  // determine direction based on whether steps_to_move is + or -:
  int direction = 1;                    // Direction of rotation: default forward
  if (steps_to_move < 0) direction = 0; // reverse

  unsigned long last_step_time = 0;     // time stamp in ms of when the last step was taken

  // decrement the number of steps, moving one step each time:
  while(this->steps_remaining > 0) {

    // move only if the appropriate delay has passed:
    if (millis() >= last_step_time + this->step_delay) {

      // get the timeStamp of when you stepped:
      last_step_time = millis();

      // increment or decrement the step number,
      // depending on direction:
      if (direction == 1) {
        this->step_number++;
        if (this->step_number == this->steps_per_revolution) {
          this->step_number = 0;
        }
      }
      else {
        if (this->step_number == 0) {
          this->step_number = this->steps_per_revolution;
        }
        this->step_number--;
      }
      // decrement the steps remaining:
      this->steps_remaining--;
      // step the motor:
      stepMotor(this->step_number % this->steps_per_cycle);
    }
  }
  // clear signals
  digitalWrite(pin_in1, LOW);
  digitalWrite(pin_in2, LOW);
  digitalWrite(pin_in3, LOW);
  digitalWrite(pin_in4, LOW);
}


void X113647Stepper::stepMotor(int thisStep) {
  digitalWrite(pin_in1, bitRead(this->step_codes[thisStep], 0));
  digitalWrite(pin_in2, bitRead(this->step_codes[thisStep], 1));
  digitalWrite(pin_in3, bitRead(this->step_codes[thisStep], 2));
  digitalWrite(pin_in4, bitRead(this->step_codes[thisStep], 3));
}


int X113647Stepper::version(void) {
  return 2;
}

}
