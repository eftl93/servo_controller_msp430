# servo_controller_msp430
Servo controller for 4 servos using MSP430G2553
## Abstract
The goal of this project is to create an independent module to control 4 servo motor with a UART` interface. 
This module is meant to be added to projects that require 4 additional PWM signals that have enough resolution to control servo motors. It can also be used independently if paired up directly to a computer via USB-UART converter or connecting it to a Bluetooth Module that accepts UART communication. 
The microcontroller of choice is the MSP430G2553, TIMERA module was used to keep track of time and interrupt after a set amount of time. The MCU is running at 16 MHz generated internally and the timer module is running using the SMCLK without post-scaling. Code Composer Studio 11.1.0 was used to develop and debug. 
The prototype is built on a perboard, it includes an onboard low-dropout 3.3V regulator. Headers are included to program via MSP-FET Flash Emulation Tool. Pinouts are soldered in order to connect Servo Motors with standard connectors. An additional 32 KHz crystal was included for future functionality expansions. The power connector is connected to the servo power pins directly therefor the maximum voltage for this prototype is 6V. 
