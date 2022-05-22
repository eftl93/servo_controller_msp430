/*
 * timera.c
 *
 *  Created on: May 21, 2022
 *      Author: eder0
 */
#include <msp430.h>
#include <stdint.h>
#include "msp430_timera.h"

void timera_cc_init(uint16_t capt_comp)
{
    TACTL |= 0x0200; //TASSEL = 01; SOURCE CLK IS ACLK## 0b10 for SMCLK
    TACTL |= 0x0010; //MCx = 01; Mode control is "UP MODE" (counts up to TACCR0)
    TACCR0 = capt_comp; //set the number of counts for the timer to interrupt
    TACTL |= 0x0004; //TACLR = 1 We do this to let it know we want to change TIMERA setting and get started
    TACCTL0 |= 0x0010; // CCIE = 1 ; enable the interrupt
}

