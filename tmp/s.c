/*=============================================================================
#   >>   文件名: s.c
#   >> 	   描述: 服务端
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://www.cnblogs.com/wangbo2008/
#   >>   Github: github.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-08-01 10:27:13
#   >> 修改时间: 2014-08-02 17:29:37
#  Copyright (c) wangbo  All rights reserved.
=============================================================================*/
#include "in.h"

//创建私有数据
pthread_key_t key;

void fun(int *client_fd)
{
	char buf[MAX_BIT];//接收到的数据
	int flag;
	int tmp_client_fd = *client_fd;

	int opt = 1;
	socklen_t len=sizeof(int);
	//设置套接字属性，连接异常断开自动关闭
	if((setsockopt(tmp_client_fd,SOL_SOCKET,SO_KEEPALIVE,(char*)&opt,len))==-1)
	{
		printf("SO_KEEPALIVE is ok\n");
	}

	//设置客户端连接成功服务器返回消息提醒
	if(send(tmp_client_fd,"您好，您已经连接成功!/n",50,0)==-1)
	{
		perror("发送通知信息失败!/n");
		exit(0);
	}

	//处理请求
	while(1)
	{
		memset(buf,0,sizeof(buf));
		//接收消息
		flag = recv(tmp_client_fd,buf,sizeof(buf),0);
		if(flag == -1)
		{
			perror("recv");
			exit(1);
		}
		else if(flag == 0)		/*客户端断开连接*/
			break;
		if((buf != NULL)&&(buf != "\0"))
		{
			printf("接收到消息:");
			printf("%s\n",buf);
		}

		/*消息处理*/

		if(send(tmp_client_fd,"消息发送成功\n",50,0)==-1)
		{
			perror("发送通知信息失败!\n");
			exit(0);
		}
	}
	printf("客户端断开连接！\n");
	close(tmp_client_fd);

	return ;
}

int main(int argc,char **argv)

{
	struct sockaddr_in client_addr;
	int sock_fd;//套接字
	int client_len;
	int client_fd;
	pthread_t thid;

	//套接字地址

	//清空数据
	memset(&client_addr,0,sizeof(struct sockaddr_in));
	//设置ip类型为ipv4
	client_addr.sin_family = AF_INET;
	//接受所有ip
	client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	//端口
	client_addr.sin_port = htons (PORT);
	//填充0
	memset(client_addr.sin_zero,0,sizeof(client_addr.sin_zero));

	//创建套接字
	//IPV4,TCP连接
	sock_fd = socket(AF_INET,SOCK_STREAM,0);
	if(sock_fd == -1)
	{
		perror("socket");
		exit(1);
	}

	//绑定
	if(bind(sock_fd,(struct sockaddr *)&client_addr,sizeof(struct sockaddr_in)) == -1)
	{
		perror("bind");
		exit(1);
	}

	//监听
	if(listen(sock_fd,LISTEN_NUM) == -1)
	{
		perror("listen");
		exit(1);
	}

	printf("服务端启动成功，正在监听系统端口:%d\n",PORT);

	//修改套接字属性
	//int setsockopt(int sock, int level, int optname, const void *optval, socklen_t optlen);

	//getsockopt(sock_fd,IPPROTO_TCP,SO_KEEPALIVE,);
	//getsockopt(sock_fd,IPPROTO_TCP,SO_KEEPALIVE,);

	//创建私有数据
	//pthread_key_create(&key,NULL);
	//接受连接，阻塞方式
	while(1)
	{
		client_len = sizeof(struct sockaddr_in);
		client_fd = accept(sock_fd,(struct sockaddr *)&client_addr,&client_len);
		if(client_fd < 0)
		{
			perror("accept");
			exit(1);
		}


		printf("receive a new client,ip:%s\n",inet_ntoa(client_addr.sin_addr));
		if(pthread_create(&thid,NULL,(void *)fun,&client_fd) != 0)
		{
			perror("pthread_create");
			exit(1);
		}

	}
	//pthread_key_delete(key);
	close(sock_fd);
	pthread_key_delete(key);

	return 0;

}

