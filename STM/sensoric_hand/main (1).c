#include <stm32l1xx.h>
#include "stm32l1xx_conf.h" //includy stdp
#include <stdio.h>
#include "uart.h"
#include "i2c.h"
#include "BNO055.h"


volatile long time=0;
float qw,qx,qy,qz;
int time_s1,s1=100;  // min 59=3B max 237=ED  
// prstenicek min 40 max B4
// malic 

void send_uart(char data[])
{
	int i=0;
	while(data[i])
	{
		fputchar(data[i]);
		i++;
	}
}
void GPIO_pin_conf(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed =	GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed =	GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}


void adc_init(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 1;
  ADC_Init(ADC1, &ADC_InitStructure);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_16Cycles);
	ADC_Cmd(ADC1, ENABLE);
  /* Wait until the ADC1 is ready */
  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET);
	
  /* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConv(ADC1);
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

float invSqrt(float x) {
	float halfx = 0.5f * x;
	float y = x;
	long i = *(long*)&y;
	i = 0x5f3759df - (i>>1);
	y = *(float*)&i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}

void delay(int tim)
{
	long t=time;
	while((tim+t)>time);
}

void TIM6_IRQHandler(void) // vyvolany po 10us
{
	time++;	
	time_s1++;
	if(time_s1>1999)
	{
	time_s1=0;
	GPIO_ResetBits(GPIOD, GPIO_Pin_2);
	}
	
	if(time_s1>s1)
	GPIO_SetBits(GPIOD, GPIO_Pin_2);
	
	
	
	TIM_ClearFlag(TIM6, TIM_FLAG_Update);
}




int main(void)
{
	char s[200];
	float ad;
	
	GPIO_pin_conf();
	InitializeTimer_interr();
	

	
	//GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	USART_Config();
	send_uart("cusik svete!!");	
	adc_init();
	I2C2_init();
	init_imu();
	
	while(1)
	{
	cti_quat(&qw,&qx,&qy,&qz);
	ad=(float)ADC_GetConversionValue(ADC1);
	//sprintf(s,"quat1:%d\tquat2:%d\tquat3:%d\tquat4:%d\r",(int)(qw),(int)(qx),(int)(qy),(int)(qz));
	sprintf(s,"cusky!!!\rad:%f\r",ad);
	send_uart(s);	
	}
}
