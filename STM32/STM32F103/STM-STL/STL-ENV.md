# ���

��ƪΪSTM32F103��ѧϰ�ʼǣ�����֮������ָ����лл��


# 1.�����
## 1.1 Ӳ��׼��

- STM32F103RCT6��Сϵͳ��

## 1.2 ���׼��
���������ڶ�̳̰���ԭ�Ӹ�Ľ̳����ڣ�������keil5�����п��������ǿ��ǵ��Ժ��ѧϰ�����Ӹ��ӵĿ��������������Ҿ���ʹ��Clion + cmake���п�����
## 1.3 ���������

- ��װClion

> Clion�İ�װ�ҾͲ�������׸���ˣ����Ͻ̳̺ܶࡣ

��������
> - [arm-gcc ������](https://developer.arm.com/downloads/-/gnu-rm) ����.zip��ʽ
> - [OPEN-OCD](https://gnutoolchains.com/arm-eabi/openocd/)

����������ѹ���ļ��У���÷���ͳһ��toolchains�ļ����£��������
1.��Clion������ļ�->����->������ִ�С�����->������
![](./src/img/1.png)
�ڹ��������½�mingw-stm32��Ȼ�󹤾߼�ѡMingw����������ѡmingw��cmake.exe��C������ѡ���ص�arm-gcc,C++ͬ�����������ģ�Ȼ��Ӧ�á�
![](./src/img/2.png)
���ļ�->����->������ִ�С�����->Ƕ��ʽ�����У�ѡ��openocd��λ�ã����Ӧ�á�

## 1.4 �����ļ�
������[STM32/STM32F103/src/code](./src/code/temp)Ŀ¼�£���Clion��Ŀ¼����Ҫ�޸�`CMakeLists.txt`�ļ�����ͼ��
![](./src/img/3.png)
��Ҫ�޸Ĺ�����Ϊ���Լ���װ��λ�á��޸ĺ����¼���CmakeList.txt��Ȼ����ܱ����ˡ�
�������û����������м��������λ�ú� ```C:/windows/system32```
�磺```PATH=F:\stm32\gcc-arm-none-eabi-10.3-2021.10\bin\;C:/windows/system32```
![](./src/img/6.png)

## 1.5 Printf�ض�������

��STM32F103�У�printf����Ĭ����ʹ��USART1����ӡ�ģ���keil������fputc�������ɴ�ӡ�������ݣ�������CLion�£��������ӵ�stdio.h��ͬ����Ҫ���صĺ���Ҳ��̫һ����������ԭ�ӵ�STM32F103��׼����Ϊ������USART.c�У��޸���ͼ��
![](./src/img/4.png)

�������£�
``` #if !defined(OS_USE_SEMIHOSTING)

#define STDIN_FILE_NO 0
#define STDOUT_FILE_NO 1
#define STDERR_FILE_NO 2

USART_TypeDef *G_uart;

void PrintfInit(USART_TypeDef *uarTx) {
    G_uart = uarTx;
    /* Disable I/O buffering for STDOUT stream, so that
     * chars are sent out as soon as they are printed. */
    setvbuf(stdout, NULL, _IONBF, 0);
}
int _isatty(int fd) {
    if (fd >= STDIN_FILE_NO && fd <= STDERR_FILE_NO)
        return 1;
    return 0;
}
int _write(int fd, char *ptr, int len) {
    if (fd == STDOUT_FILE_NO || fd == STDERR_FILE_NO) {
        uint32_t i;
        for (i = 0; i < len; i++) {
            USART_SendData(G_uart, ptr[i]);

            while (USART_GetFlagStatus(G_uart, USART_FLAG_TXE) == RESET);
        }
        while (USART_GetFlagStatus(G_uart, USART_FLAG_TC) == RESET);

        return len;

    }
    return -1;
}
int _close(int fd) {
    if (fd >= STDIN_FILE_NO && fd <= STDERR_FILE_NO)
        return 0;
    return -1;
}
int _lseek(int fd, int ptr, int dir) {
    (void) fd;
    (void) ptr;
    (void) dir;
    return -1;
}

int _read(int fd, char *ptr, int len) {
    if (fd == STDIN_FILE_NO) {
        while (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET) {
        }
        *ptr = USART_ReceiveData(USART2);
        return 1;
    }
    return -1;
}

#endif //#if !defined(OS_USE_SEMIHOSTING)
```
�޸�USART.h�����һЩ���壺
![](./src/img/5.png)
�������£�
```
#ifndef __USART_H
#define __USART_H
#include "stdio.h"
#include "sys.h"

#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����

extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з�
extern u16 USART_RX_STA;         		//����״̬���
//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 bound);
//���ڷ�������



void PrintfInit(USART_TypeDef *uarTx);

int _isatty(int fd);

int _write(int fd, char *ptr, int len);

int _close(int fd);

int _lseek(int fd, int ptr, int dir);

int _read(int fd, char *ptr, int len);
void USART_SEND(USART_TypeDef* USARTx,u8 *buf);
#endif
```
��main.c����Ҫ����```PrintfInit(USART1)```;ʹUSART1�ܹ�ʹ��printf������


