/*=============================================================================
#   >>   文件名: getenv.c
#   >> 	   描述: getenv简单测试
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://www.cnblogs.com/wangbo2008/
#   >>   Github: github.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-24 16:59:33
#   >> 修改时间: 2014-07-24 16:59:33
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
	char *name;
	char *path;
	char pa[20][50];
	int i,j,k;


	name = getenv("HOSTNAME");
	path = getenv("PATH");

	for(i=0,j=0,k=0;*(path+i)!='\0';i++)
	{
		if(*(path+i)!=':')
		{
			pa[j][k]=*(path+i);
			pa[j][k+1]='\0';
			k++;
		}
		else
		{
			j++;
			k=0;
		}
	}
	pa[j+1][0]='\0';

	printf("hostname = %s\n",name);
	printf("path = %s\n",path);
	for(i=0;pa[i][0]!='\0';i++)
	{
		printf("~~%s\n",pa[i]);
	}

	return 0;
}

