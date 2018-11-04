#pragma once
/*
  X113647Stepper - a X113647/ULN2003A Stepper Motor library for Arduino

  This library is derived from the Arduino Stepper library http://www.arduino.cc/en/Tutorial/Stepper
  but with two differences:

  * uses a default pin mapping that matches the 28BYJ-48 stepper motor (1-3-2-4 compared to the standard library).
  * supports full-step, half-step and single-step modes

  For info and circuit diagrams see https://github.com/tardate/X113647Stepper

*/


namespace tardate {

/// Define the step mode
///
enum class StepMode : uint8_t {
    SingleStep,
    FullStep,
    HalfStep
};


class X113647Stepper {
  public:

    /*
     * Constructor with step mode specification
     * Sets the number of steps per revolution, stepping mode and which pins should control the motor.
     */
    X113647Stepper(int steps_per_revolution, int pin_in1, int pin_in2, int pin_in3, int pin_in4, StepMode step_mode = StepMode::FullStep);

    /*
     * Command: sets the speed in revs per minute
     */
    void setSpeed(float whatSpeed);

    /*
     * Command: Moves the motor steps_to_move steps.
     * If the number is negative, the motor moves in the reverse direction.
     */
    void step(int number_of_steps);

    /*
     * Command: Emergency Stop.
     * Terminates any movement in progres.
     */
    void emergencyStop();

    /*
     * Returns the version of the library
     */
    int version(void);

  private:

    /*
     * Command: initialise stepper output
     */
    void ignition();

    /*
     * Command: moves the motor forward or backwards.
     */
    void stepMotor(int this_step);

    unsigned long step_delay;     // delay between steps, in ms, based on speed
    unsigned long minimum_delay;  // minimum delay between steps
    int steps_per_revolution;     // actual number of steps per revolution given step mode
    StepMode step_mode;           // number of phases being used to drive the motor
    int steps_per_cycle;          // number of steps per revolution (before gearing)
    int signals_per_step;         // number of signals per step. when full step == 1, when half-step == 2
    int step_number;              // which step the motor is on
    volatile int steps_remaining; // number of steps remaining in step()

    // motor pin numbers:
    int pin_in1;
    int pin_in2;
    int pin_in3;
    int pin_in4;

    int step_codes[8];

};

}
