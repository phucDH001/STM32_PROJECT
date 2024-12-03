#ifndef SRC_GLOBAL_H_
#define SRC_GLOBAL_H_

#include "main.h"
#include "software_timer.h"
#include "button.h"
#include "lcd_display.h"
#include <stdio.h>

#define INIT 0
#define RED_GREEN 1
#define RED_AMBER 2
#define GREEN_RED 3
#define AMBER_RED 4

#define MAN_RED 10
#define MAN_GREEN 11
#define MAN_AMBER 12

extern int status;
extern int red, amber, green;
extern int timer, timer1, mode, manual;
extern int red_green, red_amber, green_red, amber_red;

void clearAllLed();

#endif /* SRC_GLOBAL_H_ */
