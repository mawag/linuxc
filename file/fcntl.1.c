/*=============================================================================
#   >>   文件名: fcntl.1.c
#   >> 	   描述: 获取文件打开方式
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://hi.baidu.com/wangbo2008
#   >>   Github: hithub.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-15 16:10:09
#   >> 修改时间: 2014-07-15 17:35:49
#  Copyright (c) wangbo  All rights reserved.
=============================================================================*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

//#define DEBUG

void seerror(const char *error_string,int line)
{
	#ifdef DEBUG
	printf("line:%d\n",line);
	#endif
	perror(error_string);
}

int main(int argc,char ** argv)
{
	int fd;		//文件标示符
	char* filename;	//文件名
	int flag;	//文件打开标示位

	//参数初始化
	if(argc == 1)
	{
		printf("input file name:");
		filename = malloc (50);
		gets(filename);
	}
	else
	{
		filename = argv[1];
	}

	printf("请输入文件打开方式：1，只读，2，只写，3，可读可写.\t");
	scanf("%d",&flag);

	switch(flag)
	{
		case 1:
			if((fd = open(filename,O_RDONLY))== -1)
			{
				seerror("open",__LINE__);
				exit(1);
			}
			break;
		case 2:
			if((fd = open(filename,O_WRONLY))== -1)
			{
				seerror("open",__LINE__);
				exit(1);
			}
			break;
		case 3:
			if((fd = open(filename,O_RDWR))== -1)
			{
				seerror("open",__LINE__);
				exit(1);
			}
			break;
	}

	printf("请输入文件打开方式的第三个参数：\n1，追加，2，非阻塞，3，异步.\t");
	scanf("%d",&flag);

	switch(flag)
	{
		case 1:
			if(fcntl(fd,F_SETFL,O_APPEND)== -1)
			{
				seerror("fcntl",__LINE__);
				exit(1);
			}
			break;
		case 2:
			if(fcntl(fd,F_SETFL,O_NONBLOCK)== -1)
			{
				seerror("fcntl",__LINE__);
				exit(1);
			}
			break;
		case 3:
			if(fcntl(fd,F_SETFL,O_ASYNC)== -1)
			{
				seerror("fcntl",__LINE__);
				exit(1);
			}
			break;
	}


	//调用fcntl，使用第二个参数为 F_GETFL,使用返回值
	if((flag = fcntl(fd,F_GETFL)) < 0)
	{
		seerror("fcntl",__LINE__);
		exit(1);
	}

	if(close(fd) == -1)
	{
		seerror("close",__LINE__);
		exit(1);
	}

	//显示文件打开方式
	/*
	 * O_ACCMODE取得打开文件方式的掩码，实际值为3
	 * 和flag做与运算，是为了取得flag的最后两位的值
	 */
	switch(flag & O_ACCMODE)
	{
		case O_RDONLY:
			printf("%s access mode :read only(只读) ",filename);
			break;
		case O_WRONLY:
			printf("%s access mode :write only(只写) ",filename);
			break;
		case O_RDWR:
			printf("%s access mode :read and write(读写) ",filename);
			break;
	}
	if (flag & O_APPEND)
	{
		printf (", append(追加)");
	}

	if (flag & O_NONBLOCK)
	{
		printf (", nonblock(非阻塞)");
	}

	if (flag & O_SYNC)
	{
		printf (", sync(异步)");
	}

	printf("\n");


	return 0;
}
