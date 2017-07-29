#include "usart.h"
#include "delay.h"
#include "string.h"
#include "ppm.h"
#include "remote_ctrl.h"
#include "ppm_parser.h"


extern u16 USART1_RX_STA ;
extern PPM remote_ctrl_channel ;

int main()
{
	int len = 0;
	char string_tmp[Rx1Length] = {0};  
	int loop = 0;
	int time = 0;
	char *str = "<b>1:1300,2:1200,3:1300,4:1400,5:1500,6:1600,7:1700,8:1800,9:1900,[1234]<e>";  
	PPM a;
	delay_init(72);
	USART1_Init(115200) ;
	NVIC_Configuration() ;
	printf1("ppm system begin\r\n");
	ppm_init();

	
	while(1)
	{
		if (USART1_RX_STA & 0x8000){
			len = USART1_RX_STA & 0X3FFF;
			memcpy(string_tmp, Rx1Buf, len);
			USART1_RX_STA = 0;
			parser_string2ppm(string_tmp, 0);
			memset(string_tmp, 0, len) ;
		}
		ppm_generate(remote_ctrl_channel);
	}
	
}










