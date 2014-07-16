/*=============================================================================
#   >>   文件名: chown.c
#   >> 	   描述: chown函数的简单实现
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://hi.baidu.com/wangbo2008
#   >>   Github: hithub.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-16 15:29:41
#   >> 修改时间: 2014-07-16 15:29:41
#  Copyright (c) wangbo  All rights reserved.
=============================================================================*/



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

//#define DEBUG

void seerror(const char *error_string,int line)
{
	#ifdef DEBUG
	printf("line:%d\n",line);
	#endif
	perror(error_string);
}

int main(int argc,char ** argv)
{
	//参数合法性检测
	if(argc != 3)
	{
		printf("\"chown <userid:groppid> <filename>\"");
		exit(1);
	}
	else if(argc == 3)
	{

	}

	return 0;
}
