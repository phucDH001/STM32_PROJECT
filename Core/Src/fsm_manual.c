#include "fsm_manual.h"

void fsm_manual_run() {
	char str[10];
	switch (status) {
		case MAN_RED:
			HAL_GPIO_WritePin(GPIOA, LED1_A_Pin | LED1_B_Pin, SET);
			HAL_GPIO_WritePin(GPIOB, LED2_A_Pin, SET);
			HAL_GPIO_WritePin(GPIOC, LED2_B_Pin, SET);
			lcd_put_cur(1, 0);
			lcd_send_string("RED:");
			lcd_put_cur(1, 4);
			sprintf(str, "%02d", timer);
			lcd_send_string(str);
			if (isButtonPressed(0) == 1) {
				clearAllLed();
				status = MAN_AMBER;
				timer = amber;
				mode = 3;
				lcd_put_cur(1, 13);
				lcd_send_string("   ");
			}
			if (isButtonPressed(1) == 1) {
				if (timer < 99) timer++;
				else {
					lcd_put_cur(1, 4);
					lcd_send_string("  ");
					timer = 1;
				}
			}
			if (isButtonPressed(2) == 1) {
				red = timer;
				lcd_put_cur(1, 13);
				lcd_send_string("OK!");
			}
			break;
		case MAN_AMBER:
			HAL_GPIO_WritePin(GPIOA, LED1_A_Pin, RESET);
			HAL_GPIO_WritePin(GPIOA, LED1_B_Pin, SET);
			HAL_GPIO_WritePin(GPIOB, LED2_A_Pin, SET);
			HAL_GPIO_WritePin(GPIOC, LED2_B_Pin, RESET);
			lcd_put_cur(1, 0);
			lcd_send_string("AMBER:");
			lcd_put_cur(1, 6);
			sprintf(str, "%02d", timer);
			lcd_send_string(str);
			if (isButtonPressed(0) == 1) {
				clearAllLed();
				status = MAN_GREEN;
				timer = green;
				mode = 4;
				lcd_put_cur(1, 13);
				lcd_send_string("   ");
			}
			if (isButtonPressed(1) == 1) {
				if (timer < 99) timer++;
				else {
					lcd_put_cur(1, 6);
					lcd_send_string("  ");
					timer = 1;
				}
			}
			if (isButtonPressed(2) == 1) {
				amber = timer;
				lcd_put_cur(1, 13);
				lcd_send_string("OK!");
			}
			break;
		case MAN_GREEN:
			HAL_GPIO_WritePin(GPIOA, LED1_A_Pin, SET);
			HAL_GPIO_WritePin(GPIOA, LED1_B_Pin, RESET);
			HAL_GPIO_WritePin(GPIOB, LED2_A_Pin, RESET);
			HAL_GPIO_WritePin(GPIOC, LED2_B_Pin, SET);
			lcd_put_cur(1, 0);
			lcd_send_string("GREEN:");
			lcd_put_cur(1, 6);
			sprintf(str, "%02d", timer);
			lcd_send_string(str);
			if (isButtonPressed(0) == 1) {
				if (red == amber + green) {
					status = INIT;
					manual = 0;
					lcd_clear();
				}
				else {
					clearAllLed();
					lcd_clear();
					status = MAN_RED;
					timer = red;
					mode = 2;
				}
			}
			if (isButtonPressed(1) == 1) {
				if (timer < 99) timer++;
				else {
					lcd_put_cur(1, 6);
					lcd_send_string("  ");
					timer = 1;
				}
			}
			if (isButtonPressed(2) == 1) {
				green = timer;
				lcd_put_cur(1, 13);
				lcd_send_string("OK!");
			}
			break;
		default:
			break;
	}
}
