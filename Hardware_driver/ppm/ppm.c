#include "ppm.h"


void ppm_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //ÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

static void ppm_format2group(int *dst, PPM *ppm_data)
{
	dst[0] = ppm_data->ElEV-const_delay_time ;
	dst[1] = ppm_data->AILE-const_delay_time ;
	dst[2] = ppm_data->THRO-const_delay_time ;
	dst[3] = ppm_data->RUDO-const_delay_time ;
	dst[4] = ppm_data->GEAR-const_delay_time ;
	dst[5] = ppm_data->AUX1-const_delay_time ;
	dst[6] = ppm_data->AUX2-const_delay_time ;
	dst[7] = ppm_data->AUX3-const_delay_time ;
	dst[8] = ppm_data->AUX4-const_delay_time ;
}

static int ppm_sumDelayTime(int *group, int len)
{
	int sum = 0;
	int i = 0;
	for(i = 0; i < len; i++){
		sum += group[i] ;
	}
	return sum ;
}

void ppm_generate(PPM ppm_data)
{
	int t = 0;
	int last_t = 0;
	int ppm_group[9] = {0} ;
	int sum_DelayTime = 0;
	int len = 9;
	int remain_time = 0;
	
	ppm_format2group(ppm_group, &ppm_data) ;
	sum_DelayTime = ppm_sumDelayTime(ppm_group, len) ;
	for(t = 0; t < len; t++){
		PPMout = 0;
		delay_us(const_delay_time);
		PPMout = 1;
		delay_us(ppm_group[t]) ;
	}
	PPMout = 0 ;
	delay_us(const_delay_time) ;
	remain_time = 20000-sum_DelayTime-const_delay_time*10 ;
	PPMout = 1;
	remain_time = remain_time / 100 ;
	for(t = 0; t < remain_time;t++)
		delay_us(100) ;

}



