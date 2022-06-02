/*
 * main.h
 *
 *  Created on: May 21, 2022
 *      Author: eder0
 */

#ifndef MAIN_H_
#define MAIN_H_

struct flags {
    uint8_t toggle;
    uint8_t state;
};

extern struct flags led0_flag, servo0_flag, servo1_flag, servo2_flag, servo3_flag;
extern volatile uint16_t timer_count;
extern volatile uint16_t servo0_duty;
extern volatile uint16_t servo1_duty;
extern volatile uint16_t servo2_duty;
extern volatile uint16_t servo3_duty;
/*
extern const double tick_length;
extern double period;
extern double compare_reg_double;
*/

#endif /* MAIN_H_ */
