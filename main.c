#include <msp430.h> 
#include <stdint.h>
#include "main.h"
#include "msp430_timera.h"
#include "msp430_uart.h"



struct flags led1_flag, servo1_flag, servo2_flag, servo3_flag, servo4_flag;



/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    const uint16_t x = 50000; //set the capture compare register to 1/20 of a second assuming having a 1MHz clk
    BCSCTL1 =   CALBC1_1MHZ; //set range to 1MHz
    DCOCTL  =   CALDCO_1MHZ; //set DCO step + modulation
    BCSCTL2 &= 0xF0;
    P1DIR |= 0x01; //p1.1 is output
    timera_cc_init(x);


    while(1)
    {
        if(led1_flag.toggle == 1)
        {
            led1_flag.toggle = 0;
            P1OUT ^= 0x01;
        }

        _BIS_SR(LPM0_bits | GIE); //enable the global interrupt and go to sleep
    }
}


