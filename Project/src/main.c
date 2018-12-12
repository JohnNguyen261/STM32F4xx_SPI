#include "mylib.h"


/*Declare Struct*/
GPIO_InitTypeDef GPIO_InitStructure;

void init_GPIO(void);


/*---------------------------Interrupt Systick-------------------------------*/
void SysTick_Handler()
{
	TimingDelay_Decrement();
}
  
  
  
  
void init_GPIO()
{
	/*setting PORT Led*/
	/* enable GPIOA */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Pin = Led1 | Led2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(PORTLed, &GPIO_InitStructure);
	
	/*setting PORT User Button*/
	/* enable GPIOE */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  GPIO_InitStructure.GPIO_Pin = UserButton | UserButton1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(PORTButton, &GPIO_InitStructure);
}


int main(){
	
	/*--------------------------Initialise Clock------------------------------*/
	SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
  if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
    while (1);                                  /* Capture error              */
  }
	
	
	init_GPIO();

	SPI1_Init();
	SPI1_SetSpeed(SPI_BaudRatePrescaler_256);
	USART_Config();	
	W25QXX_Init();
	myprintf("\n W25QXX_TYPE = %d \n",W25QXX_TYPE);
	W25QXX_TYPE=W25QXX_ReadIDAB();
	myprintf("\n W25QXX_TYPE = 0x%x ",W25QXX_TYPE);
	while(1){
		GPIO_ToggleBits(PORTLed,Led1);
		delay_ms(500);

	}
}
