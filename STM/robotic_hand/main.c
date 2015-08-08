#include <stm32l1xx.h>
#include "stm32l1xx_conf.h" //includy stdp
#include <stdio.h>
#include "uart.h"
#include "init.h"

#define min_1 60
#define max_1 236

char s[200];
volatile long time=0;
unsigned int stat_calib=0,time_calib=0;
int time_s1,time_s2,time_s3,time_s4,time_s5,time_s6;
int s1=100,s2=100,s3=100,s4=100,s5=100,s6=100;  // min 59=3B max 237=ED  

// prst min 40 max B4

void send_uart(char data[])
{
	int i=0;
	while(data[i])
	{
		fputchar(data[i]);
		i++;
	}
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
	time_s1++;
	time_s2++;
	time_s3++;
	time_s4++;
	time_s5++;
	time_s6++;	
	
	if(time_calib>500000)
	{
		stat_calib=1;
	}
	
	if(time_s1>1999)
	{
	time_s1=0;
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	}
	if(time_s1>s1)
	GPIO_SetBits(GPIOA, GPIO_Pin_0);
	
	if(time_s2>1999)
	{
	time_s2=0;
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	}
	if(time_s2>s2)
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
	
	if(time_s3>1999)
	{
	time_s3=0;
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	}
	if(time_s3>s3)
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
	
	if(time_s4>1999)
	{
	time_s4=0;
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	}
	if(time_s4>s4)
	GPIO_SetBits(GPIOA, GPIO_Pin_3);
	
	if(time_s5>1999)
	{
	time_s5=0;
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
	}
	if(time_s5>s5)
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	
	if(time_s6>1999)
	{
	time_s6=0;
	GPIO_ResetBits(GPIOA, GPIO_Pin_5);
	}
	if(time_s6>s6)
	GPIO_SetBits(GPIOA, GPIO_Pin_5);
	
	TIM_ClearFlag(TIM6, TIM_FLAG_Update);
}

void USART1_IRQHandler(void){

	static uint8_t cnt = 0;

	if( USART_GetITStatus(USART1, USART_IT_RXNE) ){

		char t = USART1->DR; 


		if( (t != (char)0x65) && (cnt < 200) ){
			s[cnt] = t;
			cnt++;
		}
		else{ 
			cnt = 0;
		}
	}
}

int main(void)
{
	
	GPIO_pin_conf();
	InitializeTimer_interr();
	USART_Config();
	
	send_uart("Wello world!!");	
	
	while(1)
	{
		delay(10);
		s1=(int)((float)(max_1-min_1)*s[1]/100)+min_1;
		s2=(int)((float)(max_1-min_1)*s[2]/100)+min_1;
		s3=(int)((float)(max_1-min_1)*s[3]/100)+min_1;
		s4=(int)((float)(max_1-min_1)*s[4]/100)+min_1;
		s5=(int)((float)(max_1-min_1)*s[5]/100)+min_1;
		s6=(int)((float)(max_1-min_1)*s[0]/100)+min_1;
	}
}
	
