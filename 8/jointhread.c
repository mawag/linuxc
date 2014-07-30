/*=============================================================================
#   >>   文件名: jointhread.c
#   >> 	   描述: 线程等待与退出
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://www.cnblogs.com/wangbo2008/
#   >>   Github: github.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-28 17:25:03
#   >> 修改时间: 2014-07-28 17:25:03
#  Copyright (c) wangbo  All rights reserved.
=============================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

void fun(void *arg)
{
	printf("i am helping to do some jobs.\n");
	sleep(3);
	pthread_exit(0);
}

int main(int argc,char **argv)
{
	pthread_t pthreaddd;
	int status;

	pthread_create(&pthreaddd,NULL,(void *)&fun,NULL);
	pthread_join(pthreaddd,(void *)&status);
	printf("fun exit is caused %d\n",status);

	return 0;
}

