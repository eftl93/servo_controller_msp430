//Main file for the MSP430G2553 Servo controller
//DCO is 16MHz which is used for MCLK and SMCLK
//Frequency of signal is 50Hz
//Min Poswidth for servo is 1.0 mS which will be a count of 32 in this program
//Max Poswidth for servo is 2.0 mS which will be a count of 65 in this program

//Servo controller will receive characters through the UART peripheral
//UART is running at 115200 baud rate
//'d' character increases servo0_duty 
//'a' character decreases servo0_duty
//'w' character increases servo1_duty
//'s' character decreases servo1_duty
//'l' character increases servo2_duty 
//'j' character decreases servo2_duty
//'i' character increases servo3_duty
//'k' character decreases servo3_duty

#include <msp430.h> 
#include <stdint.h>
#include "main.h"
#include "msp430_timera.h"
#include "msp430_uart.h"
#include "msp430_led.h"
#include "msp430_servo.h"

struct flags led0_flag, led1_flag, servo0_flag, servo1_flag, servo2_flag, servo3_flag;


//servo0_duty will change the duty cycle of servo signal on pin 2.0
//servo1_duty will change the duty cycle of servo signal on pin 2.1
//servo2_duty will change the duty cycle of servo signal on pin 2.2
//servo3_duty will change the duty cycle of servo signal on pin 2.3
uint16_t servo0_duty = NEUTRAL_DUTY;
uint16_t servo1_duty = NEUTRAL_DUTY;
uint16_t servo2_duty = NEUTRAL_DUTY;
uint16_t servo3_duty = NEUTRAL_DUTY;


int main(void)
{
	uint8_t received_byte = 0xff;    
    WDTCTL  = WDTPW | WDTHOLD;       //stop watchdog timer
    BCSCTL1 =   CALBC1_16MHZ;        //set internal clock range to 16MHz
    DCOCTL  =   CALDCO_16MHZ;        //set DCO step | modulation
    BCSCTL2 &= 0xF0;                 //Ensure that DCO resistor is internal | Divider for SMCLK /1
    uart_init();
    led_init();
    servo_init();
    timera_cc_init(COUNTER_COMPARE);

    while(1)
    {
//After each timer interrupt, CPU wakes up and runs once before going back to sleep
//check if any servo flag has been updated and clear/set its signal accordingly
        if(servo0_flag.set)
         {
             servo0_flag.set = 0;
             servo0_set();
         }

         if(servo1_flag.set)
         {
             servo1_flag.set = 0;
             servo1_set();
         }

         if(servo2_flag.set)
          {
              servo2_flag.set = 0;
              servo2_set();
          }

         if(servo3_flag.set)
          {
              servo3_flag.set = 0;
              servo3_set();
          }

         if(servo0_flag.clear)
          {
              servo0_flag.clear = 0;
              servo0_clear();
          }

          if(servo1_flag.clear)
          {
              servo1_flag.clear = 0;
              servo1_clear();
          }

          if(servo2_flag.clear)
           {
               servo2_flag.clear = 0;
               servo2_clear();
           }

          if(servo3_flag.clear)
           {
               servo3_flag.clear = 0;
               servo3_clear();
           }

          if(led0_flag.toggle)
          {
              led0_flag.toggle = 0;
              led0_toggle();
          }

          if(led1_flag.toggle)
          {
              led1_flag.toggle = 0;
              led1_toggle();
          }
//after each timer interrupt and updating the servo signals, check if a new command has arrived through uart
//and update the duty_cycle variable accordingly
        received_byte = uart_rd_char();
        switch(received_byte)
        {
        case 'd'    :
            if(servo0_duty < MAX_DUTY)
                servo0_duty++;
            break;
        case 'a'    :
            if(servo0_duty > MIN_DUTY)
                servo0_duty--;
            break;
        case 'w'    :
            if(servo1_duty < MAX_DUTY)
                servo1_duty++;
            break;
        case 's'    :
            if(servo1_duty > MIN_DUTY)
                servo1_duty--;
            break;

        case 'l'    :
            if(servo2_duty < MAX_DUTY)
                servo2_duty++;
            break;
        case 'j'    :
            if(servo2_duty > MIN_DUTY)
                servo2_duty--;
            break;
        case 'i'    :
            if(servo3_duty < MAX_DUTY)
                servo3_duty++;
            break;
        case 'k'    :
            if(servo3_duty > MIN_DUTY)
                servo3_duty--;
            break;
        }
//Enable the global interrupt and go to sleep to wait to be waken up by the TimerA interrupt
        __bis_SR_register(LPM0_bits | GIE);
    }
}
