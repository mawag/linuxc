/*=============================================================================
#   >>   文件名: mv.c
#   >> 	   描述: mv的简单实现
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://hi.baidu.com/wangbo2008
#   >>   Github: hithub.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-16 20:24:11
#   >> 修改时间: 2014-07-16 20:30:13
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
	char* oldpath;	//老文件
	char* newpath;	//新文件

	//参数合法性检查
	if(argc != 3)
	{
		printf("\"mv <old file> <new file>\"\n");
		exit(1);
	}
	oldpath = argv[1];
	newpath = argv[2];

	if(rename(oldpath,newpath) == -1)
	{
		seerror("mv",__LINE__);
		exit(1);
	}


	return 0;
}
