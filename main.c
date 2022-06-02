#include <msp430.h> 
#include <stdint.h>
#include "main.h"
#include "msp430_timera.h"
#include "msp430_uart.h"
#include "msp430_led.h"
#include "msp430_servo.h"

struct flags led0_flag, servo0_flag, servo1_flag, servo2_flag, servo3_flag;

volatile uint16_t servo0_duty = 33;
volatile uint16_t servo1_duty = 16;
volatile uint16_t servo2_duty = 65;
volatile uint16_t servo3_duty = 32;
/**
 * main.c
 */
int main(void)
{
	const uint16_t counter_x = 500;
	uint8_t received_byte = 0xff;
    WDTCTL  = WDTPW | WDTHOLD;   // stop watchdog timer
    BCSCTL1 =   CALBC1_16MHZ; //set range to 16MHz
    DCOCTL  =   CALDCO_16MHZ; //set DCO step + modulation
    BCSCTL2 &= 0xF0;
    uart_init();
    led_init();
    servo_init();
    timera_cc_init(counter_x);

    while(1)
    {


        if(servo0_flag.toggle == 1)
        {
            servo0_flag.toggle = 0;
            servo0_toggle();
        }

        if(servo1_flag.toggle == 1)
        {
            servo1_flag.toggle = 0;
            servo1_toggle();
        }

        if(servo2_flag.toggle == 1)
         {
             servo2_flag.toggle = 0;
             servo2_toggle();
         }

        if(servo3_flag.toggle == 1)
         {
             servo3_flag.toggle = 0;
             servo3_toggle();
         }

        received_byte = uart_rd_char();
        switch(received_byte)
        {
        case 'd'    :
            if(servo0_duty < 65)
                servo0_duty++;
            break;
        case 'a'    :
            if(servo0_duty > 32)
                servo0_duty--;
            break;
        case 'w'    :
            if(servo1_duty < 65)
                servo1_duty++;
            break;
        case 's'    :
            if(servo1_duty > 32)
                servo1_duty--;
            break;

        case 'l'    :
            if(servo2_duty < 65)
                servo2_duty++;
            break;
        case 'j'    :
            if(servo2_duty > 32)
                servo2_duty--;
            break;
        case 'i'    :
            if(servo3_duty < 65)
                servo3_duty++;
            break;
        case 'k'    :
            if(servo3_duty > 32)
                servo3_duty--;
            break;

        }
        __bis_SR_register(LPM0_bits | GIE); //enable the global interrupt and go to sleep
    }
}


