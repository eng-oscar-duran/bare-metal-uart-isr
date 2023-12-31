#include <stdint.h>
#include "uart.h"

#define GPIOAEN (1U<<0)
#define UART2EN (1U<<17)

#define DGB_UART_BAUDRATE   115200
#define SYS_FREQ            16000000
#define APB1_CLK            SYS_FREQ
#define CR1_TE              (1U<<3)
#define CR1_UE              (1U<<13)
#define SR_TXE              (1U<<7)

void debug_uart_init(void)
{
    /*Enable clock access to GPIOA*/
    RCC->AHB1ENR |= GPIOAEN;

    /*Set the mode of PA2 to alternate function mode*/
    GPIOA->MODER &=~(1U<<4);
    GPIOA->MODER |=(1U<<5);
}

static void uart_write(int ch)
{
    /*Make sure transmit data register is empty*/
    while(!(USART2->SR & SR_TXE)){}
    /*Write to transmit data register*/
    USART2->DR = (ch & 0xFF);
}