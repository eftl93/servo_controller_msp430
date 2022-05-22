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

extern struct flags led1_flag, servo1_flag, servo2_flag, servo3_flag, servo4_flag;
extern volatile uint8_t timer_count;

#endif /* MAIN_H_ */
