#include "led.h"
#include "delay.h"
void LED_Init()
{
    GPIO_InitTypeDef gpioInitStructure = {0};
    gpioInitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    gpioInitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    gpioInitStructure.GPIO_Pin = LED_PIN;
    GPIO_Init(LED_PORT,&gpioInitStructure);
}

void LED_Blink(uint16_t ms)
{
    LED_ON();
#if USE_FRTOS
    delay_ms(ms);
#else
    delay_ms(ms);
#endif
    LED_OFF();
#if USE_FRTOS
    delay_ms(ms);
#else
    delay_ms(ms);
#endif
}