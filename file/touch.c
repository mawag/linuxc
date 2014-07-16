/*=============================================================================
#   >>   文件名: touch.c
#   >> 	   描述: touch的简单实现
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://hi.baidu.com/wangbo2008
#   >>   Github: hithub.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-16 18:19:31
#   >> 修改时间: 2014-07-16 18:19:31
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
#include <utime.h>

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
	char* filename;		//文件名
	int fd;			//文件描述符
	//参数合法性判断
	if(argc != 2)
	{
		printf("\"touch <filename>\"\n");
		exit(1);
	}
	filename = argv[1];

	//打开文件
	if((fd = open(filename,(O_RDONLY|O_CREAT),436))== -1)
	{
		seerror("open",__LINE__);
		exit(1);
	}

	//关闭文件
	if(close(fd) == -1)
	{
		perror("close");
		exit(1);
	}

	//修改时间
	if(utime(filename,NULL) == -1)
	{
		seerror("utime",__LINE__);
		exit(1);
	}

	return 0;
}
