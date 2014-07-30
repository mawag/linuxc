/*=============================================================================
#   >>   文件名: tsd.c
#   >> 	   描述: 线程间私有数据测试
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://www.cnblogs.com/wangbo2008/
#   >>   Github: github.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-28 17:53:44
#   >> 修改时间: 2014-07-28 17:53:44
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

pthread_key_t key;

void fun2(void *arg)
{
	pthread_t thid;
	int tsd = 520;

	printf("我是地板,");
	pthread_setspecific(key,(void*)tsd);

	printf("我(%lu)为%d带盐!\n",pthread_self(),(int )pthread_getspecific(key));

}

void fun1(void *arg)
{
	pthread_t thid;
	int tsd = 2014;

	printf("板凳表示来了！\n");
	pthread_setspecific(key,(void*)tsd);
	pthread_create(&thid,NULL,(void*)&fun2,NULL);

	printf("板凳(%lu)上写着:%d\n",pthread_self(),(int )pthread_getspecific(key));


}

int main(int argc,char **argv)
{
	pthread_t thid;
	int *status;

	printf("主线程runing!\n");
	pthread_key_create(&key,NULL);
	pthread_create(&thid,NULL,(void*)&fun1,NULL);



	pthread_join(thid,(void*)&status);
	pthread_key_delete(key);
	printf("主线程exiting!\n");
	return 0;
}

