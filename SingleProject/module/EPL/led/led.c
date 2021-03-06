#include "led/led.h"

void led_init()
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  // LED1
  RCC_AHB1PeriphClockCmd(LED1_RCC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = LED1_PIN;
  GPIO_Init(LED1_GPIO, &GPIO_InitStructure);
  // LED2
  RCC_AHB1PeriphClockCmd(LED2_RCC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = LED2_PIN;
  GPIO_Init(LED2_GPIO, &GPIO_InitStructure);
  // LED3
  RCC_AHB1PeriphClockCmd(LED3_RCC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = LED3_PIN;
  GPIO_Init(LED3_GPIO, &GPIO_InitStructure);
  // LED4
  RCC_AHB1PeriphClockCmd(LED4_RCC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = LED4_PIN;
  GPIO_Init(LED4_GPIO, &GPIO_InitStructure);
  // LED5
  RCC_AHB1PeriphClockCmd(LED5_RCC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = LED5_PIN;
  GPIO_Init(LED5_GPIO, &GPIO_InitStructure);

  led_allSwitch(0);
}

void led_on(uint8_t index)
{
  switch (index)
  {
  case 1:
    LDE1_L();
    break;
  case 2:
    LDE2_L();
    break;
  case 3:
    LDE3_L();
    break;
  case 4:
    LDE4_L();
    break;
  case 5:
    LDE5_L();
    break;
  }
}

void led_off(uint8_t index)
{
  switch (index)
  {
  case 1:
    LDE1_H();
    break;
  case 2:
    LDE2_H();
    break;
  case 3:
    LDE3_H();
    break;
  case 4:
    LDE4_H();
    break;
  case 5:
    LDE5_H();
    break;
  }
}

void led_set(uint8_t state)
{
  uint8_t mask = 0;
  for (uint8_t i = 0; i <= 5; i++)
  {
    mask = (1 << i);
    if ((state & mask) == mask)
      led_on(i);
    else
      led_off(i);
  }
}

void led_allSwitch(uint8_t state)
{
  if (state)
    led_set(0xFF);
  else
    led_set(0x00);
}
