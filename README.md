#cmake_simavr_sample

[![Build Status](https://travis-ci.org/joemccann/dillinger.svg?branch=master)](https://travis-ci.org/joemccann/dillinger)

This project builds a sample project from simavr with cmake:

```sh
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./pc/ledramp-x86_64-linux-gnu.exe avr/ledramp-atmega168p.elf
```

This contains a sample program to demonstrate the use of simavr
using 'custom' code, and own "peripherals". It shows how it is
possible to "hook" code to the AVR pins, and also how to make
"peripherals" and also hook them up to AVR pins.

The demo will display a running "led ramp" that are the representation
of the PORTB pins of the mega168.

The mega168 firmware runs a timer and a pin-change interrupt that
will react to a "button press".

The display uses opengl and "glut" so it should be very portable.
On most linux you will need "freeglut-dev" package.

