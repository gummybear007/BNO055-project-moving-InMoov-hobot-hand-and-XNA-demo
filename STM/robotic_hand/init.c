#include "stm32l1xx_conf.h" //includy stdp

void GPIO_pin_conf(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed =	GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
  GPIO_Init(GPIOA, &GPIO_InitStructure);	
}

void InitializeTimer_interr(void)
{	
		NVIC_InitTypeDef nvicStructure;
		TIM_TimeBaseInitTypeDef timerInitStructure;
	
    nvicStructure.NVIC_IRQChannel = TIM6_IRQn;
    nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
    nvicStructure.NVIC_IRQChannelSubPriority = 1;
    nvicStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvicStructure);
	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

     
    timerInitStructure.TIM_Prescaler = 0;
    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    timerInitStructure.TIM_Period = 321;
    timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM6, &timerInitStructure);
    TIM_Cmd(TIM6, ENABLE);
		TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
}

