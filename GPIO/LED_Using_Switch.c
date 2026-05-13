#define RCC_AHB1ENR   (*(volatile unsigned int *)0x40023830)

#define GPIOB_MODER   (*(volatile unsigned int *)0x40020400)
#define GPIOB_ODR     (*(volatile unsigned int *)0x40020414)

#define GPIOC_MODER   (*(volatile unsigned int *)0x40020800)
#define GPIOC_PUPDR   (*(volatile unsigned int *)0x4002080C)
#define GPIOC_IDR     (*(volatile unsigned int *)0x40020810)

void RED_LED_Init(void)
{
  
    RCC_AHB1ENR |= (1 << 1);

    GPIOB_MODER &= ~(0x3 << 26);

    GPIOB_MODER |= (0x1 << 26);
}

void ENTER_SW_Init(void)
{
    RCC_AHB1ENR |= (1 << 2);

    GPIOC_MODER &= ~(0x3 << 20);
    GPIOC_PUPDR &= ~(0x3 << 20);
    GPIOC_PUPDR |=  (0x1 << 20);// pull-up enabled: pull up means intially 1, when switch pressed it gives 0, it means for pressing becomes 0, releasing it becomes 1
}



int main(void)
{
    RED_LED_Init();
    ENTER_SW_Init();

    GPIOB_ODR |= (1 << 13); // here why gpio pin setting because here led is low level hardware, it blink when the pin set to 0, for turn off the led make the pin to 0 to 1 

    while(1)
    {
        if(!(GPIOC_IDR & (1 << 10))) // when switch is pressed, condition looks like !0 it means true, then led will be blink, after releasing the switch, if condition looks like !0 it means false, it goes to else part set the gpio pin 13 
        {
            GPIOB_ODR &= ~(1 << 13);
        }
        else
        {
            GPIOB_ODR |= (1 << 13);
        }
    }
}