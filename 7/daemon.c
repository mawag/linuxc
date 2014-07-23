/*=============================================================================
#   >>   文件名: daemon.c
#   >> 	   描述: 守护进程
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://www.cnblogs.com/wangbo2008/
#   >>   Github: github.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-23 14:21:02
#   >> 修改时间: 2014-07-23 14:21:02
#  Copyright (c) wangbo  All rights reserved.
=============================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <syslog.h>

int init_daemon(void)
{
	pid_t pid;
	int i;

	//忽略终端I/O信号，STOP信号
	signal(SIGTTOU,SIG_IGN);
	signal(SIGTTIN,SIG_IGN);
	signal(SIGTSTP,SIG_IGN);
	signal(SIGHUP,SIG_IGN);

	pid = fork();
	if(pid > 0)
		exit(0);
	else
		return -1;

	printf("创建守护进程!\n");
	setsid();

	pid = fork();
	if(pid > 0)
		exit(0);
	else
		return -1;

	for(i = 0;i < NOFILE;close(i++));

	//更换工作目录
	chdir("/");
	//文件屏蔽字设置为0
	umask(0);
	signal(SIGCHLD,SIG_IGN);

	return 0;

}

int main(int argc,char **argv)
{
	time_t now;
	init_daemon();
	syslog(LOG_USER|LOG_INFO,"测试守护进程！\n");
	while(1)
	{
		sleep(8);
		time(&now);
		syslog(LOG_USER|LOG_INFO,"系统时间:\t%s\t\t\n",ctime(&now));
	}
}
