
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include "stm32f10x.h"

#define LEDPORT (GPIOC)
#define LEDPIN (GPIO_Pin_13)
#define ENABLE_GPIO_CLOCK (RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE))


/* timing is not guaranteed :) */
void simple_delay(uint32_t us)
{
	/* simple delay loop */
	while (us--)
    {
		asm volatile ("nop");
	}
}


int main(void)
{
    //Step 1: Enable the clock to PORT B
    // RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    GPIO_InitTypeDef GPIO_InitStructure;
    //Step 2: Change PB0's mode to 0x3 (output) and cfg to 0x0 (push-pull)
    // GPIOB->CRL = GPIO_CRL_MODE0_0 | GPIO_CRL_MODE0_1;
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    ENABLE_GPIO_CLOCK;
    /* Configure PD0 and PD2 in output pushpull mode */
    GPIO_InitStructure.GPIO_Pin = LEDPIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(LEDPORT, &GPIO_InitStructure);

    while (1)
    {
		GPIO_SetBits(LEDPORT, LEDPIN);
		/* delay */
		simple_delay(100000);
		/* clear led */
		GPIO_ResetBits(LEDPORT, LEDPIN);
		/* delay */
		simple_delay(100000);
    }
    return 0;
}
