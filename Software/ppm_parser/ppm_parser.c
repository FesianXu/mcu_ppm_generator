#include "ppm_parser.h"

static int atoi_my(char *str)
{
	int sum = 0;
	int len = strlen(str);
	int i = 0;
	char ascii = 0;
	for(i = 0; i < len; i++)
	{
		ascii = *str-'0';
		if(ascii > 9 || ascii < 0)
			return 0;
		sum += ascii*pow(10, len-i-1) ;
		str++ ;
	}
	return sum;
}


static int get_channel_value(char *str,const char *which_channel)
{
	char *channel_begin = strstr(str, which_channel) ;
	char channel_val_str[10] = {0} ;
	int i = 0;
	if(channel_begin != 0)
	{
		channel_begin += sizeof(char)*strlen(which_channel) ;
		while(*channel_begin != channel_end_pattern)
		{
			channel_val_str[i++] = *channel_begin ;
			channel_begin++ ;
		}
		return atoi_my(channel_val_str);
	}
	else
		return 0;
}


static int get_check_value(char *str)
{
	char *check_begin = strstr(str, check_begin_pattern) ;
	char check_val_str[10] = {0} ;
	int i = 0;
	if(check_begin != 0)
	{
		check_begin += sizeof(char)*strlen(check_begin_pattern) ;
		while(*check_begin != check_end_pattern)
		{
			check_val_str[i++] = *check_begin ;
			check_begin++ ;
		}
		return atoi_my(check_val_str) ;
	}
	else
		return 0;
}

static void update_ppm(int *channel_vals)
{
	if(channel_vals[0] != 0)
		remote_ctrl_channel.ElEV = channel_vals[0];
	if(channel_vals[1] != 0)
		remote_ctrl_channel.AILE = channel_vals[1];
	if(channel_vals[2] != 0)
		remote_ctrl_channel.THRO = channel_vals[2];
	if(channel_vals[3] != 0)
		remote_ctrl_channel.RUDO = channel_vals[3];
	if(channel_vals[4] != 0)
		remote_ctrl_channel.GEAR = channel_vals[4];
	if(channel_vals[5] != 0)
		remote_ctrl_channel.AUX1 = channel_vals[5];
	if(channel_vals[6] != 0)
		remote_ctrl_channel.AUX2 = channel_vals[6];
	if(channel_vals[7] != 0)
		remote_ctrl_channel.AUX3 = channel_vals[7];
	if(channel_vals[8] != 0)
		remote_ctrl_channel.AUX4 = channel_vals[8];
}



/*
* retVal: 用掩膜的形式表示的解析后控制的通道，比如
* 0100，0100，0 | 000,0000 表示控制的是第二，第六通道，前九位有效
*/
short parser_string2ppm(char *str, u8 is_check)
{
	int channel_val_group[9] = {0} ;
	int check_val = 0;
	int re_check_val = 0;
	int i = 0;
	short ret_mask = 0;
	if(strstr(str, begin_pattern) == 0 || strstr(str, end_pattern) == 0)
		return 0 ;
	channel_val_group[0] = get_channel_value(str, c1_begin_pattern);
	channel_val_group[1] = get_channel_value(str, c2_begin_pattern);
	channel_val_group[2] = get_channel_value(str, c3_begin_pattern);
	channel_val_group[3] = get_channel_value(str, c4_begin_pattern);
	channel_val_group[4] = get_channel_value(str, c5_begin_pattern);
	channel_val_group[5] = get_channel_value(str, c6_begin_pattern);
	channel_val_group[6] = get_channel_value(str, c7_begin_pattern);
	channel_val_group[7] = get_channel_value(str, c8_begin_pattern);
	channel_val_group[8] = get_channel_value(str, c9_begin_pattern);
	check_val = get_check_value(str) ;
	
	re_check_val = channel_val_group[0];
	for(i = 1; i < 9; i++)
	{
		re_check_val ^= channel_val_group[i];
	}
	if(is_check == 1)
	{
		if(re_check_val != check_val)
			return 0;
	} // 进行校验
	
//	for(i=0; i < 9;i++){
//		printf1("i+1 = %d\r\n", channel_val_group[i]) ;
//	}
//	
//	printf1("check val = %d\r\n", re_check_val);
	
	for(i = 0; i < 9; i++)
	{
		if(channel_val_group[i] != 0)
		{
			ret_mask |= (1 << (15-i)) ; // update mask
		}
	}
	update_ppm(channel_val_group) ;
	return ret_mask;
}









