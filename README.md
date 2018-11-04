# X113647Stepper Arduino Library

The 28BYJ-48 stepper motor and ULN2003A-based X113647 Stepper Motor Driver Board is pretty common in Arduino kits, and
[available from various suppliers on aliexpress](http://www.aliexpress.com/item/Free-shipping-one-set-5-v-ULN2003-stepper-motor-drive-board/1938256381.html).

* 28BYJ-48 stepper motor is a unipolar motor with 32 steps and a 64:1 gear reduction drive.
* the X113647 module is basically just the ULN2003A with additional LEDs and convenience pins for connecting power for the motor.

I've gone into more detail, including Fritzing parts, in the LittleArduinoProjects repository:

* [LEAP#431 28BYJ-48](https://github.com/tardate/LittleArduinoProjects/tree/master/Kinetics/StepperMotors/28BYJ48) - all about the 28BYJ-48
* [LEAP#432 ULN2003Module](https://github.com/tardate/LittleArduinoProjects/tree/master/Kinetics/StepperMotors/ULN2003Module) - deconstructing a ULN2003 module such as the X113647



## Why the X113647Stepper Library?

Although the name is now a bit misleading, this project started as an attempt to address two issues:

* clarify the pin connections required to work with the 28BYJ-48
* add a half-step mode, where the standard Stepper library only provides full-step control

I've updated the X113647Stepper library to better reflect these issues.
Feel free to borrow and use this library if it helps. In general though, I'd recommend alternatives:

* stick to the standard [Arduino Stepper library](https://www.arduino.cc/en/Reference/Stepper) if full-step control is sufficient
* look at some far more capable libraries such as [AccelStepper](https://github.com/waspinator/AccelStepper) if you need more


## Pin Connections Summary

Most (all?) versions of the 28BYJ-48 expose a consistent Blue-Pink-Yellow-Orange-Red wire sequence at the connector.
Red is the common (5V/positive) connection.

The full step sequence required by the 28BYJ-48 for the 4 control lines is:

| Step | Blue | Pink | Yellow | Orange |
|------|------|------|--------|--------|
|  1   | 1    | 1    |        |        |
|  2   |      | 1    | 1      |        |
|  3   |      |      | 1      | 1      |
|  4   | 1    |      |        | 1      |


The standard Stepper Library implements the following sequence:

|Step | C0 | C1 | C2 | C3 |
|-----|----|----|----|----|
|   1 |  1 |  0 |  1 |  0 |
|   2 |  0 |  1 |  1 |  0 |
|   3 |  0 |  1 |  0 |  1 |
|   4 |  1 |  0 |  0 |  1 |


It is readily observed that switching Pink/Yellow (C1/C2) aligns things nicely,
so we end up with a 1-3-2-4 pin mapping for initializing the standard Stepper library as follows:

    Stepper myStepper(STEPS_PER_REVOLUTION, PIN_IN1_BLUE, PIN_IN3_YELLOW, PIN_IN2_PINK, PIN_IN4_ORANGE);

In full-step mode, `STEPS_PER_REVOLUTION` is 32 (steps) * 64 (gear reduction) i.e. 2048.


## Using the X113647Stepper Library


The `X113647Stepper` class (in the `tardate` namespace) is virtually a drop-in replacement for the Stepper library.

Basic initialisation (full step mode by default):

    tardate::X113647Stepper myStepper(STEPS_PER_REVOLUTION, PIN_IN1_BLUE, PIN_IN2_PINK, PIN_IN3_YELLOW, PIN_IN4_ORANGE);

Or add the StepMode parameter. For example, half-step:

    tardate::X113647Stepper myStepper(STEPS_PER_REVOLUTION, PIN_IN1_BLUE, PIN_IN2_PINK, PIN_IN3_YELLOW, PIN_IN4_ORANGE, tardate::StepMode::HalfStep);


Example sketches:

* [DirectDrive.ino](./examples/DirectDrive/DirectDrive.ino) - examples of driving various stepper modes without a library
* [WithStepperLibrary.ino](./examples/WithStepperLibrary/WithStepperLibrary.ino) - using the standard Stepper library
* [HalfStepSweep.ino](./examples/HalfStepSweep/HalfStepSweep.ino) - using X113647Stepper, half-step
* [FullStepSweep.ino](./examples/FullStepSweep/FullStepSweep.ino) - using X113647Stepper, full-step
* [SingleStepSweep.ino](./examples/SingleStepSweep/SingleStepSweep.ino) - using X113647Stepper, single-step
* [EmergencyStop.ino](./examples/EmergencyStop/EmergencyStop.ino) - using X113647Stepper, half-step, with immiedate stop function



## Construction

The stepper motor and driver will typically draw at least 130mA at 5V with [HalfStepSweep](./examples/HalfStepSweep),
and over 250mA at 5V with [WithStepperLibrary](./examples/WithStepperLibrary),
so it is not particularly advisable to power directly from the Arduino's regulated supply.

![The Build](./assets/X113647Stepper_bb.jpg?raw=true)

Note the crossover of the wires eminating from the 28BYJ-48. This is actually done in the wiring of the standard connector provided with the stepper motor - but I haven't included this detail in the part as yet.

![Schematic](./assets/X113647Stepper_schematic.jpg?raw=true)

![The X113647](./assets/X113647_board.jpg?raw=true)

## Credits and References
* [Arduino Stepper library](https://www.arduino.cc/en/Reference/Stepper)
* [AccelStepper](https://github.com/waspinator/AccelStepper)
* [LEAP#431 28BYJ-48](https://github.com/tardate/LittleArduinoProjects/tree/master/Kinetics/StepperMotors/28BYJ48) - all about the 28BYJ-48
* [LEAP#432 ULN2003Module](https://github.com/tardate/LittleArduinoProjects/tree/master/Kinetics/StepperMotors/ULN2003Module)
