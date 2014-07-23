/*=============================================================================
#   >>   文件名: 1.c
#   >> 	   描述:
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://www.cnblogs.com/wangbo2008/
#   >>   Github: github.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-23 11:44:57
#   >> 修改时间: 2014-07-23 11:44:57
#  Copyright (c) wangbo  All rights reserved.
=============================================================================*/
#include <stdio.h>
int main(void)
{
	int i;
	for(i=0;i<90;i++)
		printf("%d",i%10 +1);

	system("ls -l");
	return 0;
}
