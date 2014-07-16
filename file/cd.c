/*=============================================================================
#   >>   文件名: cd.c
#   >> 	   描述: 切换线程的工作目录
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://hi.baidu.com/wangbo2008
#   >>   Github: hithub.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-16 20:41:56
#   >> 修改时间: 2014-07-16 21:12:05
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
	char* path;//目标路径

	//参数合法性检测
	if(argc != 2)
	{
		printf("cd <new path>\n");
		exit(1);
	}

	path = argv[1];

	if(chdir(path) == -1)
	{
		seerror("cd",__LINE__);
		exit(1);
	}

	if((path = getcwd(NULL,0)) == NULL)
	{
		seerror("pwd",__LINE__);
		exit(1);
	}

	printf("%s\n",path);

	free(path);


	return 0;
}
