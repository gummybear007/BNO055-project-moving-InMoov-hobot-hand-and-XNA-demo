#include <stm32l1xx.h>
#include "stm32l1xx_conf.h" //includy stdp
#include <stdio.h>
#include "uart.h"
#include "i2c.h"
#include "BNO055.h"

#define ARRAYSIZE 8*4

#define ADC1_DR_ADDRESS    ((uint32_t)0x40012458)
//#define IOPIN0         (*((volatile unsigned char *) 0x08082000))
volatile long time=0;
unsigned int stat_calib=0,time_calib=0;
int time_s1,time_s2,time_s3,time_s4,time_s5,time_s6;
int s1=100,s2=100,s3=100,s4=100,s5=100,s6=100;  // min 59=3B max 237=ED  
volatile uint16_t ADC_values[ARRAYSIZE];
__IO uint16_t ADC_C_Val[10];
__IO uint16_t ADC_C_Val_l[10];
__IO uint16_t ADC_C_Val_h[10];
float ADC_C_Val_cal[10];

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




void ADC_DMA_Config(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
  /*------------------------ DMA1 configuration ------------------------------*/
  /* Enable DMA1 clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  /* DMA1 channel1 configuration */
  DMA_DeInit(DMA1_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_ADDRESS;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC_C_Val[0];
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = 10;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable ;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  
  /* Enable DMA1 channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);

  /*----------------- ADC1 configuration with DMA enabled --------------------*/
  /* Enable the HSI oscillator */
  RCC_HSICmd(ENABLE);


  /* Enable GPIOA clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  /* Configure PB.12 (ADC Channel18) in analog mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Enable GPIOC clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  /* Configure PB.12 (ADC Channel18) in analog mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* Check that HSI oscillator is ready */
  while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);

  /* Enable ADC1 clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  /* ADC1 configuration */
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 10;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channel18 configuration */ 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_192Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_192Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_192Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_192Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 5, ADC_SampleTime_192Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 6, ADC_SampleTime_192Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 7, ADC_SampleTime_192Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 8, ADC_SampleTime_192Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 9, ADC_SampleTime_192Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 10, ADC_SampleTime_192Cycles);
	
  /* Enable the request after last transfer for DMA Circular mode */
  ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
  
  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

  /* Wait until the ADC1 is ready */
  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET)
  {
  }

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
	time_calib++;
	time++;	
	
	if(time_calib>500000)
	{
		stat_calib=1;
	}
	
	TIM_ClearFlag(TIM6, TIM_FLAG_Update);
}

void calib(void)
{
	int iter;
	stat_calib=1;
	for(iter=0;iter<10;iter++)
	{
		ADC_C_Val_l[iter]=ADC_C_Val[iter];
		ADC_C_Val_h[iter]=ADC_C_Val[iter];
	}
		
	time=0;
	send_uart("8 sekund calibrace");	
	while(time<800000)
	{
		for(iter=0;iter<10;iter++)
		{
			if(ADC_C_Val[iter]<ADC_C_Val_l[iter])
				ADC_C_Val_l[iter]=ADC_C_Val[iter];
			if(ADC_C_Val[iter]>ADC_C_Val_h[iter])
				ADC_C_Val_h[iter]=ADC_C_Val[iter];
		}
	}
	
	DATA_EEPROM_Unlock();
	delay(20);
	for(iter=0;iter<20;iter++)
	{
		DATA_EEPROM_ProgramHalfWord((uint32_t)(((uint16_t *)0x08080000)+iter), 0x00);
		if(iter<10)
		DATA_EEPROM_ProgramHalfWord((uint32_t)(((uint16_t *)0x08080000)+iter), ADC_C_Val_l[iter]);
		if(iter>9)
		DATA_EEPROM_ProgramHalfWord((uint32_t)(((uint16_t *)0x08080000)+iter), ADC_C_Val_h[iter-10]);
	}
}

int main(void)
{
	char s[200],x;
	float qw,qx,qy,qz,qw2,qx2,qy2,qz2,qw3,qx3,qy3,qz3;
	float lacc_x,lacc_y,lacc_z,lacc_low,lacc_high,lacc_1;
	uint16_t adc_LP[10][5];
	int i;

	InitializeTimer_interr();
	

	USART_Config();
	send_uart("Hello world!!");	
	
	I2C1_init();
	init_imu(SLAVE_ADDRESS1);
	init_imu(SLAVE_ADDRESS2);
	I2C2_init();
	init_imu2(SLAVE_ADDRESS1);

	ADC_DMA_Config();
	
	for(i=0;i<10;i++)
	ADC_C_Val_l[i]=*(((uint16_t *)0x08080000)+i);
	for(i=0;i<10;i++)
	ADC_C_Val_h[i]=*(((uint16_t*)0x08080000)+(i+10));

	for(i=0;i<10;i++)
	{
		sprintf(s,"adl%d:%d\tadh%d:%d\r",i,ADC_C_Val_l[i],i,ADC_C_Val_h[i]);
		send_uart(s);	
	}
	
	cti_lin_acc(&lacc_x,&lacc_y,&lacc_z,SLAVE_ADDRESS1);
	lacc_1=lacc_y;

	while(1)
	{
	cti_quat(&qw, &qx,&qy,&qz,SLAVE_ADDRESS1);
	cti_quat(&qw2, &qx2,&qy2,&qz2,SLAVE_ADDRESS2);
	cti_quat2(&qw3, &qx3,&qy3,&qz3,SLAVE_ADDRESS1);
		
	if(stat_calib==0)
	{
	cti_lin_acc(&lacc_x,&lacc_y,&lacc_z,SLAVE_ADDRESS1);
		if(lacc_y<lacc_low)
			lacc_low=lacc_y;
		if(lacc_y>lacc_high)
			lacc_high=lacc_y;
		if((lacc_low<(lacc_1-350))&&(lacc_high>(lacc_1+350)))
			calib();
	}
	
	for(i=0;i<10;i++)
	{
//		adc_LP[i][4]=adc_LP[i][3];
//		adc_LP[i][3]=adc_LP[i][2];
//		adc_LP[i][2]=adc_LP[i][1];
//		adc_LP[i][1]=adc_LP[i][0];
//	  adc_LP[i][0]=ADC_C_Val[i];
		
//		ADC_C_Val[i]=(int)((float)(adc_LP[i][0]+adc_LP[i][1]+adc_LP[i][2]+adc_LP[i][3]+adc_LP[i][4])/5);
		if((ADC_C_Val_h[i]-ADC_C_Val_l[i])!=0)
		ADC_C_Val_cal[i]=((float)(ADC_C_Val[i]-ADC_C_Val_l[i])*100)/(ADC_C_Val_h[i]-ADC_C_Val_l[i]);
		else
		ADC_C_Val_cal[i]=100;
		
		if(ADC_C_Val_cal[i]>100)
			ADC_C_Val_cal[i]=100;
		if(ADC_C_Val_cal[i]<0)
			ADC_C_Val_cal[i]=0;
	}
	
	if(stat_calib)
	{
//		sprintf(s,"ad1:%d\tad2:%d\tad3:%d\tad4:%d\tad5:%d\tad6:%d\tad7:%d\tad8:%d\tad9:%d\tad10:%d\tad1:%d\tad2:%d\tad3:%d\tad4:%d\tad5:%d\tad6:%d\tad7:%d\tad8:%d\tad9:%d\tad10:%d\r",
//		ADC_C_Val[0],ADC_C_Val[1],ADC_C_Val[2],ADC_C_Val[3],ADC_C_Val[4],ADC_C_Val[5],ADC_C_Val[6],ADC_C_Val[7],ADC_C_Val[8],ADC_C_Val[9],(int)ADC_C_Val_cal[0],(int)ADC_C_Val_cal[1],(int)ADC_C_Val_cal[2],(int)ADC_C_Val_cal[3],(int)ADC_C_Val_cal[4],(int)ADC_C_Val_cal[5],(int)ADC_C_Val_cal[6],(int)ADC_C_Val_cal[7],(int)ADC_C_Val_cal[8],(int)ADC_C_Val_cal[9]);
	//sprintf(s,"%d\t%d\t%d\t\r",(int)(qx),(int)(qy),(int)(qz));
	//sprintf(s,"quat1:%d\tquat2:%d\tquat3:%d\tquat4:%d\tquat5:%d\tquat6:%d\tquat7:%d\tquat8:%d\r",(int)(qw),(int)(qx),(int)(qy),(int)(qz),(int)(qw3),(int)(qx3),(int)(qy3),(int)(qz3));
	sprintf(s,"quat1:%d\tquat2:%d\tquat3:%d\tquat4:%d\tquat5:%d\tquat6:%d\tquat7:%d\tquat8:%d\tquat9:%d\tquat10:%d\tquat11:%d\tquat12:%d\tad1:%d\tad2:%d\tad3:%d\tad4:%d\tad5:%d\tad6:%d\tad7:%d\tad8:%d\tad9:%d\tad10:%d\r",
	(int)(qw),(int)(qx),(int)(qy),(int)(qz),(int)(qw2),(int)(qx2),(int)(qy2),(int)(qz2),(int)(qw3),(int)(qx3),(int)(qy3),(int)(qz3),(int)ADC_C_Val_cal[0],(int)ADC_C_Val_cal[1],(int)ADC_C_Val_cal[2],(int)ADC_C_Val_cal[3],(int)ADC_C_Val_cal[4],(int)ADC_C_Val_cal[5],(int)ADC_C_Val_cal[6],(int)ADC_C_Val_cal[7],(int)ADC_C_Val_cal[8],(int)ADC_C_Val_cal[9]);
		send_uart(s);	
	}	
	}
}
