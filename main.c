#include <msp430.h> 
#include <stdint.h>
#include "msp430_timera.h"


volatile uint8_t timer_count = 0;
/**
 * main.c
 */
int main(void)
{
    const uint16_t x = 50000; //set the capture compare register to 1/20 of a second assuming having a 1MHz clk
    BCSCTL1 =   CALBC1_1MHZ; //set range to 1MHz
    DCOCTL  =   CALDCO_1MHZ; //set DCO step + modulation
    BCSCTL2 &= 0xF0;
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1DIR |= 0x01; //p1.1 is output
    timera_cc_init(x);
    _BIS_SR(LPM0_bits | GIE); //enable the global interrupt



    while(1)
    {


    }
}

#pragma vector = TIMER0_A0_VECTOR
interrupt void TIMERA0_interrupt(void)
{
    timer_count++;
    if(timer_count >= 20)
    {
        timer_count = 0;
        P1OUT ^= 0x01;
    }

}
