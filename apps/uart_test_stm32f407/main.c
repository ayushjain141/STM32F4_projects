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

/*******************************************************************************
 * Macros
 *******************************************************************************/


/*******************************************************************************
 * Global Variables
 *******************************************************************************/
uint8_t tx_buff[] = "Hello ayush\r\n";
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
	/* Enable UART1's GPIO clock */
	RCC->AHB1ENR |= (1U << 0);

	/* Enable UART1's clock */
    RCC->APB2ENR |= (1U << 4);

    // PA9 and PA10 set to AF mode.
	GPIOA->MODER |= ((GPIOA->MODER & (~(0xFU << 18))) | (0xAU << 18));

    // PA9(TX) set to push-pull
    GPIOA->OTYPER |= ((GPIOA->OTYPER & (~(1U << 9))));

    // P10(RX) set to input open-drain.

    // set max output speed on PA9
    GPIOA->OSPEEDR |= ((GPIOA->OSPEEDR & (~(0x3U << 18))) | (0x3U << 18));
	
	GPIOA->PUPDR = 0;

    // set AF function number on PA9 and PA10
    GPIOA->AFR[1] |= ( (GPIOA->AFR[1] & (~(0xFFU << 4))) | (0x7U << 4));

    /* Enable Tx and Rx in UART register, no parity and no interrupts,
       8 bit word, USART enable, oversampling by 8 */
    USART1->CR1 = 0U; 
	USART1->CR1 |= (1U << 3);
	USART1->CR1 |= (1U << 2) | (1U << 13);

	USART1->CR2 = 0;

    /* USARTDIV for APB2 freq = 50 MHz, and baud = 115200 */

    /* 
     * USARTDIV complete value = 27.126736,  DIV_fraction = (16 * 0d0.126736) = 0d2
     * DIV_MANTISSA = 27
    */
    #if 1
	USART1->BRR = 0;
    USART1->BRR |= (4U << 0) | (54U << 4);
	#else
	USART2->BRR |= (22 << 4);
    USART2->BRR |= 13;
	#endif

    for(;;)
    {
        for(uint16_t i = 0; i < tx_buf_siz; i++)
        {
			while( !(USART1->SR >> 7 & 1U) );
            USART1->DR = tx_buff[i];
			//while( !(USART1->SR & (1U << 6)) );
        }
		for(int i=0; i<10000000; i++);
        //delay_ms(200);
    }

	//return 0;
}

