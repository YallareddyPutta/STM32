#define RCC_AHB1ENR (*(int *) 0x40023830)
#define GPIOB_MODER (*(int *) 0x40020400)
#define GPIOB_ODR (*(int *) 0x40020414)
#define STK_CTRL (*(int *) 0xE000E010)
#define STK_LOAD (*(int *) 0xE000E014)
#define STK_VAL (*(int *) 0xE000E018)

void RED_LED_Init(void)
{
    RCC_AHB1ENR = RCC_AHB1ENR|(0x1<<1);
    while(!(RCC_AHB1ENR & 0x2))
    {
        
    }
		GPIOB_MODER &= ~(0x03<<26);
    GPIOB_MODER|=0x04000000;
}
void SysTick_Init(void)
{
	STK_CTRL |=0x05; // Control/status register
  
	STK_VAL =0x123; // Writing ANY value to STK_VAL: Clears current counter to 0
  //STK_VAL = 0: is standard.
  //Writing 0x123 has no special meaning.
  
	STK_LOAD = 1600000-1; // delay = load/clock frequency.
  
  /* for example cpu clock is 16 MHZ: 16M clock cycles / sec
    load=1600000/16M = 0.1= 100 ms -> it means every 100mseconds the led will be toggle
    systick count the 1 count per clock pulse
    */
}
// SysTick is actually a hardware countdown timer inside the Cortex-M core itself.
// 24-bit countdown timer built into ARM Cortex-M core not part of STM32 peripherals like TIm1/TIM2 etc are the stm peripherals. Systick is Arm cortex-M core
// why 24-bit? -> because max reload value should 2^24 -1


int main()
{
    RED_LED_Init();
    SysTick_Init();
	
    while(1)
    {
        GPIOB_ODR ^=(0x01<<13); // every 100 ms the led will be toggle
			  while((STK_CTRL & (0x1<<16))==0);// cpu repeatedly reads the STK_CTRL to check the countflag,
      // whenever counter reaches to '0', hardware automatically countflag set to '1'.
      //it checks the 16bit repeatedly, when it becomes '1', while condition fails then loop exits.
      // whenever reads the register: hardware automatically clears countflag, it means count flag=0.
      // systick reloads the value(VAL) from LOAD, then countinue counting, process should be vice-versa.
		}
}

 /* SysTick works independently of CPU instructions.

  Even while CPU executes code:

  SysTick hardware counts in parallel. */
