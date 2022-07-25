#include "stm32f1xx.h"
#include "clk_user.h"
#include "gpio_user.h"
#include "delay_user.h"

volatile uint8_t count = 0;

int main(void) {
	RCC->APB2ENR |= (RCC_APB2ENR_AFIOEN);
	AFIO->MAPR |= (AFIO_MAPR_TIM1_REMAP_0);
	AFIO->MAPR &= ~(AFIO_MAPR_TIM1_REMAP_1);

	clk_user();
	PORT_A_Init();

	TIM4->CR1 &= ~(TIM_CR1_DIR);
	delay(5000);

	while (1) {
		//GPIOA->ODR |= (GPIO_ODR_ODR9);
		//delay(1000);
		//GPIOA->ODR &= ~(GPIO_ODR_ODR9);
		//delay(1000);
	}

}

void TIM4_IRQHandler(void) {
	if ((TIM4->SR & TIM_SR_UIF) != 0) {
		TIM4->SR &= ~(TIM_SR_UIF);
		switch (count) {
		case 0:
			GPIOA->ODR |= (GPIO_ODR_ODR9);
			break;
		case 1:
			GPIOA->ODR &= ~(GPIO_ODR_ODR9);
			break;
		}
		count++;
		if (count > 1) {
			count = 0;
		}

	}
}

