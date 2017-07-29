#ifndef _PPM_H_
#define _PPM_H_

#include "sys.h"
#include "delay.h"

/*
* 范围从1000到2000
*/

#define PPMout PAout(4)

typedef struct ppm_format
{
	unsigned int ElEV; // ROLL         -->No.1
	unsigned int AILE; // PITCH        -->No.2
	unsigned int THRO; // THROTTL      -->No.3
	unsigned int RUDO; // YAW          -->No.4
	unsigned int GEAR; // RADIO5       -->No.5
	unsigned int AUX1; // RADIO6       -->No.6
	unsigned int AUX2; // RADIO7       -->No.7
	unsigned int AUX3; // RADIO8       -->No.8
	unsigned int AUX4; // RADIO9       -->No.9
}PPM ; // 遥控器上的9个通道

const static int const_delay_time = 500 ; 

void ppm_generate(PPM ppm_data);
void ppm_init();

#endif