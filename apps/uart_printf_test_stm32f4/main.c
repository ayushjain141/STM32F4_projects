/*******************************************************************************
* File Name:    main.c
*
* Description:  This is the source code for the UART peripheral test application
* for STM32F407 MCU.
*
* Related Document: See README.md
*
*******************************************************************************/
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f407xx.h"
#include "bsp_aj_stm32f4.h"
#include "usart_aj_stm32f4.h"
#include "delay_aj_stm32f4.h"
#include "retarget_stdio_aj_stm32f4.h"

/*******************************************************************************
 * Macros
 *******************************************************************************/
#define USART_TX_PORT                       (GPIOA)
#define USART_TX_PIN                        (9)
#define USART_RX_PORT                       (GPIOA)
#define USART_RX_PIN                        (10)

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

    printf_retarget_uart_init();

    /* Clear screen and move cursor to terminal's home position (0,0). */
    printf("\x1b[1J\x1b[H");

    /* Print Hello world message, an integer and a float value. */
    printf("----------------------------------------------\r\n");
    printf("Hello World !!!   int = %d, float = %f\r\n", 141, 235.89324);
    printf("----------------------------------------------\r\n");

    while (1);
}
