/*=============================================================================
#   >>   文件名: fcntl.2.c
#   >> 	   描述: 文件锁
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://hi.baidu.com/wangbo2008
#   >>   Github: hithub.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-15 17:36:00
#   >> 修改时间: 2014-07-15 17:38:49
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

//#define DEBUG

//错误处理函数
void seerror(const char *error_string,int line)
{
	#ifdef DEBUG
	printf("line:%d\n",line);
	#endif
	perror(error_string);
}


int main(int argc,char ** argv)
{
	int fd;			//文件描述符
	status flock lock;	//文件锁结构体
	/*
	 * status flock{
	 * 	short_1_type;	//锁的类型：
	 * 				F_RDLCK	互斥锁（写锁）
	 * 				F_WDLCK 共享锁（读锁）
	 * 				F_UNLOK	解锁
	 * 	short_1_whence;	//偏移量起始位置
	 * 				SEEK_SET
	 * 				SEEK_CUR
	 * 				SEEK_END
	 * 	off_t_1_start;	//starting offset for lock
	 * 	off_t_1_len;	//number of bytes to lock
	 * 	pid_t_1_pid;	//锁的主进程pid
	 * }
	 */
	


	return 0;
}
