#ifndef _USART_H_
#define _USART_H_

#include "sys.h"

#define BUF_USART1 500
#define BUF_USART2 500
#define BUF_USART3 500



#define Rx1Length 500
#define Rx2Length 500
#define Rx3Length 500


extern u8 Rx1Buf[Rx1Length];     //接收缓冲,最大USART_REC_LEN个字节.	
extern u8 Rx2Buf[Rx2Length];     //接收缓冲,最大USART_REC_LEN个字节.
extern u8 Rx3Buf[Rx3Length];     //接收缓冲,最大USART_REC_LEN个字节.

extern u16 USART1_RX_STA ;


extern void USART1_Init(u32 bound);
extern void USART2_Init(u32 bound);
extern void USART3_Init(u32 bound);


extern void printf1(char *fmt, ...);
extern void printf2(char *fmt, ...);
extern void printf3(char *fmt, ...);


#endif

