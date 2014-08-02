/*=============================================================================
#   >>   文件名: getip.c
#   >> 	   描述: 获取hostip
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://www.cnblogs.com/wangbo2008/
#   >>   Github: github.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-08-01 09:41:35
#   >> 修改时间: 2014-08-01 09:41:36
#  Copyright (c) wangbo  All rights reserved.
=============================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>


int main(int argc,char **argv)
{
	int i;
	struct hostent *ip;
	//  struct hostent
	//  {
	//	 char *h_name;
	// 	 char **h_aliases;
	// 	 int h_addrtype;
	// 	 int h_length;
	// 	 char **h_addr_list;
	//  };
	char *hostname;

	if(argc == 1)
	{
		hostname = malloc (81);
		gets(hostname);
	}
	else
	{
		hostname = argv[1];
	}

	if((ip = gethostbyname(hostname)) == NULL)
	{
		herror("gethostbyname");
		exit(1);
	}

	printf("获取主机信息成功!\n");
	printf("主机名：%s\n",ip->h_name);
	if(ip->h_aliases[0]!= NULL)
		printf("别名：");
	for(i=0;*(ip->h_aliases+i);i++)
	{
		printf("%s\n",*(ip->h_addr_list));
	}
	if(ip->h_addrtype == AF_INET)
		printf("主机ip类型为ipv4\n");
	else
		printf("主机ip类型为ipv6\n");

	printf("IP list:\n");
	for(i = 0;ip->h_addr_list[i]; i++)
	{
		printf("%s\n",inet_ntoa(*((struct in_addr *)ip->h_addr_list[i])));
	}

	return 0;
}

