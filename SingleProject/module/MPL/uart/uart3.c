#include "uart/uart.h"
#include "DXL.h"

void Uart3_Init(uint32_t bpr)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  
  /* Configure USARTx_Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度10MHz
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    //串口1对应引脚复用映射
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //GPIO复用为USART
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIO复用为USART
  
  USART_InitStructure.USART_BaudRate = bpr;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  
  USART_Init(USART3, &USART_InitStructure);
  
    /* Enable the USARTz Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  /* Enable USARTy Receive and Transmit interrupts */
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
  
   /* Enable the USARTy */
  USART_Cmd(USART3, ENABLE);
  
}

void Uart3_SendByte(unsigned char x)
{
  USART_SendData(USART3, x);
    // Loop until the end of transmission 
  while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
}

/*PUTCHAR_PROTOTYPE
{
  uart1_putc(ch);
  return ch;
}*/

#if 0

static void (*irq_call_RXNE)(unsigned char x) = NULL;
void  Uart3_SetIrqCall_RXNE(void (*fun)(unsigned char ))
{
  irq_call_RXNE = fun;
}

static void (*irq_call_IT_TC)(void) = NULL;
void  Uart3_SetIrqCall_IT_TC(void (*fun)(void))
{
  irq_call_IT_TC = fun;
}

void USART3_IRQHandler(void)
{
  unsigned char x;
  if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
  {
    x = USART_ReceiveData(USART3);
    if(irq_call_RXNE != NULL)
      irq_call_RXNE(x);
  }
  if(USART_GetITStatus(USART3, USART_IT_TC) != RESET)
  {
    if(irq_call_IT_TC != NULL)
      irq_call_IT_TC();
  }
}

#else

void USART3_IRQHandler(void)
{
  dxl_irqPc();
}

#endif

