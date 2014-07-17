/*=============================================================================
#   >>   文件名: ls.c
#   >> 	   描述: ls的简单实现
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://hi.baidu.com/wangbo2008
#   >>   Github: hithub.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-17 20:22:55
#   >> 修改时间: 2014-07-17 20:22:55
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
#include <linux/limits.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>


//#define DEBUG

//显示错误信息
void seerror(const char* error_string,int line)
{
	#ifdef DEBUG
	printf("line:%d\n",line);
	#endif
	perror(error_string);
}

//展示单个文件信息
int showdirinfo(const struct dirent* ptr)
{
	printf("%s\t",ptr->d_name);
}

//读取文件夹内文件并输出
int showdir(const char* path)
{
	DIR		* dir;
	struct dirent	* ptr;
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

	if ((dir = opendir(path)) == NULL) 
	{
		seerror("opendir",__LINE__);
		return 1;
	}

	while ((ptr = readdir(dir))!=NULL) 
	{
		showdirinfo(ptr);
	}

	closedir(dir);

	return 0;
}


int main(int argc,char ** argv)
{
	int i;		//循环变量
	int flag;	//标志位
	char* path;
	/*
	 *	参数设置
	 *	参数解析方案：
	 *
	 *	1，建立结构体，结构体内直接用数字说明状态
	 *	2，设置int型参数位，通过按位运算来解析参数
	 *	这里暂时使用方案1
	 *
	 */
	struct param
	{
		int p_i;//i参数
		int p_l;//l参数
		int p_a;//a参数
	}


	flag = 0;
	//解析参数

	//获取参数目录信息
	for(i=1;i<argc;i++)
	{
		if(argv[i][0] != '-')
		{
			flag = 1;
			path = argv[i];
			showdir(path);
		}
	}

	if(flag == 0)
	{
		path = ".";
		return (showdir(path));
	}


	return 0;
}
