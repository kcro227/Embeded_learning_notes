#ifndef __USART_H
#define __USART_H

#include "stdio.h"
#include "sys.h"

#define USART_REC_LEN            200    //定义最大接收字节数 200
#define EN_USART1_RX            1        //使能（1）/禁止（0）串口1接收
#define USE_USART_REC_IRQn       0      //使能（1）/禁止（0） 0使用stdio.h的scanf函数接收 1为正点原子的接收协议
#define USE_PRINTF 1                //使用printf

extern u8 USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
extern u16 USART_RX_STA;                //接收状态标记
//如果想串口中断接收，请不要注释以下宏定义
void uart_init(u32 bound);
//串口发送数组


void PrintfInit(USART_TypeDef *uarTx);

#if USE_PRINTF

int _isatty(int fd);

int _write(int fd, char *ptr, int len);

int _close(int fd);

int _lseek(int fd, int ptr, int dir);

int _read(int fd, char *ptr, int len);

#endif

void USART_SEND(USART_TypeDef *USARTx, u8 *buf);

#endif


