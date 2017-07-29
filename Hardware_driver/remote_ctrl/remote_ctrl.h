#ifndef _REMOTE_CTRL_H_
#define _REMOTE_CTRL_H_

#include "ppm.h"
#include "delay.h"

extern PPM remote_ctrl_channel ;

const static int max_channel_val = 2000 ;
const static int min_channel_val = 1000 ;
const static unsigned char step_channel = 50 ;

void remote_calibration(); // Ð£×¼Ò£¿ØÆ÷


#endif