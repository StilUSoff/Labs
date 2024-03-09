#include "stm32f2xx.h"             // Device header
void delay ()
{
  unsigned long i;                   // Counter for blinky delay
  i=0;
  for(i=0; i<2000000; i++){}       // Delay
}
int main ()
{
  RCC->AHB1ENR |= 1ul<<6;         // Enable port G clocking
  GPIOG->MODER = (GPIOG->MODER & ~1ul<<15) | 1ul<<14;
	for (;;)
	{	
    GPIOG->ODR |= 1ul<<7;	
    delay ();
    GPIOG->ODR &= ~1ul<<7;
    delay ();	
	}	
}