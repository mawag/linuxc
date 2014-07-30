/*=============================================================================
#   >>   文件名: oncerun.c
#   >> 	   描述: 双线程限制函数调用一次
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://www.cnblogs.com/wangbo2008/
#   >>   Github: github.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-28 16:14:39
#   >> 修改时间: 2014-07-28 16:14:39
#  Copyright (c) wangbo  All rights reserved.
=============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_once_t once = PTHREAD_ONCE_INIT;

void run(void)
{
	printf("Fuction run is running in thread %lu\n",pthread_self());
}

void * thread1(void *arg)
{
	pthread_t thid=pthread_self();
	printf("Current thread's ID is %lu\n", thid);
	pthread_once(&once,run);
	printf("thread1 ends\n");
}

void * thread2(void *arg)
{
	pthread_t thid=pthread_self();
	printf("Current thread's ID is %lu\n", thid);
	pthread_once(&once, run);
	printf("thread2 ends\n");
}

int main(void)
{
	pthread_t thid1,thid2;

	pthread_create(&thid1,NULL,thread1,NULL);
	pthread_create(&thid2,NULL, thread2,NULL);
	sleep(3);
	printf("main thread exit! \n");
	exit(0);
}
