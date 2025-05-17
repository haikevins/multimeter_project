#include "uart.h"
#include "stdio.h"
#include "gpio.h"

char uart_buffer[100];
uint32_t uart_index = 0;

/*
		Cau hinh UART1:
		- Toc do baud 9600
		- TX: PA9 (Push-Pull)
		- RX: PA10 (Input Floating)
		- Kich hoat clock cho GPIOA va USART1
*/
void Uart_Config(uint16_t baudrate)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	USART_InitTypeDef uart;
	
	// TX - PA9
	Gpio_Config(GPIOA, GPIO_Pin_9, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);
	
	// RX - PA10
	Gpio_Config(GPIOA, GPIO_Pin_10, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
	
	uart.USART_BaudRate = baudrate;
	uart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	uart.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	uart.USART_Parity = USART_Parity_No;
	uart.USART_StopBits = USART_StopBits_1;
	uart.USART_WordLength = USART_WordLength_8b;
	
	USART_Init(USART1, &uart);
	USART_Cmd(USART1, ENABLE);
}

/*
		Gui 1 ky tu qua UART1

		Tham so:
		- chr: ky tu can gui
*/
void Uart_Send_Char(char chr)
{
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	USART_SendData(USART1, chr);
}

/*
		Gui mot chuoi ky tu qua UART1

		Tham so:
		- str: con tro den chuoi ky tu can gui (ket thuc bang NULL)
*/
void Uart_Send_String(char *str)
{
	while(*str)
	{
		Uart_Send_Char(*str++);
	}
}

/*
		Gui mot so nguyen duoi dang chuoi qua UART1

		Tham so:
		- num: so nguyen can gui
*/
void Uart_Send_Digit(int num)
{
	char buffer[12];
	sprintf(buffer, "%d", num);
	Uart_Send_String(buffer);
}

/*
    Gui mot so dang hex qua UART1 (2 ky tu cho 8-bit, 4 ky tu cho 16-bit)

    Tham so:
    - num: so can gui (uint8_t hoac uint16_t)
*/
void Uart_Send_Hex(uint16_t num)
{
    char hex_buffer[5]; // 4 ky tu hex + null terminator

    // Chuyen so sang chuoi hex, them so 0 o dau neu can
    sprintf(hex_buffer, "%04X", num);

    // Gui chuoi hex qua UART
    Uart_Send_String(hex_buffer);
}

/*
		Trinh xu ly ngat USART1

		Khi co du lieu den tu UART:
		- Neu ky tu la '!', luu vao buffer va tang index
		- Neu khong phai '!', reset buffer ve 0
*/
void USART1_IRQHandler()
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		char char_received = USART_ReceiveData(USART1);
		if(char_received != '!')
		{
			uart_buffer[uart_index] = NULL;
			uart_index = 0;
		}
		else
		{
			uart_buffer[uart_index++] = char_received;
		}
	}
}
