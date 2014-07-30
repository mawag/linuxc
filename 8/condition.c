/*=============================================================================
#   >>   文件名: condition.c
#   >> 	   描述: 条件变量
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://www.cnblogs.com/wangbo2008/
#   >>   Github: github.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-28 20:34:26
#   >> 修改时间: 2014-07-28 20:34:26
#  Copyright (c) wangbo  All rights reserved.
=============================================================================*/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t	mutex;
pthread_cond_t	cond;

void *thread1(void *arg)
{

	pthread_cleanup_push (pthread_mutex_unlock, &mutex);

	while(1)
	{
		printf ("thread1 is running\n");
		//添加互斥锁
		pthread_mutex_lock (&mutex);
		//条件变量
		pthread_cond_wait (&cond, &mutex);
		printf ("thread1 applied the condition\n");
		//去掉互斥锁
		pthread_mutex_unlock (&mutex);
		sleep (4);
	}

	pthread_cleanup_pop (0);
}

void *thread2(void *arg)
{
	while(1)
	{
		printf ("thread2 is running\n");
		//添加互斥锁
		pthread_mutex_lock (&mutex);
		//等待条件成立
		pthread_cond_wait (&cond, &mutex);
		printf ("thread2 applied the condition\n");
		//解除互斥锁
		pthread_mutex_unlock (&mutex);
		sleep (1);
	}
}

int main(void)
{
	pthread_t tid1, tid2;

	printf ("condition variable study! \n");
	//初始化互斥锁
	pthread_mutex_init (&mutex, NULL);
	//初始化条件变量
	pthread_cond_init (&cond, NULL);
	//创建子线程
	pthread_create (&tid1, NULL, (void *) thread1, NULL);
	pthread_create (&tid2, NULL, (void *) thread2, NULL);

	do
	{
		//激活等待的线程
		pthread_cond_signal (&cond);
	} while (1);

	sleep (6);
	pthread_exit (0);
}
