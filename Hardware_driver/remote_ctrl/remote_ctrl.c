#include "remote_ctrl.h"

PPM remote_ctrl_channel ;

static void remote_init()
{
	remote_ctrl_channel.ElEV = 1000 ;
	remote_ctrl_channel.AILE = 1000 ;
	remote_ctrl_channel.THRO = 1000 ;
	remote_ctrl_channel.RUDO = 1000 ;
	remote_ctrl_channel.GEAR = 1000 ;
	remote_ctrl_channel.AUX1 = 1000 ;
	remote_ctrl_channel.AUX2 = 1000 ;
	remote_ctrl_channel.AUX3 = 1000 ;
	remote_ctrl_channel.AUX4 = 1000 ;
}


void calibration()
{
	int t = 0;
	remote_init() ;
	ppm_generate(remote_ctrl_channel) ;
	for(t = 0; t < ((max_channel_val-min_channel_val)/step_channel)+1; t++){
		remote_ctrl_channel.ElEV += step_channel ;
		remote_ctrl_channel.AILE += step_channel ;
		remote_ctrl_channel.THRO += step_channel ;
		remote_ctrl_channel.RUDO += step_channel ;
		remote_ctrl_channel.GEAR += step_channel ;
		remote_ctrl_channel.AUX1 += step_channel ;
		remote_ctrl_channel.AUX2 += step_channel ;
		remote_ctrl_channel.AUX3 += step_channel ;
		remote_ctrl_channel.AUX4 += step_channel ;
		if(remote_ctrl_channel.ElEV > max_channel_val)
			break ;
		ppm_generate(remote_ctrl_channel) ;
		delay_ms(100) ;
	}
}





