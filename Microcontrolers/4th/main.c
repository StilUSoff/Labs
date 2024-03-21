#include "stm32f2xx.h"                  // Device header
#include "core_cm3.h"
#include "core_cm0.h"

void delay ()
{
unsigned long i;
i=0;
for(i=0; i<2000000; i++){}
}

void TIM_DAC_IRQHandler()
{
	if(TIM6->SR&TIM_SR_UIF)
	{
		TIM6->SR&=~TIM_SR_UIF;
		GPIOG->ODR |= 1ul<<8;
		delay ();
		GPIOG->ODR &= ~(1ul<<8);
	}
}


void EXTI0_IRQHandler(void)
{
	GPIOG->ODR |= 1ul<<6;
	delay ();
	GPIOG->ODR &= ~1ul<<6;
	delay ();
	EXTI->PR|=EXTI_PR_PR0;
}

int main ()
{
	RCC->AHB1ENR |= 1ul<<6; // Enable port G clocking
	RCC->APB2ENR|= 1ul<<14; //SYSCFGEN
	SCB->SCR |= 1ul<<2;

	GPIOG->MODER = (GPIOG->MODER & ~(1ul<<13)) | 1ul<<12;//PG6
	GPIOG->MODER = (GPIOG->MODER & ~(1ul<<15)) | 1ul<<14;//PG7
	GPIOA->MODER = (GPIOA->MODER & ~(1ul<<1)) & ~(1ul);//PA0

	EXTI->IMR|=EXTI_IMR_MR0;
	EXTI->RTSR|= EXTI_RTSR_TR0; //Rise Signal
	EXTI->FTSR|= EXTI_FTSR_TR0; //Fall Signal

	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA; 

	NVIC_SetPriority(6,5); 

	NVIC_EnableIRQ(6);

	RCC->APB1ENR|=RCC_APB1ENR_TIM6EN;


	TIM6->DIER|=TIM_DIER_UIE;


	TIM6->EGR|=TIM_EGR_UG;


for (;;)
{
GPIOG->ODR |= 1ul<<7;
delay ();
GPIOG->ODR &= ~1ul<<7;
GPIOG->ODR |= 1ul<<6;
delay ();
GPIOG->ODR &= ~1ul<<6;
}
}