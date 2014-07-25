/*=============================================================================
#   >>   文件名: showdir.c
#   >> 	   描述: 展示文件夹信息
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://hi.baidu.com/wangbo2008
#   >>   Github: hithub.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-17 19:53:17
#   >> 修改时间: 2014-07-17 19:53:17
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
#include <dirent.h>

#define DEBUG

//显示错误信息
void seerror(const char* error_string,int line)
{
	#ifdef DEBUG
	printf("line:%d\n",line);
	#endif
	perror(error_string);
}


int main(int argc,char ** argv)
{
	DIR* dir;		//目录
	struct dirent* t_dir;
	/*
	 *	struct dirent
	 *	{
	 *		long d_ino; 			索引节点号
	 *		off_t d_off; 			在目录文件中的偏移
	 *		unsigned short d_reclen;	文件名长
	 *		unsigned char d_type; 		文件类型
	 *		char d_name [NAME_MAX+1]; 	文件名，最长256字符
	 *	}*
	 */
	char* dirname;		//目录名称

	//参数合法性检测
	if(argc == 1)
	{
		dirname = ".";
	}
	else if(argc > 2)
	{
		printf("showdir <dir>\n");
		exit(1);
	}
	else
	{
		dirname = argv[1];
	}

	#ifdef DEBUG
	printf("dirname: %s\n",dirname);
	#endif

	if((dir = opendir(dirname)) == NULL)
	{
		seerror("opendir",__LINE__);
		exit(1);
	}

	while((t_dir = readdir(dir)) != NULL)
	{
		printf("name:%s\n",t_dir->d_name);
	}

	if(closedir(dir) == -1)
	{
		seerror("closedir",__LINE__);
		exit(1);
	}

	return 0;
}
