/*=============================================================================
#   >>   文件名: chown.c
#   >> 	   描述: chown函数的简单实现
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://hi.baidu.com/wangbo2008
#   >>   Github: hithub.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-16 15:29:41
#   >> 修改时间: 2014-07-16 18:15:57
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
#include <pwd.h>
#include <grp.h>

//#define DEBUG

//错误处理
void seerror(const char *error_string,int line)
{
	#ifdef DEBUG
	printf("line:%d\n",line);
	#endif
	perror(error_string);
}


int main(int argc,char ** argv)
{
	struct passwd* us;			//用户信息
	/*
	 * 	struct passwd
	 *	{
	 *		char *pw_name;  	用户名
	 *		char *pw_passwd;	密码
	 *		__uid_t pw_uid; 	用户ID
	 *		__gid_t pw_gid; 	组ID
	 *		char *pw_gecos; 	真实名
	 *		char *pw_dir;   	主目录
	 *		char *pw_shell; 	使用的shell
	 *	};
	 */
	struct group* gp;			//用户组信息
	/*
	 *	struct group 
	 *	{
	 *		char *gr_name;		用户组名称
	 *		char *gr_passwd;
	 *		gid_t gr_gid;		用户组id
	 *		char **gr_mem;
	 *	};
	 *
	 */
	char username[20];			//用户名
	char groupname[20];			//用户组名称
	int i,j;				//循环变量
	char* filename;

	//参数合法性检测
	if(argc != 3)
	{
		printf("\"chown <username:groupname> <filename>\"\n");
		exit(1);
	}
	else if(argc == 3)
	{
		for(i = 0;argv[1][i] != ':';i++)
			username[i] = argv[1][i];
		username[i++] = '\0';
		for(j = 0;argv[1][i] != '\0';i++,j++)
			groupname[j] = argv[1][i];
		groupname[j] = '\0';
		filename = argv[2];
	}

	#ifdef DEBUG
	printf("user:%s\ngroup:%s\nfile:%s\n",username,groupname,filename);
	#endif

	//获取用户信息
	//struct passwd *getpwnam(const char *name)
	if(username[0] != '\0')
	{
		if((us = getpwnam(username)) == NULL)
		{
			seerror("getpwnam",__LINE__);
			exit(1);
		}
		#ifdef DEBUG
		printf("user:%s\n",us->pw_name);
		printf("userid:%d\n",us->pw_uid);
		#endif
	}
	else
	{
		us = malloc(sizeof(struct passwd));
		us->pw_uid = -1;
	}


	//获取用户组信息
	if(groupname[0] != '\0')
	{
		if((gp = getgrnam(groupname)) == NULL)
		{
			seerror("getgrnam",__LINE__);
			exit(1);
		}
		#ifdef DEBUG
		printf("group:%s\n",gp->gr_name);
		printf("groupid:%d\n",gp->gr_gid);
		#endif

	}
	else
	{
		gp = malloc(sizeof(struct group));
		gp->gr_gid = -1;
	}

	if(chown(filename,us->pw_uid,gp->gr_gid) == -1)
	{
		seerror("chown",__LINE__);
		exit(1);
	}

	return 0;
}
