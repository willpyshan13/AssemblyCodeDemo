#ifndef USART_H
#define USART_H
#include "User_Def.h"

void UART_Config(void);
void SendData(u8 dat);
void SendString(char *s);
void Uart_Send_Data(char *s, uchar len);


#endif