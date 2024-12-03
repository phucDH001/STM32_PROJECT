#include "button.h"

uint16_t btnPinArr[] = {BUTTON_1_Pin, BUTTON_2_Pin, BUTTON_3_Pin};
GPIO_TypeDef *btnPortArr[] = {BUTTON_1_GPIO_Port, BUTTON_2_GPIO_Port, BUTTON_3_GPIO_Port};

int KeyReg0[3] = {NORMAL_STATE};
int KeyReg1[3] = {NORMAL_STATE};
int KeyReg2[3] = {NORMAL_STATE};
int KeyReg3[3] = {NORMAL_STATE};

int TimeOutForKeyPress[3] = {100, 100, 100};
int button_flag[3] = {0};

int isButtonPressed(int idx) {
	if (button_flag[idx] == 1) {
		button_flag[idx] = 0;
		return 1;
	}
	return 0;
}

void getKeyInput() {
	for (int i = 0; i < 3; i++) {
		KeyReg0[i] = KeyReg1[i];
		KeyReg1[i] = KeyReg2[i];
		KeyReg2[i] = HAL_GPIO_ReadPin(btnPortArr[i], btnPinArr[i]);
		if ((KeyReg0[i] == KeyReg1[i]) && (KeyReg1[i] == KeyReg2[i])) {
			if (KeyReg3[i] != KeyReg2[i]) {
				KeyReg3[i] = KeyReg2[i];
				if (KeyReg2[i] == PRESSED_STATE) {
					TimeOutForKeyPress[i] = 15;
					button_flag[i] = 1;
				}
			}
			else {
				TimeOutForKeyPress[i]--;
				if (TimeOutForKeyPress[i] == 0) {
					KeyReg3[i] = NORMAL_STATE;
				}
			}
		}
	}
}
