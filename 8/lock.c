/*=============================================================================
#   >>   文件名: lock.c
#   >> 	   描述: 线程互斥锁
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://www.cnblogs.com/wangbo2008/
#   >>   Github: github.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-28 19:57:09
#   >> 修改时间: 2014-07-28 20:30:40
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

int key;
pthread_mutex_t mutex_t;

void fun2(void *arg)
{
	sleep(1);
	key = 520;
	printf("我是地板,key = %d!\n",key);

	printf("我(%lu)为%d带盐!\n",pthread_self(),key);

}

void fun1(void *arg)
{
	pthread_t thid;

	key = 2014;
	printf("板凳表示来了！\n");

	//加锁,普通锁
	pthread_mutex_lock(&mutex_t);
	//pthread_mutex_trylock(&mutex_t);

	printf("板凳(%lu)上写着:%d\n",pthread_self(),(int )pthread_getspecific(key));
	sleep(3);
	//解锁
	pthread_mutex_unlock(&mutex_t);
	printf("the key is %d\n",key);

}

int main(int argc,char **argv)
{
	pthread_t thid1,thid2;
	int *status;

	//线程锁初始化
	pthread_mutex_init(&mutex_t,PTHREAD_MUTEX_TIMED_NP);

	printf("主线程runing!\n");
	pthread_create(&thid1,NULL,(void*)&fun1,NULL);
	pthread_create(&thid2,NULL,(void*)&fun2,NULL);

	pthread_join(thid1,(void*)&status);
	printf("主线程exiting!\n");
	printf("key = %d\n",key);

	//清除锁
	pthread_mutex_destroy(&mutex_t);
	return 0;
}

