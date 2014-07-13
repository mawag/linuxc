/*=============================================================================
#   >>   文件名: mychmod.c
#   >> 	   描述: 
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://hi.baidu.com/wangbo2008
#   >>   Github: hithub.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-13 11:56:12
#   >> 修改时间: 2014-07-13 13:12:16
#  Copyright (c) wangbo  All rights reserved.
=============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
//#define DEBUG

int main(int argc, char ** argv)
{
	int mode;	//权限
	int mode_u;	//所有者权限
	int mode_g;	//用户组权限
	int mode_o;	//其他权限
	char *path;

	//参数合法性检测
	if(argc < 3)
	{
		printf("please input \"%s <mode number> <file name>\"\n", argv[0]);
		exit(0);
	}

	//获取参数
	mode = atoi(argv[1]);
	if (mode > 777 || mode < 0)
	{
		printf("mode number error!\n");
		exit(0);
	}
	mode_u = mode / 100;
	mode_g = ( mode - mode_u * 100) / 10;
	mode_o = mode % 10;
	path = argv[2];
	mode = mode_u * 8 * 8 + mode_g * 8 +mode_o;

	#ifdef DEBUG
	printf("path:%s\nmode:%d-%d-%d\nmode=%d\n",path,mode_u,mode_g,mode_o,mode);
	#endif

	//权限更改，错误检测
	if( chmod(path,mode) != 0)
	{
		perror("");		//错误情况输出
		exit(1);
	}

	#ifdef DEBUG
	system("ls -al");
	#endif

	return 0;
}
