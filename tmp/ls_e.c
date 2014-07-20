/*=============================================================================
#   >>   文件名: ls.c
#   >> 	   描述: ls的简单实现
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://hi.baidu.com/wangbo2008
#   >>   Github: hithub.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-17 20:22:55
#   >> 修改时间: 2014-07-17 22:02:51
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
#include <linux/limits.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>


//#define DEBUG


//参数
typedef struct parameter
{
	int i;//i参数
	int l;//l参数
	int a;//a参数
}par;


//参数<全局变量>
par opt;



//显示错误信息
void seerror(const char* error_string,int line)
{
	#ifdef DEBUG
	printf("line:%d\n",line);
	#endif
	perror(error_string);
}

//展示单个文件信息
int showdirinfo(const struct dirent* ptr)
{
	printf("%s\t",ptr->d_name);
	return 0;
}

//读取文件夹内文件并输出
int showdir(const char* path)
{
	int i,j;			//循环变量
	int t,m;			//临时变量
	char *tmp;			//临时变量
	char **name;			//文件名指针数组
	int maxd_filename;		//最长文件名
	int d_dirfile;			//文件夹内文件数
	DIR *dir;			//文件夹
	struct dirent *ptr;		//文件信息
	/*
	 *	struct dirent
	 *	{
	 *		long d_ino; 			索引节点号
	 *		off_t d_off; 			在目录文件中的偏移
	 *		unsigned short d_reclen;	文件名长
	 *		unsigned char d_type; 		文件类型
	 *		char d_name [NAME_MAX+1]; 	文件名，最长256字符
	 *	}*
	 */

	//初始化 
	maxd_filename = 0;
	d_dirfile = 0;

	if ((dir = opendir(path)) == NULL) 
	{
		seerror("opendir",__LINE__);
		return 1;
	}

	//获取最长文件名长度和文件数目
	while ((ptr = readdir(dir))!=NULL) 
	{
		d_dirfile++;
		if(maxd_filename < ptr->d_reclen)
			maxd_filename = ptr->d_reclen;	
	}
	#ifdef DEBUG
	printf("file number:%d,max filename:%d\n",d_dirfile,maxd_filename);
	#endif

	closedir(dir);

	//把文件名存入数组
	if ((dir = opendir(path)) == NULL) 
	{
		seerror("opendir",__LINE__);
		return 1;
	}
	if((name = calloc ( d_dirfile,maxd_filename + 1)) == NULL)
	{
		seerror("malloc",__LINE__);
		exit(1);
	}

	for(i = 0;i < d_dirfile; i++)
	{
		ptr = readdir(dir);
		name[i] = ptr->d_name;
	}

	closedir(dir);
	#ifdef DEBUG
	for(i = 0;i < d_dirfile;i++)
	{
		printf("%d,name:%s\n",i+1,name[i]);
	}
	#endif

/*	//对文件名排序
	for(i = 0;i < d_dirfile - 1; i++)
	{
		for( j = i+1; j < d_dirfile; j++)
		{
			if(strcmp(name[i],name[j]) > 0)
			{

				memmove(tmp,name[i],maxd_filename);
				memmove(name[i],name[j],maxd_filename);
				memmove(name[j],tmp,maxd_filename);
			}
		}
	}
	*/


	if((tmp = malloc ( maxd_filename + 1)) == NULL)
	{
		seerror("malloc",__LINE__);
		exit(1);
	}

	for (i = 0; i < d_dirfile - 1; i++) 
	{
		for (j = 0; j < d_dirfile - 1- i; j++) 
		{
			if (strcmp(name[j],name[j+1])> 0) 
			{
				memmove(tmp,name[j],8);
				memmove(name[j],name[1+j],8);
				memmove(name[j+1],tmp,8);


			/*	
				strcpy (tmp, name[j]);
				tmp[strlen (name[j])] = '\0';

				strcpy (name[j], name[j + 1]);
				name[j][strlen (name[j + 1])] = '\0';

				strcpy (name[j + 1], tmp);
				name[j + 1][strlen (tmp)] = '\0';*/
			}
		}
	}


	for(i = 0;i < d_dirfile;i++)
	{
		printf("%d,name:%s\n",i+1,name[i]);
	}

	return 0;
}


int main(int argc,char ** argv)
{
	int i;		//循环
	int flag = 0;	//循环标志位
	char* path;	//目录

	//参数初始化
	opt.a = 0;
	opt.l = 0;
	opt.i = 0;

	opterr = 0;	//getopt不输出错误参数



	//循环处理传入参数
	while(flag != -1)
	{
		//调用getopt处理参数
		switch(getopt( argc, argv, "ali"))
		{
			case 'a':
				opt.a = 1;
				break;
			case 'l':
				opt.l = 1;
				break;
			case 'i':
				opt.i = 1;
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


	if((argc - optind) < 2)
	{
		path = ".";
		return (showdir(path));
	}
	else
	{
		for(i = optind; i < argc; i++)
		{
			path = argv[i];
			printf("%s:\n",path);
			showdir(path);
			printf("\n");
		}
	}


	return 0;
}
