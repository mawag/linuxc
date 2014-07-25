/*=============================================================================
#   >>   文件名: edit.c
#   >> 	   描述: 简单编辑器
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://hi.baidu.com/wangbo2008
#   >>   Github: hithub.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-14 20:17:13
#   >> 修改时间: 2014-07-14 20:20:38
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

int main(int argc,char ** argv)
{
	int fd;			//文件描述符
	int i,j;		//循环变量
	char file;		//文件内容
	char *filename;		//文件名
	int flag;		//标志位

	//参数合法性检测
	if(argc == 1)
	{
		printf("input file:");
		filename = malloc(50);
		gets(filename);
	}
	else if(argc == 2)
	{
		filename = argv[1];
	}
	else if(argc > 2)
	{
		for( i = 1; i < argc; i++)
		{
			if (argv[i][0] == '-')
			{
				for( j = 1; argv[i][j] != '\0'; j++)
				{
					//参数部分
					if(argv[i][j] == 'r')
						flag += 1;
					else if (argv[i][j] == 'w')
						flag += 2;
					else if (argv[i][j] == ' ')
						break;
					else
					{
						printf("出现不合法的参数\"%c\"，将被忽略！\n",argv[i][j]);
					}
				}
			}
			else
				filename = argv[i];
		}
	}


	//文件效验
	if((fd =(open(filename,(O_RDWR))))== -1)
	{
		if(errno == 2)
		{
			perror("open");
			printf("Do you want to creat a new file?");
			if(getchar() == 'y')
			{
				if((fd = creat(filename,436)) == -1)
				{
					perror("creat");
					exit(1);
				}
			}
			else exit(1);
		}
		else
		{
			perror("open");
			exit(1);
		}
	}

	//文件读取
	i = 0;		//记录行号
	printf("%5d\t",++i);
	do
	{
		flag = read(fd,&file,1);
		if(flag == -1)
		{
			perror("read");
			exit(1);
		}
		printf("%c",file);
		if((file == '\n')&&(flag != 0))
		{
			printf("%5d\t",++i);
		}
	}while (flag == 1);
	printf("\n");
	
	//文件关闭
	if(close(fd) == -1)
	{
		perror("close");
		exit(1);
	}
	
	return 0;
}
