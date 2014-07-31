/*=============================================================================
#   >>   文件名: my_signal.c
#   >> 	   描述: 信号signal测试
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://www.cnblogs.com/wangbo2008/
#   >>   Github: github.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-31 10:52:01
#   >> 修改时间: 2014-07-31 11:01:05
#  Copyright (c) wangbo  All rights reserved.
=============================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

void fun(int signo)
{
	printf("检测到你按下了Ctrl+c!\n");
}

int main(int argc,char **argv)
{
	if(signal(SIGINT,fun) == SIG_ERR)
	{
		perror("signal");
		exit(1);
	}
	while(1);

	return 0;
}

