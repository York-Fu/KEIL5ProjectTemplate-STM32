#include "fire/fire.h"
#include "stm32f0xx.h"



void FireInit(void)
{
	
  GPIO_InitTypeDef	GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(Sensor_RCC  , ENABLE);//使能晚外设 PA 时钟
  
  GPIO_InitStructure.GPIO_Pin = Sensor_PIN ;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  //不上拉也不下拉
	GPIO_Init(Sensor_GPIO, &GPIO_InitStructure);	        //读取电平
}


u8 FireStatusGet(void)
{
  	if(GPIO_ReadInputDataBit(Sensor_GPIO, Sensor_PIN)==SET)          
       return 0;
     else return 1;
}

