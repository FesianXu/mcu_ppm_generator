#include "USART.h"
#include "sys.h"
#include "stm32f10x_usart.h"
#include "stdarg.h"


//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   
u8 Rx1Buf[Rx1Length] = {0};     //接收缓冲,最大USART_REC_LEN个字节.	
u8 Rx2Buf[Rx2Length];     //接收缓冲,最大USART_REC_LEN个字节.
u8 Rx3Buf[Rx3Length];     //接收缓冲,最大USART_REC_LEN个字节.


/*******************************************************************
下面是串口初始化函数USARTx_Init(u32 bound)
*******************************************************************/
void USART1_Init(u32 bound){
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
	  USART_InitTypeDef USART_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
	 
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
 	  USART_DeInit(USART1);  //复位串口1
	 //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PA9
   
    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PA10

   //Usart1 NVIC 配置

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	  NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	 USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	 USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	 USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	 USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	 USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	 USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(USART1, &USART_InitStructure); //初始化串口
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断
    USART_Cmd(USART1, ENABLE);                    //使能串口 

}

void USART2_Init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//使能USART1，GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	 //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PA9
   
    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PA10

   //Usart1 NVIC 配置

    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	  NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	 USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	 USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	 USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	 USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	 USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	 USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(USART2, &USART_InitStructure); //初始化串口
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断
    USART_Cmd(USART2, ENABLE);                    //使能串口 

}


//初始化IO 串口1 
//bound:波特率
void USART3_Init(u32 bound){
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//使能USART1，GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	//USART1_TX   PA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化PB10
   
	//USART1_RX	  PA.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);  //初始化PB11

   //Usart1 NVIC 配置

    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(USART3, &USART_InitStructure); //初始化串口
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启中断
    USART_Cmd(USART3, ENABLE);                    //使能串口 

}
/*******************************************************************
下面是串口接受中断函数USARTx_IRQHandler(void) 
*******************************************************************/


//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART1_RX_STA = 0;       //接收状态标记	  

void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
//		Res = USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据
		Res = (uint16_t)(USART1->DR & (uint16_t)0x01FF);
		if((USART1_RX_STA & 0x8000) == 0)//接收未完成
		{
			if(USART1_RX_STA & 0x4000)//接收到了0x0d
			{
				if(Res != 0x0a)
					USART1_RX_STA = 0;//接收错误,重新开始
				else 
					USART1_RX_STA |= 0x8000;	//接收完成了 
			}
			else //还没收到0X0D
			{	
				if(Res == 0x0d)
					USART1_RX_STA |= 0x4000;
				else
				{
					Rx1Buf[USART1_RX_STA & 0X3FFF] = Res ;
					USART1_RX_STA++;
					if(USART1_RX_STA > (Rx1Length-1))
						USART1_RX_STA = 0;//接收数据错误,重新开始接收	  
				}		 
			}
		}   		 
	} 						
} 
	



/*******************************************************************
下面是串口打印函数printfx()
*******************************************************************/
void printf1(char *fmt, ...) 
 { 
	 char buffer[BUF_USART1+1];  
	 u8 i = 0; 
	 va_list arg_ptr; 
	 va_start(arg_ptr, fmt);   
	 vsnprintf(buffer,BUF_USART1+1,fmt,arg_ptr); 
	 USART_ClearFlag(USART1,USART_FLAG_TC);

	 while ((i <BUF_USART1) && buffer[i]) 
	 { 
			USART_SendData(USART1, (u8) buffer[i++]); 
			while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);  
	 } 
	 va_end(arg_ptr); 
 } 
 
void printf2(char *fmt, ...) 
 { 
	 char buffer[BUF_USART2+1];  
	 u8 i = 0; 
	 va_list arg_ptr; 
	 va_start(arg_ptr, fmt);   
	 vsnprintf(buffer,BUF_USART2+1,fmt,arg_ptr); 
	 USART_ClearFlag(USART2,USART_FLAG_TC);

	 while ((i <BUF_USART2) && buffer[i]) 
	 { 
			USART_SendData(USART2, (u8) buffer[i++]); 
			while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);  
	 } 
	 va_end(arg_ptr); 
 } 
 
void printf3(char *fmt, ...) 
 { 
	 char buffer[BUF_USART3+1];  
	 u8 i = 0; 
	 va_list arg_ptr; 
	 va_start(arg_ptr, fmt);   
	 vsnprintf(buffer,BUF_USART3+1,fmt,arg_ptr); 
	 USART_ClearFlag(USART3,USART_FLAG_TC);

	 while ((i <BUF_USART3) && buffer[i]) 
	 { 
			USART_SendData(USART3, (u8) buffer[i++]); 
			while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);  
	 } 
	 va_end(arg_ptr); 
 } 

