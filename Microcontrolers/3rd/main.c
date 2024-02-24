#include "stm32f2xx.h"                  // Device header
#include "core_cm3.h"
void delay ()
{
unsigned long i;
i=0;
for(i=0; i<2000000; i++){}
}
 
void EXTI0_IRQHandler(void)
{
GPIOG->ODR |= 1ul<<6;
delay ();
GPIOG->ODR &= ~1ul<<6;
delay ();
 
​EXTI->PR|=EXTI_PR_PR0;
}
 
void EXTI15_10_IRQHandler(void)
{
GPIOG->ODR |= 1ul<<8;
delay ();
GPIOG->ODR &= ~1ul<<8;
delay ();
 
​EXTI->PR|=EXTI_PR_PR0;
}
 
 
int main ()
{
  RCC->AHB1ENR |= 1ul<<6; // Enable port G clocking
  RCC->APB2ENR|= 1ul<<14; //SYSCFGEN
​
 GPIOG->MODER = (GPIOG->MODER & ~(1ul<<13)) | 1ul<<12;//PG6
 GPIOG->MODER = (GPIOG->MODER & ~(1ul<<15)) | 1ul<<14;//PG7
 GPIOG->MODER = (GPIOG->MODER & ~(1ul<<17)) | 1ul<<16;//PG8
 
 GPIOG->MODER = (GPIOG->MODER & ~(1ul<<31)) & ~(1ul<<30);//PG15
 GPIOA->MODER = (GPIOA->MODER & ~(1ul<<1)) & ~(1ul);//PA0
​
 EXTI->IMR|=EXTI_IMR_MR0|EXTI_IMR_MR15;
//зарезервировали две линии под прерывания (сконфигурировали маскирующие биты...)
 
 EXTI->RTSR|= EXTI_RTSR_TR0; //Rise Signal
 EXTI->FTSR|=EXTI_FTSR_TR15; //Fall Signal
​
 SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;
//прикрепили pa0 к зарезарвированной линии
​
SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI15_PG;
​
NVIC_SetPriority(6,5); //(номер в таблице векторов прерываний(тип), приоритет)
NVIC_SetPriority(40,6);
​
NVIC_EnableIRQ(6); //активировали прерывание
NVIC_EnableIRQ(40);
​
for (;;)
{
GPIOG->ODR |= 1ul<<7;
delay ();
GPIOG->ODR &= ~1ul<<7;
delay ();
}
}