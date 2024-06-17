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
#define USART_RX_PORT						(GPIOA)
#define USART_RX_PIN						(10)



/*******************************************************************************
 * Global Variables
 *******************************************************************************/
uint8_t tx_buff[] = "\x1b[1J\x1b[H\r\n================\r\n Hello World !!!\r\n================\r\n";
uint8_t tx_buff_size = sizeof(tx_buff)/sizeof(tx_buff[0]);

const uint8_t rx_buff_size = 1;
uint8_t rx_buff[rx_buff_size] = {0};

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
        .txrxmode = USART_TXRX_MODE_RX_TX_BOTH_EN,
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
    usart_config(usart1cfg_ptr, USART_TX_PORT, USART_TX_PIN, USART_RX_PORT, USART_RX_PIN);

    /* Initialize the USART channel */
    usart_init(usart1cfg_ptr);

    /* Transmit Hello world message */
    uart_transmit_blocking(usart1cfg_ptr, tx_buff, tx_buff_size, 0);

    delay_ms(200);

    while (1)
    {
        /* Receive single character from the keyboard press. For this the
         * size of rx_buff kept as "1". */
        uart_receive_poll(usart1cfg_ptr, rx_buff, rx_buff_size, 0);

        /* Transmit back (echo) the received character, to the serial COM port */
        uart_transmit_blocking(usart1cfg_ptr, rx_buff, rx_buff_size, 0);
    }
}
