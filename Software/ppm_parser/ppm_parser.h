#ifndef _PPM_PARSER_H_
#define _PPM_PARSER_H_

#include "string.h"
#include "remote_ctrl.h"
#include "math.h"

extern PPM remote_ctrl_channel ;

/*
* 协议帧格式
* <b>1:val,2:val,3:val,4:val,5:val,6:val,7:val,8:val,9:val,[校验位]<e>
* 允许缺失某个通道，其值为以前改变过后的最后一个值。
* 如果没有默认值则改为中值
* 校验位不可缺，此处校验采用的是异或校验，将所有的val异或比较
*/

const static char *begin_pattern = "<b>" ;
const static char *end_pattern = "<e>" ;
const static char *c1_begin_pattern = "1:" ;
const static char *c2_begin_pattern = "2:" ;
const static char *c3_begin_pattern = "3:" ;
const static char *c4_begin_pattern = "4:" ;
const static char *c5_begin_pattern = "5:" ;
const static char *c6_begin_pattern = "6:" ;
const static char *c7_begin_pattern = "7:" ;
const static char *c8_begin_pattern = "8:" ;
const static char *c9_begin_pattern = "9:" ;
const static char channel_end_pattern = ',' ;
const static char *check_begin_pattern = "[" ;
const static char check_end_pattern = ']' ;

short parser_string2ppm(char *str, u8 is_check);

#endif