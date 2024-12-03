#include "global.h"

int status = 0;
int red = 5, amber = 2, green = 3;
int timer = 0, timer1 = 0, mode = 1, manual = 0;
int red_green, red_amber, green_red, amber_red;

void clearAllLed() {
	HAL_GPIO_WritePin(GPIOA, LED1_A_Pin | LED1_B_Pin, RESET);
	HAL_GPIO_WritePin(GPIOB, LED2_A_Pin, RESET);
	HAL_GPIO_WritePin(GPIOC, LED2_B_Pin, RESET);
}
