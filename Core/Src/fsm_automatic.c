#include "fsm_automatic.h"

void fsm_automatic_run() {
	switch (status) {
		case INIT:
			status = RED_GREEN;
			timer = red;
			timer1 = green;
			mode = 1;
			red_green = 1, red_amber = 0, green_red = 0, amber_red = 0;
			setTimer(1, 1000);
			setTimer(0, timer1 * 1000);
			break;
		case RED_GREEN:
			HAL_GPIO_WritePin(GPIOA, LED1_A_Pin | LED1_B_Pin, SET);
			HAL_GPIO_WritePin(GPIOB, LED2_A_Pin, RESET);
			HAL_GPIO_WritePin(GPIOC, LED2_B_Pin, SET);
			if (timer_flag[0] == 1) {
				status = RED_AMBER;
				timer = red - green;
				timer1 = amber;
				red_green = 0, red_amber = 1, green_red = 0, amber_red = 0;
				setTimer(1, 1000);
				setTimer(0, timer1 * 1000);
			}
			if (isButtonPressed(0) == 1) {
				clearAllLed();
				lcd_clear();
				status = MAN_RED;
				timer = red;
				mode = 2;
				manual = 1;
				red_green = 0, red_amber = 0, green_red = 0, amber_red = 0;
				setTimer(2, 250);
			}
			break;
		case RED_AMBER:
			HAL_GPIO_WritePin(GPIOA, LED1_A_Pin | LED1_B_Pin, SET);
			HAL_GPIO_WritePin(GPIOB, LED2_A_Pin, SET);
			HAL_GPIO_WritePin(GPIOC, LED2_B_Pin, RESET);
			if (timer_flag[0] == 1) {
				status = GREEN_RED;
				timer = green;
				timer1 = red;
				red_green = 0, red_amber = 0, green_red = 1, amber_red = 0;
				setTimer(1, 1000);
				setTimer(0, timer * 1000);
			}
			if (isButtonPressed(0) == 1) {
				clearAllLed();
				lcd_clear();
				status = MAN_RED;
				timer = red;
				mode = 2;
				manual = 1;
				red_green = 0, red_amber = 0, green_red = 0, amber_red = 0;
				setTimer(2, 250);
			}
			break;
		case GREEN_RED:
			HAL_GPIO_WritePin(GPIOA, LED1_A_Pin, SET);
			HAL_GPIO_WritePin(GPIOA, LED1_B_Pin, RESET);
			HAL_GPIO_WritePin(GPIOB, LED2_A_Pin, SET);
			HAL_GPIO_WritePin(GPIOC, LED2_B_Pin, SET);
			if (timer_flag[0] == 1) {
				status = AMBER_RED;
				timer = amber;
				timer1 = red - green;
				red_green = 0, red_amber = 0, green_red = 0, amber_red = 1;
				setTimer(1, 1000);
				setTimer(0, timer * 1000);
			}
			if (isButtonPressed(0) == 1) {
				clearAllLed();
				lcd_clear();
				status = MAN_RED;
				timer = red;
				mode = 2;
				manual = 1;
				red_green = 0, red_amber = 0, green_red = 0, amber_red = 0;
				setTimer(2, 250);
			}
			break;
		case AMBER_RED:
			HAL_GPIO_WritePin(GPIOA, LED1_A_Pin, RESET);
			HAL_GPIO_WritePin(GPIOA, LED1_B_Pin, SET);
			HAL_GPIO_WritePin(GPIOB, LED2_A_Pin, SET);
			HAL_GPIO_WritePin(GPIOC, LED2_B_Pin, SET);
			if (timer_flag[0] == 1) {
				status = INIT;
			}
			if (isButtonPressed(0) == 1) {
				clearAllLed();
				lcd_clear();
				status = MAN_RED;
				timer = red;
				mode = 2;
				manual = 1;
				red_green = 0, red_amber = 0, green_red = 0, amber_red = 0;
				setTimer(2, 250);
			}
			break;
		default:
			break;
	}
}
