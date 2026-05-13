#define RCC_AHB1ENR (*(int *) 0x40023830)
#define GPIOB_MODER (*(int *) 0x40020400)
#define GPIOB_ODR (*(int *) 0x40020414)
#define STK_CTRL   (*(int *) 0xE000E010)
#define STK_LOAD   (*(int *) 0xE000E014)
#define STK_VAL  (*(int *) 0xE000E018)

void RED_LED_Init(void)
{
    RCC_AHB1ENR = RCC_AHB1ENR|(0x1<<1);
		GPIOB_MODER &= ~(0x03<<26);
    GPIOB_MODER|=0x04000000;
}
void SysTick_Init(void)
{
	STK_CTRL |=0x07;// enabled the interrupt 
	STK_VAL =0x123;
	STK_LOAD = 1600000;
}

void SysTick_Handler(void) // handler is a ISR(interrupt service routine), this function will execute automatically when the interrupt occurs
{
	GPIOB_ODR ^=(0x01<<13);
}

int main()
{
    RED_LED_Init();
	  SysTick_Init();
 
    while(1)
    {
       	
		}
}
/* Normally CPU executes:

while(1)
{
}

When SysTick (counter) reaches zero:

Hardware tells CPU: "Pause current execution and run SysTick_Handler()"
  
After handler completes: CPU automatically returns back.


  CPU Must Know Which Function To Execute, cpu read the address from interrupt vector table load into program counter i.e., address of sysTrick_handler
  
note: never calling the sysTick_Handler() manually, hardware calls automatically, when countflag is set i.e '1' and  counter reaches to '0'
