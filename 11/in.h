#ifndef IN_H
#define IN_H
/*=============================================================================
#   >>   文件名: in.h
#   >> 	   描述: in.h
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://www.cnblogs.com/wangbo2008/
#   >>   Github: github.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-08-01 09:58:31
#   >> 修改时间: 2014-08-01 09:58:52
#  Copyright (c) wangbo  All rights reserved.
=============================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <linux/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

//设置服务器ip和端口
#define HOSTIP "127.0.0.1"
#define PORT 8888

//最大请求数目
#define LISTEN_NUM 12

#endif
