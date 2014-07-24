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
void explain_input(char *buf, int *argcount, char arglist[100][256]);	/* 对输入命令进行解析 */
void do_cmd(int argcount, char arglist[100][256]);				/* 执行命令 */
int  find_command(char *command);				/* 查找命令中的可执行程序 */

//打印提示符
void print_prompt(void)
{
	char *path;
	char hostname[32];
	char *loginname;
	char *ps;

	if(!(loginname = getenv("LOGNAME")))
	{
		seerror("getenv",__LINE__);
		exit(1);
	}

	if(gethostname(hostname,sizeof(hostname)))
	{
		seerror("gethostname",__LINE__);
		exit(1);
	}

	if(!(path = getenv("PWD")))
	{
		seerror("getenv",__LINE__);
		exit(1);
	}



	printf("%s@%s:%s $",loginname,hostname,path);
}

//得到输入的命令
void get_input(char *buf)
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
void explain_input(char *buf, int *argcount, char a[100][256])
{
	int i,j;
	int d;

	j = 0;
	d = 0;
	for(i = 0;*(buf+i)!= '\0';i++)
	{
		if(*(buf+i) != ' ')
		{
			a[d][j]=*(buf+i);
			j++;
		}
		else
		{
			d++;
			j = 0;
		}
	}
	*argcount = d;

	#ifdef DEBUG
	for(i = 0;i<d+1;i++)
	printf("%s\n",a[i]);
	#endif
}


/* 执行命令 */
void do_cmd(int argcount, char arglist[100][256])
{
	int i;

}

/* 查找命令中的可执行程序 */
int  find_command(char *command);


int main(int argc,char **argv)
{
	char *buf;//记录输入的命令
	int argcount;//记录参数个数
	char arglist[100][256];//解析出来的参数

	buf = malloc(256);
	if(buf == NULL)
	{
		seerror("malloc",__LINE__);
		exit(1);
	}
	do
	{
		print_prompt();
		memset(buf,0,256);
		get_input(buf);
		#ifdef DEBUG
		printf("buf = %s\n",buf);
		#endif
		if((strcmp("exit",buf) == 0)||(strcmp("logout",buf) ==0))
			exit(0);
		argcount = 0;
		for(i = 0;i<100;i++)
		{
			arglist[i][0]= '\0';
		}
		explain_input(buf,&argcount,arglist);
		printf("%d,%s\n",argcount+1,arglist[0]);
		do_cmd(argcount,arglist);
	}while(1);

	exit(1);
}

