/*=============================================================================
#   >>   文件名: getopt.c
#   >> 	   描述: getopt的简单使用
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://hi.baidu.com/wangbo2008
#   >>   Github: hithub.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-17 23:04:18
#   >> 修改时间: 2014-07-18 08:48:43
#  Copyright (c) wangbo  All rights reserved.
=============================================================================*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct parameter
{
	int       a;		//参数a
	int       b;		//参数b
	char *b_pri;		//参数b的关联值
	int       c;		//参数c
	char *c_pri;		//参数c的关联值
}par;


int main( int argc, char **argv )
{
	int i;		//循环变量
	par opt;	//参数
	int flag = 0;	//循环退出标志位

	//参数初始化
	opt.a = 0;
	opt.b = 0;
	opt.b_pri = NULL;
	opt.c = 0;
	opt.c_pri = NULL;
	opterr = 0;	//getopt不输出错误参数

	//参数检测
	if (argc == 1)
	{
		printf("您没有设置选项！\n");
		exit(0);
	
	}
	//输出未处理的参数
	printf("系统传入的参数为:");
	for ( i = 1; i < argc; i++)
	{
		printf("%s ",argv[i]);
	}
	printf("\n");

	//循环处理传入参数
	while(flag != -1)
	{
		//调用getopt处理参数
		switch(getopt( argc, argv, "ab:c::"))
		{
			case 'a':
				opt.a = 1;
				break;
			case 'b':
				opt.b = 1;
				opt.b_pri = optarg;
				break;
			case 'c':
				opt.c = 1;
				opt.c_pri = optarg;
				break;
			case '?':
				printf("出现非正常选项：%c\n",optopt);
				break;
			case -1:
				flag = -1;
				break;
			default:
				break;
		}
	}

	if( optind != argc)
	{
		printf("参数中非程序选项的有:");
		for (i = optind; i < argc; i++)
		{
			printf("%s\t",argv[i]);
		}
		printf("\n");
	}

	//输出解析结果
	printf("解析到程序启动后启用的选项有：");
	if (opt.a == 1)
		printf("a,");
	if (opt.b == 1)
		printf("b(参数为:%s),",opt.b_pri);
	if (opt.c == 1)
		printf("c(参数为:%s),",opt.c_pri);
	printf("\n");


	//处理后，输出全部参数与原来对比
	printf("使用getopt后，系统参数变为为:");
	for ( i = 1; i < argc; i++)
	{
		printf("%s ",argv[i]);
	}
	printf("\n");

	return 0;
}
