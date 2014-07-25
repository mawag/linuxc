/*=============================================================================
#   >>   文件名: pwd.c
#   >> 	   描述: 
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://hi.baidu.com/wangbo2008
#   >>   Github: hithub.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-16 20:36:59
#   >> 修改时间: 2014-07-16 20:41:24
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

//显示错误信息
void seerror(const char* error_string,int line)
{
	#ifdef DEBUG
	printf("line:%d\n",line);
	#endif
	perror(error_string);
}


int main(int argc,char ** argv)
{
	char* path;//当前工作路径

	if((path = getcwd(NULL,0)) == NULL)
	{
		seerror("pwd",__LINE__);
		exit(1);
	}

	printf("%s\n",path);

	free(path);

	return 0;
}
