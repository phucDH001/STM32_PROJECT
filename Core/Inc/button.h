#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define NORMAL_STATE SET
#define PRESSED_STATE RESET

int isButtonPressed(int);
void getKeyInput();

#endif /* INC_BUTTON_H_ */
