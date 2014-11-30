# X113647Stepper Arduino Library

The X113647 Stepper Motor Driver Board is pretty common in Arduino kits, and
[available from various suppliers on aliexpress](http://www.aliexpress.com/item/Free-shipping-one-set-5-v-ULN2003-stepper-motor-drive-board/1938256381.html),
often with a 28BYJ-48 stepper motor. How do you know if you have a board like an X113647? Here's what mine looks like:

![The X113647](./assets/X113647_board.jpg?raw=true)


Unfortunately, details of the board are scant. I'm not even sure if X113647 is it's correct name or nomenclature.

One of the best technical resources is
[this geeetech page](http://www.geeetech.com/wiki/index.php/Stepper_Motor_5V_4-Phase_5-Wire_%26_ULN2003_Driver_Board_for_Arduino),
best read in conjuction with a fantastic teardown and examination of the 28BYJ-48 stepper motor
by [Gaven MacDonald on youtube](http://youtu.be/Dc16mKFA7Fo).

It doesn't take long when playing around with an X113647 board and 28BYJ-48 motor to realise two things:
* The drive control is quite different from that assumed by the standard [Arduino Stepper library](http://www.arduino.cc/en/Tutorial/Stepper), and
* There don't seem to be any suitable parts on offer to draw nice diagrams with the wonderful [Fritzing app](http://fritzing.org/home/).

So this repository is the result of my little efforts to get around these limitations. There are two things here:
* An X113647Stepper Arduino Library, which drives the X113647 in a similar way to the standard Arduino Stepper library, but fixes the few incompatibilities and makes it possible to fully exploit the stepper motor with the X113647 board, and
* Some new Fritzing parts for the X113647 and 28BYJ-48. These are not suitable for etching your own stepper drive board, but they do work nicely for drawing circuits involving and X113647 or 28BYJ-48 components.


Feel free to borrow any ideas, and if you spot any issues do let me know. IF you see ways to improve what is on offer here, do let me know, or better yet, send a pull request!

## Example Programs

There are a few examples included with the X113647Stepper library:
* [FullSweep](./examples/FullSweep) a basic example of the X113647 at work - driving a stepper to sweep 360 degrees back and forth
* [DirectDrive](./examples/DirectDrive) for diagnostic purposes, this program drives the X113647 directly without the use of any libraries
* [SinglePhaseSweepWithSteeperLibrary](./examples/SinglePhaseSweepWithSteeperLibrary) demonstrates how it is possible to drive the X113647 board with the standard Stepper library - albeit with limited functionality.

## Fritzing Parts

If you use [Fritzing](http://fritzing.org/home/), it is annoying not to have parts available for these common stepper components!

After searching high and low and not finding anything already available, I thought I'd try my hand at creating some custom parts
(using the new part formats - most recently tested with Fritzing 0.9.0b06.11). This was my first experience creating Fritzing parts, so appologies for anything I botched up. Note that these parts are not suitable for etching your own stepper drive board, but they do work nicely for drawing circuits involving and X113647 or 28BYJ-48 components.
* [28BYJ-48 Stepper Motor](./fritzing_parts/28BYJ-48 Stepper Motor.fzpz?raw=true) is a part similar to the [Adafruit Gear-Reduced Steeper Motor](https://www.adafruit.com/products/858) however with different connections
* [X113647 Stepper Driver Board](./fritzing_parts/X113647 Stepper Driver Board.fzpz?raw=true) is a part for the board.
* see the [fritzing_parts](./fritzing_parts/) folder for all the source files for the parts if you wish to modify, borrow or copy.

With these parts you can draw stepper motor circuits like this canonical hookup of the X113647 and 28BYJ-48 to an Arduino Uno, with external power supply for the motor. In this case, the breadboard is just a glorified cable connector.

![The Build](./assets/X113647Stepper_bb.jpg?raw=true)

Note the crossover of the wires eminating from the 28BYJ-48. This is actually done in the wiring of the standard connector provided with the stepper motor - but I haven't included this detail in the part as yet.


