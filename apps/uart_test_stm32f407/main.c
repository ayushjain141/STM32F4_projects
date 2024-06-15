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

/*******************************************************************************
 * Macros
 *******************************************************************************/
#define USART_TX_PORT						(GPIOA)
#define USART_TX_PIN						(9)

/*******************************************************************************
 * Global Variables
 *******************************************************************************/
uint8_t tx_buff[] = "\r\n======== Hello World ========\r\n";
uint8_t tx_buf_size = sizeof(tx_buff)/sizeof(tx_buff[0]);

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

    /* Define the USART configs */
    usart_config_st_t usart1cfg = {
        .compatmode = USART_COMPATIBLE_MODE_ASYNC,
        .stopbits = USART_STOPBIT_1,
        .txrxmode = USART_TXRX_MODE_TX_EN,
        .hwflowctrl = USART_FLOWCTRL_NONE,
        .instance = USART1,
        .baudrate = 115200,
        .wordlen = USART_WORD_LEN_8_BIT,
        .oversample = USART_OVERSAMPLE_BY_16,
        .parity_en = USART_PARITY_DISABLE,
        .parity = 0
    };

    usart_config_st_t *usart1cfg_ptr = &usart1cfg;

    /* Config the USART channel */
    usart_config(usart1cfg_ptr, USART_TX_PORT, USART_TX_PIN, NULL, 0);

    /* Initialize the UART channel */
    usart_init(usart1cfg_ptr);

    for (;;)
    {
        for (uint16_t i = 0; i < tx_buf_size; i++)
        {
            /* Wait for the Transmit buffer to be ready to accept data safely */
            while (!(usart1cfg_ptr->instance->SR & (1U << 7)));
            usart1cfg_ptr->instance->DR = tx_buff[i];
        }
        delay_ms(200);
    }
}
