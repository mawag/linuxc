/*=============================================================================
#   >>   文件名: creatfile.c
#   >> 	   描述: 
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://hi.baidu.com/wangbo2008
#   >>   Github: hithub.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-13 16:00:44
#   >> 修改时间: 2014-07-13 16:59:32
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

#define DEBUG

int main(int argc,char ** argv)
{
	int mode;		//权限
	int mode_u;		//所有者权限
	int mode_g;		//用户组权限
	int mode_o;		//其他用户权限
	char *path;		//文件名
	int fd;			//文件描述符标识

	//参数初始化
	if(argc == 1)
	{
		printf("Please input \"creat <new file name> <mode>\"or \"creat <new file name>\"\n");
		exit(1);
	}
	else if(argc == 2)
	{
		mode = 777;
	}
	else if(argc == 3)
	{
		mode = atoi(argv[2]);
	}
	mode_u = mode / 100;
	mode_g = (mode % 10) % 10;
	mode_o = mode % 10;
	mode = mode_u * 8 * 8 + mode_g * 8 + mode_o;
	path = argv[1];
	#ifdef DEBUG
	printf("%d\n",mode);
	printf("file name:%s\nmode:%d-%d-%d\n",path,mode_u,mode_g,mode_o);
	#endif

	if(fd = open(path,(O_RDONLY|O_CREAT|O_EXCL),mode) == -1)
	//if(fd = creat (path,mode) == -1)
	{
		printf("%s:%s\n",argv[0],strerror(errno));
		exit(1);
	}
	if(close(fd) == -1)
	{
		perror("creat");
		exit(1);
	}

	return 0;
}

