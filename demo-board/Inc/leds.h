#ifndef __LEDS__H_
#define __LEDS__H_

#include "main.h"
#include "stm32f3xx_hal.h"

#define LED1 LED1_GPIO_Port, LED1_Pin
#define LED2 LED2_GPIO_Port, LED2_Pin
#define LED3 LED3_GPIO_Port, LED3_Pin
#define LED_TEST LD2_GPIO_Port, LD2_Pin

void LED_turn_on(GPIO_TypeDef*, uint16_t);
void LED_turn_off(GPIO_TypeDef*, uint16_t);

#endif
