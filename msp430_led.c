/*
 * msp430_led.c
 *
 *  Created on: May 27, 2022
 *      Author: eder0
 */
#include <msp430.h>
#include <stdint.h>
#include "msp430_led.h"
#include "main.h"

void led_init(void)
{
    P1DIR |= 0x01; //P1.0 are set as output
    P1OUT &= 0xFE;
    P2DIR |= 0x20; //P2.5 is set as output
    P2OUT &= 0xEF;
}
void led0_high(void)
{
    P2OUT |= 0x20;
}

void led0_low(void)
{
    P2OUT &= 0xDF;
}

void led0_toggle(void)
{
    P2OUT ^= 0x20;
}

void led1_high(void)
{
    P1OUT |= 0x01;

}


void led1_low(void)
{
    P1OUT &= 0xFE;
}

void led1_toggle(void)
{
    P1OUT ^= 0x01;
}
