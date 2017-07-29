#ifndef _PPM_PARSER_H_
#define _PPM_PARSER_H_

#include "string.h"
#include "remote_ctrl.h"
#include "math.h"

extern PPM remote_ctrl_channel ;

/*
* Э��֡��ʽ
* <b>1:val,2:val,3:val,4:val,5:val,6:val,7:val,8:val,9:val,[У��λ]<e>
* ����ȱʧĳ��ͨ������ֵΪ��ǰ�ı��������һ��ֵ��
* ���û��Ĭ��ֵ���Ϊ��ֵ
* У��λ����ȱ���˴�У����õ������У�飬�����е�val���Ƚ�
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