/*
 * leds.c
 *
 *  Created on: Dec 6, 2019
 *      Author: Piotr Kozimor
 */

#include "leds.h"

void LED_turn_on(GPIO_TypeDef port, uint16_t pin){
	HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
}

void LED_turn_off(GPIO_TypeDef port, uint16_t pin){
	HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
}
