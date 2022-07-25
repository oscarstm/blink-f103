/*
 * delay_user.c
 *
 *  Created on: Jul 13, 2022
 *      Author: oscar
 */

#include "delay_user.h"

void delay(uint16_t ms) {
	if (ms == 0) {
		return;
	}
	/*
	 * Counter settings
	 */
	RCC->APB1ENR |= (RCC_APB1ENR_TIM4EN);

	TIM4->CR1 &= ~(TIM_CR1_CEN);

	TIM4->SR = 0;

	TIM4->CNT = 0;

	TIM4->PSC = 7200 - 1; // 10 KHz

	TIM4->ARR = ms - 1;

	TIM4->CR1 |= (TIM_CR1_CEN);

	TIM4->DIER |= (TIM_DIER_UIE);

	NVIC_EnableIRQ(TIM4_IRQn);

	while ((TIM4->SR & TIM_SR_UIF) == 0) {
		//
	}
}
