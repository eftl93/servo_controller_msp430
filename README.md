# servo_controller_msp430
Servo controller for 4 servos using MSP430G2553
## Abstract
The goal of this project is to create an independent module to control 4 servo motor with a UART interface. 

This module is meant to be added to projects that require 4 additional PWM signals that have enough resolution to control servo motors. It can also be used independently if paired up directly to a computer via USB-UART converter or connecting it to a Bluetooth Module that accepts UART communication. 

The microcontroller of choice is the MSP430G2553, TIMERA module was used to keep track of time and create an interrupt to wake up the processor after a set amount of time. The MCU is running at 16 MHz generated internally and the timer module is running using the SMCLK without post-scaling. Code Composer Studio 11.1.0 was used to develop and debug. 

The prototype is built on a perboard, it includes an onboard low-dropout 3.3V regulator. Headers are included to program via MSP-FET Flash Emulation Tool. Pinouts are soldered in order to connect Servo Motors with standard connectors. An additional 32 KHz crystal was included for future functionality expansions. The power connector is connected to the servo power pins directly therefor the maximum voltage for this prototype is 6V. In this code the characters: 'w', 's', 'a', 'd', 'i', 'k', 'j', and 'l' are used to increment and decrement the duty cycle of all 4 servo ports. 

## Alternate methods
There are two libraries that can be used for this purpose using the Energia Development Environment. One for servos and one for UART. That route was not chosen in this case in order to practice and understand the program flow for msp430 MCUs. 

## Method of execution
It was decided to use “soft-PWM” method in order to control more than 2 servos with only one timer in order to leave the second timer (TA2) available in case it’s needed for additional functions also so any GPIO can be used for servos. Signals for servos need to have a specific frequency of 50 Hz and a positive with that ranges from 1 mS to 2 mS required specific timing. 

1. Disable watchdog timer
2. Set internal clock source
3. Initialize the USCI module in order to use the UART and its corresponding pins
4. Initialize the GPIO peripherals as outputs.
5. Initialize the timer module

  ..* Set the time source

  ..*Put the timer in “UP MODE”

  ..*Set how frequent to get the timer to interrupt and exit the Low Power Mode

  ..*Enable the interrupt

6. Run the main() functions 
