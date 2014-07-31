/*=============================================================================
#   >>   文件名: condition.c
#   >> 	   描述: 条件变量
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://www.cnblogs.com/wangbo2008/
#   >>   Github: github.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-30 18:09:53
#   >> 修改时间: 2014-07-30 18:09:53
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
pthread_cond_t cond_t;
pthread_mutex_t mutex_t;

void fun2(void *arg)
{

	while(1)
	{
		pthread_mutex_lock(&mutex_t);
		/*if(pthread_mutex_trylock(&mutex_t) == EBUSY)
		{
			printf("地板抢不到，等会!\n");
			return ;
		}
		*/
		//等待条件变量
		pthread_cond_wait(&cond_t,&mutex_t);
		if(key%2==0)
		{
			printf("我是fun2!\n");
			printf("我(%lu)为%d带盐!\n",pthread_self(),key);
		}
		pthread_mutex_unlock(&mutex_t);
	}
}

void fun1(void *arg)
{
	while(1)
	{
		//加锁,普通锁
		pthread_mutex_lock(&mutex_t);
		//pthread_mutex_trylock(&mutex_t);

		pthread_cond_wait(&cond_t,&mutex_t);
		if(key%2 == 1)
		{
			printf("我是fun1，我来了。\n");

			printf("板凳(%lu)上写着:%d\n",pthread_self(),key);
		}
		pthread_mutex_unlock(&mutex_t);
	}
}

int main(int argc,char **argv)
{
	pthread_t thid1,thid2;
	int *status;


	//条件变量初始化
	pthread_cond_init(&cond_t,NULL);
	//线程锁初始化
	pthread_mutex_init(&mutex_t,PTHREAD_MUTEX_TIMED_NP);
	key = 0;

	printf("主线程runing!\n");

	pthread_create(&thid1,NULL,(void*)&fun1,NULL);
	pthread_create(&thid2,NULL,(void*)&fun2,NULL);

	while(1)
	{
		printf("条件变量测试，输入数字，奇数fun1,其他fun2，并进行输出。(0退出)\n");
		printf("请输入指令：");
		scanf("%d",&key);
		if(key == 0)
			break;
		pthread_cond_broadcast(&cond_t);
		sleep(1);
	}

	printf("主线程exiting!\n");
	//清除锁
	pthread_mutex_destroy(&mutex_t);
	return 0;
}

