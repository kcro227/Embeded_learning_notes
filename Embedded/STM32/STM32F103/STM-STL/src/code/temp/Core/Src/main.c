#include "stm32f10x.h"
#include "usart.h"
#include "delay.h"
#include "string.h"
#include "led.h"

void main(void)
{

    uart_init(115200); //初始化串口
    PrintfInit(USART1); //重定向printf到USART1

    delay_init();//初始化延迟函数
    LED_Init();//初始化LED，PA8
    while(1){
        LED_Blink(500);//LED以500ms为间隔闪烁
    }
}
