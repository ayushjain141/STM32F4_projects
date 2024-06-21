/*******************************************************************************
* File Name:	main.c
*
* Description:	This is the source code for the UART peripheral test application
* for STM32F407 MCU.
*
* Related Document: See README.md
*
*******************************************************************************/
#include "stm32f4xx.h"
#include "stm32f407xx.h"
#include "bsp_aj_stm32f4.h"
#include "usart_aj_stm32f4.h"
#include "delay_aj_stm32f4.h"
#include <stdio.h>

/*******************************************************************************
 * Macros
 *******************************************************************************/
#define USART_TX_PORT						(GPIOA)
#define USART_TX_PIN						(9)
#define USART_RX_PORT						(GPIOA)
#define USART_RX_PIN						(10)

/*******************************************************************************
 * Global Variables
 *******************************************************************************/
const uint8_t rx_buff_size = 1;
uint8_t rx_buff[rx_buff_size] = {0};

usart_config_st_t usart1cfg;
usart_config_st_t *usart1cfg_ptr;

struct __FILE
{
  int dummyVar; //Just for the sake of redefining __FILE, we won't we using it anyways ;)
};

FILE __stdout; //STDOUT
FILE __stdin;  //STDIN

/*******************************************************************************
 * Function Name: fputc()
 *******************************************************************************
 * Summary:
 *  Defines the "fputc" function used in "printf". Here the "fputc" is implemented
 *  to work with UART transmit function.
 *
 * Parameters:
 *	ch:				Character to be printed, is typecasted to char type for uart
 *					transmit.
 *  stream			File stream to send the output to. Not used in case of
 *					printf using uart.
 *
 * Return :
 *  int				Returns the printed character on success.
 *
 ******************************************************************************/
int fputc(int ch, FILE * stream)
{
  uart_transmit_blocking(usart1cfg_ptr, (uint8_t *)&ch, rx_buff_size, 0);
  return ch;
}

/*******************************************************************************
 * Function Name: main()
 *******************************************************************************
 * Summary:
 *  This is the main function. It prints a message on the serial terminal using
 *  re-targeted printf().
 *
 * Parameters:
 *
 * Return :
 *  int
 *
 ******************************************************************************/
int main()
{
    /* Initialize the BSP */
    stm32f4_bsp_init();

    /* Define the USART configs. */
    usart1cfg.compatmode = USART_COMPATIBLE_MODE_ASYNC;
	usart1cfg.stopbits = USART_STOPBIT_1;
	usart1cfg.txrxmode = USART_TXRX_MODE_RX_TX_BOTH_EN;
	usart1cfg.hwflowctrl = USART_FLOWCTRL_NONE;
	usart1cfg.instance = USART1;
	usart1cfg.baudrate = 115200;
	usart1cfg.wordlen = USART_WORD_LEN_8_BIT;
	usart1cfg.oversample = USART_OVERSAMPLE_BY_16;
	usart1cfg.parity_en = USART_PARITY_DISABLE;
	usart1cfg.parity = 0;

    usart1cfg_ptr = &usart1cfg;

    /* Config the USART channel. */
    usart_config(usart1cfg_ptr, USART_TX_PORT, USART_TX_PIN, USART_RX_PORT, USART_RX_PIN);

    /* Initialize the USART channel. */
    usart_init(usart1cfg_ptr);

	/* Clear screen and move cursor to terminal's home position (0,0). */
	printf("\x1b[1J\x1b[H");

	/* Print Hello world message, an integer and a float value. */
	printf("===========================================\r\n");
	printf("Hello world, int = %d, float = %f\r\n", 141, 235.89324);
	printf("===========================================\r\n");

	while(1);
}
