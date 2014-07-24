/*=============================================================================
#   >>   文件名: studyid.c
#   >> 	   描述: 
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://www.cnblogs.com/wangbo2008/
#   >>   Github: github.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-24 08:18:30
#   >> 修改时间: 2014-07-24 08:18:31
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
#include <time.h>

int main(int argc,char **argv)
{
	int fd;

	printf("uid study:\n");
	printf("uid:%d,euid:%d\n",getuid(),geteuid());

	if((fd = open("test",O_RDWR)) == -1)
	{
		printf("open file,errno is %d:%s\n",errno,strerror(errno));
		exit(1);
	}
	else
	{
		printf("open successfully!\n");
	}
	close(fd);

	setuid(getuid());

	printf("uid study:\n");
	printf("uid:%d,euid:%d\n",getuid(),geteuid());
	if((fd = open("test",O_RDWR)) == -1)
	{
		printf("open file,errno is %d:%s\n",errno,strerror(errno));

		exit(1);
	}
	else
	{
		printf("open successfully!\n");
	}

	close(fd);

	return 0;
}

