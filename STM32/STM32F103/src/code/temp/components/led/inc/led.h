//
// Created by Administrator on 2024/2/2.
//

#ifndef TEMPLATEF103_LED_H
#define TEMPLATEF103_LED_H

#include "sys.h"

#define USE_FRTOS 0
#define LED_PIN GPIO_Pin_8
#define LED_PORT GPIOA

#define LED_ON() GPIO_WriteBit(LED_PORT,LED_PIN,RESET)
#define LED_OFF() GPIO_WriteBit(LED_PORT,LED_PIN,SET)


void LED_Init();
void LED_Blink(uint16_t ms);
#endif //TEMPLATEF103_LED_H
