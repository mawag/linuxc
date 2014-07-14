/*=============================================================================
#   >>   文件名: mycat.c
#   >> 	   描述: 
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://hi.baidu.com/wangbo2008
#   >>   Github: hithub.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-13 17:30:44
#   >> 修改时间: 2014-07-13 18:57:36
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

void seerror(const char *error_string,int line)
{
	printf("line:%d\n",line);
	perror(error_string);
}

int main(int argc,char ** argv)
{
	int i,j;		//循环变量
	int len;		//文件长度
	char *path;		//文件名
	int fd;			//文件描述符标识
	char *file;		//文件内容
	int flag = 0;		//参数

	//参数初始化
	if(argc == 1)
	{
		printf("\"cat <file name>\"\n");
		exit(1);
	}
	if(argc > 2)
	{
		for( i = 1; i < argc; i++)
		{
			if (argv[i][0] == '-')
			{
				for( j = 1; argv[i][j] != '\0'; j++)
				{
					//参数部分
					if(argv[i][j] == 'n')
						flag += 1;
					//else if(argv[i][j])
				}
			}
			else
				path = argv[i];
		}
	}
	if(argc == 2)
	{
		path = argv[1];
		if(path[0] == '-')
		{
			printf("cat <file name> \n");
			exit(1);
		}
	}
	#ifdef DEBUG
	printf("file name:%s\n",path);
	#endif

	//检查文件，读取
	/*特别注意*/
	/*运算符优先级问题！！！*/
	if((fd = open(path,(O_RDONLY))) == -1)
	//if((fd = creat (path,mode)) == -1)
	{
		if(2 == errno)
		{
			perror("open");
			printf("Do you want to creat new file ? ");
			if(getchar() == 'y')
				if(creat(path,777) == -1)
				{
					perror("creat");
					exit(1);
				}
			else exit(1);
		}
		else
		{
			seerror("open",__LINE__);
			exit(1);
		}
	}

	//获取文件长度
	if(lseek(fd,0,SEEK_END) == -1)
	{
		seerror("lseek",__LINE__);
		exit(1);
	}
	if((len = (lseek(fd,0,SEEK_CUR)))== -1)
	{
		seerror("lseek",__LINE__);
		exit(1);
	}
	if(lseek(fd,0,SEEK_SET) == -1)
	{
		seerror("lseek",__LINE__);
		exit(1);
	}

	if((file = malloc (len)) == NULL)
	{
		seerror("malloc",__LINE__);
		exit(1);
	}
	if((read(fd,file,len)) == -1)
	{
		seerror("read",__LINE__);
		exit(1);
	}

	//显示文件
	j = 0;
	printf("filename:%s\ntype:%d\n",path,len);
	printf(">>	start\n");
	for(i=0;i<len;i++)
	{
		if(*(file - 1) == '\n')
			printf("%3d:",j++);
		printf("%c",*file++);
	}
	printf(">>	end\n");

	if(close(fd) == -1)
	{
		seerror("creat",__LINE__);
		exit(1);
	}

	return 0;
}

