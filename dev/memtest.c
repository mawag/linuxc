/*=============================================================================
#   >>   文件名: 2.c
#   >> 	   描述: 内存操作测试
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://www.cnblogs.com/wangbo2008/
#   >>   Github: github.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-23 15:08:16
#   >> 修改时间: 2014-07-23 15:08:16
#  Copyright (c) wangbo  All rights reserved.
=============================================================================*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main (void)
{
	char name[3][6]={"test1","test2","test3"};
	char tmp[5];
	int i,j;
	for(i=0;i<3;i++)
	{
		printf("%s\n",name[i]);
	}

	for(i = 0;i < 3 - 1; i++)
	{
		for( j = i+1; j < 3; j++)
		{
			if(strcmp(name[i],name[j]) < 0)
			{
				memcpy(tmp,name[i],5);
				memcpy(name[i],name[j],5);
				memcpy(name[j],tmp,5);
			}
		}
	}
	for(i=0;i<3;i++)
	{
		printf("%s\n",name[i]);
	}



	return 0;
}
