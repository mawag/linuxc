/*=============================================================================
#   >>   文件名: myshell.c
#   >> 	   描述: shell简单实现
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://www.cnblogs.com/wangbo2008/
#   >>   Github: github.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-24 09:05:48
#   >> 修改时间: 2014-07-24 09:05:48
#  Copyright (c) wangbo  All rights reserved.
=============================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#define DEBUG

//显示错误信息
void seerror(const char* error_string,int line)
{
	#ifdef DEBUG
	printf("line:%d\n",line);
	#endif
	perror(error_string);
}

void print_prompt(void);					/* 打印提示符 */
void get_input(char *buf);					/* 得到输入的命令 */
void explain_input(char *buf, int *n, char a[][]);		/* 对输入命令进行解析 */
void do_cmd(int n, char a[][]);				/* 执行命令 */
int  find_command(char *);				/* 查找命令中的可执行程序 */

//打印提示符
void print_prompt(void)
{
	char *path;
	char *hostname;
	char *loginname;
	char *ps;

	if(!(loginname = getenv("LOGNAME")))
	{
		seerror("getenv",__LINE__);
		exit(1);
	}

//	if(gethostname(hostname,8) == -1)
//	{
//		seerror("gethostname",__LINE__);
//		exit(1);
//	}

	if(!(path = getenv("PWD")))
	{
		seerror("getenv",__LINE__);
		exit(1);
	}



	printf("%s %s:$",loginname,path);
}

//得到输入的命令
void get_input(char *buf);
{
	int i = 0;
	char ch;

	ch = getchar();
	while(ch != '\n')
	{
		buf[i++] = ch;
		ch = getchar();
	}
}

/* 对输入命令进行解析 */
void explain_input(char *, int *, char a[ ][ ]);


/* 执行命令 */
void do_cmd(int, char a[ ][ ]);


/* 查找命令中的可执行程序 */
int  find_command(char *);


int main(int argc,char **argv)
{
	char *buf;
	print_prompt();
	buf = malloc(256);
	get_input(buf);
	#ifdef DEBUG
	printf("buf = %s\n",buf);
	#endif
	explain_input();

	return 0;
}

