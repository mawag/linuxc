/*=============================================================================
#   >>   文件名: fork.c
#   >> 	   描述:
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://www.cnblogs.com/wangbo2008/
#   >>   Github: github.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-21 14:57:58
#   >> 修改时间: 2014-07-21 14:57:58
#  Copyright (c) wangbo  All rights reserved.
=============================================================================*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

//fork创建新进程

int main(int argc,char ** argv)
{
	int i;
	pid_t pid;

	pid = getpid();
	printf("myself id:%d\n",pid);
	pid = getppid();
	printf("my father id:%d\n",pid);
	pid = getuid();
	printf("userid:%d\n",pid);
	pid = geteuid();
	printf("do userid:%d\n",pid);
	pid = getgid();
	printf("group id:%d\n",pid);
	pid = getegid();
	printf("do group id:%d\n",pid);

	pid = fork();
	printf("f id:%d\n",pid);


	for(i = 0;i<10;i++)
	{
		if(pid == 0)
			printf("son\n");
		else
			printf("father!\n");
		//sleep(1);

	}

	return 0;
}
