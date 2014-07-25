/*=============================================================================
#   >>   文件名: mynice.c
#   >> 	   描述: 课本测试
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://www.cnblogs.com/wangbo2008/
#   >>   Github: github.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-23 15:12:38
#   >> 修改时间: 2014-07-23 15:12:38
#  Copyright (c) wangbo  All rights reserved.
=============================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/wait.h>

int main(void)
{
	pid_t	pid;
	int 		stat_val = 0;
	int 		oldpri, newpri;

	printf("nice study\n");

	pid = fork();
	switch(pid) {
		case 0:
			printf("Child is running,CurPid is %d,ParentPid is %d\n", pid, getppid());

			oldpri = getpriority(PRIO_PROCESS,0);
			printf("Old priority = %d\n",oldpri);

			newpri = nice(2);
			printf("New priority = %d\n",newpri);

			exit(0);
		case -1:
			perror("Process creation failed\n");
			break;
		default:
			printf("Parent is running,ChildPid is %d,ParentPid is %d\n", pid, getpid());
			break;
	}

	wait(&stat_val);
	exit(0);
}
