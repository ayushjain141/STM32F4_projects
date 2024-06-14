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

/*******************************************************************************
 * Macros
 *******************************************************************************/


/*******************************************************************************
 * Global Variables
 *******************************************************************************/
uint8_t tx_buff[] = "Hello Ayush Jain\r\nThis message is from STM32 USART1\r\n\n";
uint8_t tx_buf_siz = sizeof(tx_buff)/sizeof(tx_buff[0]);

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

	/* Enable UART1's GPIO clock */
	RCC->AHB1ENR |= (1U << 0);

	/* Enable UART1's clock */
    RCC->APB2ENR |= (1U << 4);

    // PA9 AF mode.
	GPIOA->MODER |= ((GPIOA->MODER & (~(0xFU << 18))) | (0x2U << 18));

    // PA9(TX) set to push-pull
    GPIOA->OTYPER |= ((GPIOA->OTYPER & (~(1U << 9))));

    // set max output speed on PA9
    GPIOA->OSPEEDR |= ((GPIOA->OSPEEDR & (~(0x3U << 18))) | (0x3U << 18));

	GPIOA->PUPDR = 0;

    // set AF function number on PA9
    GPIOA->AFR[1] |= ( (GPIOA->AFR[1] & (~(0xFFU << 4))) | (0x7U << 4));

    /*
	 * Enable Tx and Rx in UART register, no parity and no interrupts,
     * 8 bit word, USART enable, oversampling by 8
	 */
    USART1->CR1 = 0U;
	USART1->CR1 |= (1U << 3);
	USART1->CR1 |= (1U << 2) | (1U << 13);

	USART1->CR2 = 0;

    /* USARTDIV for APB2 freq = 50 MHz, and baud = 115200
     * USARTDIV complete value = 54.2534722,
	 * DIV_fraction = (16 * 0d0.2534722) = 4.055 ~ 4
     * DIV_MANTISSA = 54
    */
	USART1->BRR = 0;
    USART1->BRR |= (4U << 0) | (54U << 4);

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

    usart_config(usart1cfg_ptr);

    for(;;)
    {
        for(uint16_t i = 0; i < tx_buf_siz; i++)
        {
			/* Wait for the Transmit buffer to be ready to accept data safely */
			while( !(USART1->SR & (1U << 7)) );
            USART1->DR = tx_buff[i];
        }

        delay_ms(200);
    }
}
