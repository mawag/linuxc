/*=============================================================================
#   >>   文件名: createthread.c
#   >> 	   描述: 创建线程
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://www.cnblogs.com/wangbo2008/
#   >>   Github: github.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-28 14:32:40
#   >> 修改时间: 2014-07-28 15:46:24
#  Copyright (c) wangbo  All rights reserved.
=============================================================================*/
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int *thread(void *arg)
{
	pthread_t newthid;

	newthid = pthread_self();
	printf("this is a new thread, thread ID = %lu\n", newthid);

	return NULL;
}

int main(void)
{
	pthread_t thid;

	thid = pthread_self();
	printf("main thread ,ID is %lu\n",thid);

	if(pthread_create(&thid, NULL,(void *)&thread, NULL) != 0)
	{
		printf("thread creation failed\n");
		exit(1);
	}
	sleep(1);
	exit(0);
}
