# servo_controller_msp430
![image](https://user-images.githubusercontent.com/86902176/174351745-566496b7-6b94-4d67-b228-3ee8d65ea0e0.png)

Servo controller for 4 servos using MSP430G2553
## Abstract
The goal of this project is to create an independent module to control 4 servo motors with a UART interface. 

This module is meant to be added to projects that require 4 additional PWM signals that have enough resolution to control servo motors. It can also be used independently if paired up directly to a computer via USB-UART converter or connecting it to a Bluetooth Module that accepts UART communication. 

The microcontroller of choice is the MSP430G2553, TIMER_A module was used to keep track of time and create an interrupt to wake up the processor after a set amount of time. The MCU is running at 16 MHz generated internally and the timer module is running using the SMCLK without post-scaling. Code Composer Studio 11.1.0 was used to develop and debug. 

The prototype is built on a perboard, it includes an onboard low-dropout 3.3V regulator. Headers are included to program via MSP-FET Flash Emulation Tool. Pinouts are soldered in order to connect Servo Motors with standard connectors. An additional 32 KHz crystal was included for future functionality expansions. The power connector is connected to the servo power pins directly therefor the maximum voltage for this prototype is 6V. In this code the characters: 'w', 's', 'a', 'd', 'i', 'k', 'j', and 'l' are used to increment and decrement the duty cycle of all 4 servo ports.  

## Method of execution
It was decided to use “soft-PWM” method in order to control more than 2 servos with only one timer in order to leave the second timer (TA1) available in case it’s needed for additional functions also so any GPIO can be used for servos. Signals for servos need to have a specific frequency of 50 Hz and a positive with that ranges from 1 mS to 2 mS required specific timing. 

1. Disable watchdog timer.
2. Set internal clock source.
3. Initialize the USCI module in order to use the UART and its corresponding pins.
4. Initialize the GPIO peripherals as outputs.
5. Initialize the timer module.
    - Set the time source.
    - Put the timer in “UP MODE”.
    - Set how frequent to get the timer to interrupt and exit the "Low Power Mode".
    - Enable the interrupt.

6. Create the ISR (interrupt service routine) to count "ticks" and update the flag for each corresponding servo":
    - check how many times has the interrupt has been activated by the timer (how many ticks).
    - if the number of ticks accumulated equals to the duty cycle, set the servo's "clear" flag.
    - if the number of ticks accumulated equals to the period, set the all the servos' "set" flag.
    - before exiting the ISR, increment the tick counter (timer_count).
    - use directive to clear bit of the status register to leave the low power mode once the ISR is exited in order to execute the code in the main() function until the processor goes back to low power mode.
8. Run the main() function:
    - Check if any flags have been updated in the ISR.
      - Set flags will be cleared.
      - Call the function according to the flag that had been set in the ISR. 
    - Check if the RX flag is set, if it is, read the received character (no need to use USCI interrupt since we choose to respond once every time the MCU leaves the ISR only).
    - Depending on the the character received, update the duty cycle requested for the corresponding servo. 
    - Set the low power mode bits and global interrupt enable bits in the Status Register. 
    - Wait for the timer interrupt to wake up the processor and service the ISR. 

## Alternate methods
There are two libraries that can be used for this purpose using the Energia Development Environment. One for servos and one for UART. That route was not chosen in this case in order to practice and understand the program flow for MSP430 MCUs.
