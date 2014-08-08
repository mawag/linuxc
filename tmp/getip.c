/*=============================================================================
#   >>   文件名: getip.c
#   >> 	   描述: 花生壳更新ip 
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://www.cnblogs.com/wangbo2008/
#   >>   Github: github.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-08-01 09:41:35
#   >> 修改时间: 2014-08-06 21:14:30
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


int s_getip(void)
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


	if((ip = gethostbyname("ddns.oray.com")) == NULL)
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

int s_changewebip(char *hostip)
{
	struct sockaddr_in sock;
	int sock_fd;
	char buf[150];
	char szbuffer[]={"GET /ph/update HTTP/1.0\r\nHost: ddns.oray.com\r\nAuthorization: bWF3YWc6d2JkeDMzMDA=\r\nUser-Agent: Oray\r\n\r\n"};

	int i,flag;

	//套接字地址
	//清空数据
	memset(&sock,0,sizeof(struct sockaddr_in));
	//设置ip类型为ipv4
	sock.sin_family = AF_INET;
	//服务器ip
	sock.sin_addr.s_addr = inet_addr (hostip);
	//端口
	sock.sin_port = htons (80);
	//填充0
	memset(sock.sin_zero,0,sizeof(sock.sin_zero));

	//创建套接字
	//IPV4,TCP连接
	sock_fd = socket(AF_INET,SOCK_STREAM,0);
	if(sock_fd == -1)
	{
		perror("socket");
		exit(1);
	}
	
	if(connect(sock_fd,(struct sockaddr *)&sock,sizeof(struct sockaddr_in)) == -1)
	{
		perror("connect");
		exit(1);
	}
	printf("服务器连接成功，请输入要发到服务器的信息。\n");
	while(1)
	{
		flag = recv(sock_fd,buf,sizeof(buf),0);
		if(flag == -1)
		{
			perror("recv");
			exit(1);
		}
		else if(flag == 0)
			break;
		if((buf != NULL)&&(buf != "\0"))
		{
			printf("%s\n",buf);
		}

	}
	printf("断开连接！\n");
	if(close(sock_fd) == -1)
	{
		perror("close");
		exit(1);
	}

	return 0;
}


int main(int argc,char **argv)
{
	
}
