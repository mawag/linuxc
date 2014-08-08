/*=============================================================================
#   >>   文件名: c.c
#   >> 	   描述: 客户端
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://www.cnblogs.com/wangbo2008/
#   >>   Github: github.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-08-01 09:59:36
#   >> 修改时间: 2014-08-02 17:29:29
#  Copyright (c) wangbo  All rights reserved.
=============================================================================*/
#include "in.h"


//处理从服务端接受到的消息队列
void c_rec(int *sock)
{
}

//注册
//登陆
//

int main(int argc,char **argv)

{
	struct sockaddr_in sock;
	int sock_fd;//套接字
	char buf[MAX_BIT];
	int flag;
	int i;

	//套接字地址
	//清空数据
	memset(&sock,0,sizeof(struct sockaddr_in));
	//设置ip类型为ipv4
	sock.sin_family = AF_INET;
	//服务器ip
	sock.sin_addr.s_addr = inet_addr (HOSTIP);
	//端口
	sock.sin_port = htons (PORT);
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

	//建立连接
	if(connect(sock_fd,(struct sockaddr *)&sock,sizeof(struct sockaddr_in)) == -1)
	{
		perror("connect");
		exit(1);
	}
	flag = recv(sock_fd,buf,sizeof(buf),0);
	if(flag == -1)
	{
		perror("recv");
		exit(1);
	}
	if((buf != NULL)&&(buf != "\0"))
		printf("%s\n",buf);

	printf("$ connect ok!sockfd = %d.\n",sock_fd);

	printf("服务器连接成功，请输入要发到服务器的信息。\n");
	while(1)
	{
		gets(buf);
		if((strcmp(buf,"exit")) == 0)
			break;
		if(send(sock_fd,buf,sizeof(buf),0) == -1)
		{
			perror("消息发送失败。");
		}
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
			printf("接收到服务器消息:");
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

