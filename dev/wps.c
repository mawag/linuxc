/*=============================================================================
#   >>   文件名: wps.c
#   >> 	   描述: wps
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://hi.baidu.com/wangbo2008
#   >>   Github: hithub.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-17 20:22:55
#   >> 修改时间: 2014-07-21 09:16:41
#  Copyright (c) wangbo  All rights reserved.
=============================================================================*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define WORD_ADD "wps"

#define PPT_ADD "wpt"

#define EXCEL_ADD "et"


//参数
typedef struct parameter
{
	int w;//word
	int p;//ppt
	int e;//excel
}par;


//参数<全局变量>
par opt;
int ss(char path[],int n);
int rr(char path[],int t);
int wopen(char *path,int x);


//提示并打开
int wopen(char *path,int x)
{
	char filename[]="★";
	int i;
	int c_ct=34;//框体颜色
	printf("\033[0m");
	printf("\033[1;%dm┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n",c_ct);
	printf("\033[1;%dm┃                 \033[1;36m@   @   @    @@@@@@@@@    @@@@@@@@@\033[1;%dm                    ┃\n",c_ct,c_ct);
	printf("\033[1;%dm┃                 \033[1;36m@   @   @    @       @    @        \033[1;%dm                    ┃\n",c_ct,c_ct);
	printf("\033[1;%dm┃                 \033[1;36m @ @ @ @     @@@@@@@@@    @@@@@@@@@\033[1;%dm                    ┃\n",c_ct,c_ct);
	printf("\033[1;%dm┃                 \033[1;36m @ @ @ @     @                    @\033[1;%dm                    ┃\n",c_ct,c_ct);
	printf("\033[1;%dm┃                 \033[1;36m  @   @      @            @@@@@@@@@\033[1;%dm          ver:0.1   ┃\n",c_ct,c_ct);
	printf("\033[1;%dm┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n",c_ct);

	printf("\033[1;%dm┃                                                                        \033[1;%dm┃\n",c_ct,c_ct);
	printf("\033[1;%dm┃\033[1;36m         ① wps文字             ② wpp演示           ③ et表格             \033[1;%dm┃\n",c_ct,c_ct);
	printf("\033[1;%dm┃                                                                        \033[1;%dm┃\n",c_ct,c_ct);
	printf("\033[1;%dm┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n",c_ct);
	printf("\033[1;%dm┃                                                                        ┃\n",c_ct);
	printf("\033[1;%dm┃\033[1;36m      欢迎使用办公文件智能辅助系统                                      \033[1;%dm┃\n",c_ct,c_ct);
	printf("\033[1;%dm┃                                                                        ┃\n",c_ct);
	if(path == NULL)
	{
	printf("┃\033[1;36m      您尚未指定要打开的文件。                                          \033[1;%dm┃\n",c_ct);
	printf("┃                                                                        ┃\n");
	}
	else
	{
	printf("┃\033[1;36m      您输入的文件为: \033[1;32m%-50s\033[1;%dm┃\n",path,c_ct);
	printf("┃                                                                        ┃\n");
	}
	if(x == 0)
	printf("┃\033[1;36m      系统无法找到对应的软件打开，请输入数字选择相应的软件打开。        \033[1;%dm┃\n",c_ct);
	else
	printf("┃\033[1;36m      系统正在打开相应软件，请稍后。。。                                \033[1;%dm┃\n",c_ct);
	printf("┃                                                                        ┃\n");

	printf("┃");
	for(i = 0;i<12;i++)
	{
		printf("\033[1;5;31m%s\033[0m",filename);
		printf("\033[1;32m%s\033[0m",filename);
		printf("\033[1;5;33m%s\033[0m",filename);
		printf("\033[1;34m%s\033[0m",filename);
		printf("\033[1;5;35m%s\033[0m",filename);
		printf("\033[1;36m%s\033[0m",filename);
	}
	printf("\033[1;%dm┃\n",c_ct);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\033[0m\n");


	printf("\n");

	return 0;

}

//根据返回值类型使用特定程序打开文件
int rr(char path[],int t)
{
	int choose;
	char t1[80];
	pid_t pid;

	wopen(path,t);
	if(t == 0)
	{
	        while(t == 0)
	        {
			printf("Please input your choose:\033[1;4m");
        		scanf("%d",&choose);
			printf("\033[0m");
			switch(choose)
			{
				case 1:
					t = 1;
					break;
				case 2:
					t = 2;
					break;
				case 3:
					t = 3;
					break;
				case 4:
					printf("\033[0m");
					exit(0);
				case 0:
					printf("\033[0m");
					exit(0);
				default:
					break;
			}
		}
	}
	//系统命令组合中
	if(t == 1)
		strcpy(t1,WORD_ADD);
	else if(t == 2)
		strcpy(t1,PPT_ADD);
	else if(t == 3)
		strcpy(t1,EXCEL_ADD);
	if(path != NULL)
	{
		strcat(t1," ");
		strcat(t1,path);
	}

	printf("\033[0m");

	pid = vfork();

	if(pid == 0)
	{
		system(t1);
		exit(0);
	}

	return 0;
}

//根据后缀判断文件类型，并选择指定软件打开
int ss(char path[],int n)
{
	int i;
	char tmp[30];
	for(i = n;path[i] != '.';i-- );

	//printf("%d,%s\n",i,(char *)&(path[i+1]));
	strcpy(tmp,((char *)&(path[i+1])));

	if 	 ((strcmp("doc",tmp) == 0) || (strcmp("docx",tmp) == 0)\
		||(strcmp("wps",tmp) == 0) || (strcmp("wpt",tmp) == 0) \
		||(strcmp("dot",tmp) == 0) || (strcmp("txt",tmp) == 0) \
		||(strcmp("md",tmp) == 0)  || (strcmp("rtf",tmp) == 0) \
		||(strcmp("html",tmp) == 0)|| (strcmp("docx",tmp) == 0))
		rr(path,1);
	else if	 ((strcmp("dps",tmp) == 0) || (strcmp("dpt",tmp) == 0)\
		||(strcmp("ppt",tmp) == 0) || (strcmp("pot",tmp) == 0) \
		||(strcmp("pps",tmp) == 0) || (strcmp("pptx",tmp) == 0) \
		||(strcmp("potx",tmp) == 0)  || (strcmp("ppsx",tmp) == 0))
		rr(path,2);
	else if	 ((strcmp("et",tmp) == 0) || (strcmp("ett",tmp) == 0)\
		||(strcmp("xlt",tmp) == 0) || (strcmp("xl",tmp) == 0))
		rr(path,3);
	else
		rr(path,0);
	return 0;
}


int main(int argc,char ** argv)
{
	int flag;
	int i;
	char *path;
	char *r;
	char run[80];
	//参数初始化
	opt.w = 0;
	opt.p = 0;
	opt.e = 0;

	opterr = 0;	//getopt不输出错误参数



	//循环处理传入参数
	while(flag != -1)
	{
		//调用getopt处理参数
		switch(getopt( argc, argv, "wpe"))
		{
			case 'w':
				opt.w = 1;
				break;
			case 'p':
				opt.p = 1;
				break;
			case 'e':
				opt.e = 1;
				break;
			case -1:
				flag = -1;
				break;
			case '?':
				printf("出现非正常选项：%c，系统将忽略.\n",optopt);
				break;
			default:
				break;
		}
	}
	#ifdef DEBUG
	printf("%dand%d\n",argc,optind);
	#endif
	if((argc - optind) < 1)
	{
		if(opt.w == 1)
		{
			rr(NULL,1);
		}
		else if(opt.p == 1)
		{
			rr(NULL,2);
		}
		else if(opt.e == 1)
		{
			rr(NULL,3);
		}
		else
		{
			rr(NULL,0);
		}
	}
	else
	{
		path = argv[optind];
		ss(path,strlen(argv[optind]));
	}


	return 0;
}
