#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "main.h"

extern int timer_counter[2], timer_flag[2];

void setTimer(int, int);
void timerRun();

#endif /* INC_SOFTWARE_TIMER_H_ */
