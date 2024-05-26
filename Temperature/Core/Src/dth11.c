/*
 * dth11.c
 *
 *  Created on: May 2, 2024
 *      Author: andre
 */
#include "main.h"
void Dht11_Start() {
	Set_Pin_Output();
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
	delay(18000);
	Set_Pin_Input();
}

void Dht11_Read(uint8_t* data) {
	for(int i = 0; i < 40; i++) {
		//esperar para sair de nível baixo
		while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9) == GPIO_PIN_RESET);
		__HAL_TIM_SET_COUNTER(&htim3, 0);
		while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9) == GPIO_PIN_SET);
		//checar tempo em us que saiu de nivel alto
		uint16_t tempo = __HAL_TIM_GET_COUNTER(&htim3);
		if(tempo >= 20 && tempo <= 30) {
			data[i/8] &= ~(1 << (7 - (i % 8)));
		} else if(tempo >= 60 && tempo <= 70) {
			data[i/8] |= (1 << (7 - (i % 8)));
		}
	}
}
