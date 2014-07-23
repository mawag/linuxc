/*=============================================================================
#   >>   文件名: difvfork.c
#   >> 	   描述: vfork和fork比较
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://www.cnblogs.com/wangbo2008/
#   >>   Github: github.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-21 16:48:27
#   >> 修改时间: 2014-07-21 16:50:25
#  Copyright (c) wangbo  All rights reserved.
=============================================================================*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>



int main(int argc,char ** argv)
{
	int i,j;
	int test =0;
	pid_t pid;

	pid = getpid();
	printf("进程id为%d\n",pid);
	pid = getppid();
	printf("父进程为:%d\n",pid);
	pid = getuid();
	printf("实际用户id为:%d\n",pid);
	pid = geteuid();
	printf("有效用户id为%d\n",pid);
	pid = getgid();
	printf("实际组id:%d\n",pid);
	pid = getegid();
	printf("有效用户id:%d\n",pid);

	//pid = fork();
	pid = vfork();

	for(i = 0;i<6;i++)
	{
		if(pid != 0)
		{
			test+=2;
			printf("father,test=%d,mysalf id:%d,father id:%d,will exit\n",test,getpid(),getppid());
			if(i == 3)
				exit(0);
		}
		else
		{
			test++;
			printf("son,test=%d,",test);
			printf("mysalf id:%d,father id:%d\n",getpid(),getppid());
			if(i == 5)
				exit(0);
		}
		sleep(1);
	}

	return 0;
}
