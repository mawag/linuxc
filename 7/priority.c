/*=============================================================================
#   >>   文件名: priority.c
#   >> 	   描述: 用户进程优先级查询修改
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://www.cnblogs.com/wangbo2008/
#   >>   Github: github.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-24 08:38:26
#   >> 修改时间: 2014-07-24 08:38:26
#  Copyright (c) wangbo  All rights reserved.
=============================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#define DEBUG

//显示错误信息
void seerror(const char* error_string,int line)
{
        #ifdef DEBUG
	printf("line:%d\n",line);
        #endif
        perror(error_string);
}


int main(int argc,char **argv)
{
	pid_t pid;
	int pri;

	if((pri = getpriority(PRIO_PROCESS,getpid())) == -1)
	{
		seerror("getpriority",__LINE__);
		exit(1);
	}

	printf("id is %d priority is:%d\n",getpid(),pri);
	if((pri = getpriority(PRIO_USER,getuid())) == -1)
	{
		seerror("getpriority",__LINE__);
		exit(1);
	}
	printf("uid is %d priority is:%d\n",getuid(),pri);

	return 0;
}

