/*=============================================================================
#   >>   文件名: ls.c
#   >> 	   描述: ls的简单实现
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://hi.baidu.com/wangbo2008
#   >>   Github: hithub.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-17 20:22:55
#   >> 修改时间: 2014-07-18 15:00:17
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

//处理文件夹内文件信息
int showdirfile(char name[256][PATH_MAX + 1],int d_dirfile)
{
	int i,j;//循环变量

	if((opt.l == 0)&&(opt.i == 0))
	{
		j == 0;
		for(i=0;i<d_dirfile;i++)
		{
			j++;
			printf("%s\t",name[i]);
			if(j%5 == 0)
				printf("\n");
		}
		printf("\n");

	}
	else
	{
		for(i=0;i<d_dirfile;i++)
			showfile(name[i]);
	}

	return 0;
}


//显示文件属性
void print(struct stat* buf)
{
	char *time;
	struct passwd *psd; 		//用户
	struct group *grp; 		//用户组
	
	if(opt.i == 1)
		printf("%ld\t", buf->st_ino);
	if(opt.l == 1)
	{
		//文件类型
		if (S_ISLNK (buf->st_mode))
		{
			printf ("l");
		}
		else if (S_ISREG (buf->st_mode))
		{
			printf ("-");
		}
		else if (S_ISDIR (buf->st_mode))
		{
			printf ("d");
		}
		else if (S_ISCHR (buf->st_mode))
		{
			printf ("c");
		}
		else if (S_ISBLK (buf->st_mode))
		{
			printf ("b");
		}
		else if (S_ISFIFO (buf->st_mode))
		{
			printf ("f");
		}
		else if (S_ISSOCK (buf->st_mode))
		{
			printf ("s");
		}
		//文件所有者权限
		if (buf->st_mode & S_IRUSR)
		{
			printf ("r");
		}
		else 
			printf ("-");

		if (buf->st_mode & S_IWUSR)
		{
			printf ("w");
		}
		else 
			printf ("-");

		if (buf->st_mode & S_IXUSR)
		{
			printf ("x");
		}
		else 
			printf ("-");

		//用户组权限 
		if (buf->st_mode & S_IRGRP)
		{
			printf ("r");
		}
		else 
			printf ("-");

		if (buf->st_mode & S_IWGRP)
		{
			printf ("w");
		}
		else 
			printf ("-");

		if (buf->st_mode & S_IXGRP)
		{
			printf ("x");
		}
		else 
			printf ("-");

		//其他用户权限
		if (buf->st_mode & S_IROTH)
		{
			printf ("r");
		}
		else 
			printf ("-");

		if (buf->st_mode & S_IWOTH)
		{
			printf ("w");
		}
		else 
			printf ("-");

		if (buf->st_mode & S_IXOTH)
		{
			printf ("x");
		}
		else 
			printf ("-");
		//链接数
		printf("\t%-5ld", buf->st_nlink);
		//用户名
		psd = getpwuid (buf->st_uid);
		printf ("%-10s", psd->pw_name);
		//所属组
		grp = getgrgid (buf->st_gid);
		printf ("%-10s", grp->gr_name);
		//文件大小
		printf("%-6ld", buf->st_size);
		//时间
		time = strdup(ctime(&buf->st_mtime));
		time[strlen(time) -1] = '\0';
		printf("%-s",time);
	}
}



//展示文件信息
int showfile(const char* filename)
{
	int fd;			//文件描述符
	int i;			//循环变量
	struct stat* buf;	//文件属性

	buf = malloc (sizeof(struct stat));

	//文件状态结构体
	//	struct stat  
	//	{  
	//		dev_t       st_dev;     /* 文件所在设备的ID*/  
	//		ino_t       st_ino;     /* inode节点号*/  
	//		mode_t      st_mode;    /* 文件的类型和存储权限*/  
	//		nlink_t     st_nlink;   /* 链向此文件的连接数(硬连接)*/  
	//		uid_t       st_uid;     /* user ID*/  
	//		gid_t       st_gid;     /* group ID*/  
	//		dev_t       st_rdev;    /* 设备号，针对设备文件*/  
	//		off_t       st_size;    /* 文件大小，字节为单位*/  
	//		blksize_t   st_blksize; /* 文件系统I/O缓冲区大小，系统块的大小*/  
	//		blkcnt_t    st_blocks;  /* 文件所占块数*/
	//		time_t      st_atime;   /* 最后访问时间*/  
	//		time_t      st_mtime;   /* 最后修改时间，一般只能调用write和utime函数才更改*/  
	//		time_t      st_ctime;   /* 最后更改时间，在文件所有者，所属组和文件权限被更改时更新*/  
	//	};

	//使用lstat
	if(lstat(filename,buf) == -1)
	       seerror("stat",__LINE__);
	else 
	{
	 	print(buf);
		if(opt.l == 1)
		printf("\t%s\n",filename);
	}
	return 0;
}

//读取文件夹内文件
int showdir(const char* path)
{
	int i,j;			//循环变量
	char tmp[PATH_MAX + 1];		//临时变量
	char name[256][PATH_MAX + 1];	//文件名数组
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
	 *	}
	 */

	//初始化 
	maxd_filename = 0;
	d_dirfile = 0;

	//切换工作目录
	if(chdir(path) == -1)
	{
		seerror("cd",__LINE__);
		exit(1);
	}

	//获取最长文件名长度和文件数目
	if ((dir = opendir(path)) == NULL) 
	{
		seerror("opendir",__LINE__);
		return 1;
	}
	while ((ptr = readdir(dir))!=NULL) 
	{
		if((opt.a == 0)&& (ptr->d_name[0] == '.'))
			continue;
		d_dirfile++;
		if(maxd_filename < ptr->d_reclen)
			maxd_filename = ptr->d_reclen;	
	}
	maxd_filename+=1;
	#ifdef DEBUG
	printf("file number:%d,max filename:%d\n",d_dirfile,maxd_filename-1);
	#endif

	closedir(dir);

	//把文件名存入数组
	if ((dir = opendir(path)) == NULL) 
	{
		seerror("opendir",__LINE__);
		return 1;
	}
	for(i = 0;i < d_dirfile; i++)
	{
		ptr = readdir(dir);
		if((opt.a == 0)&& (ptr->d_name[0] == '.'))
		{
			i--;
			continue;
		}
		strcpy(name[i],ptr->d_name);
		name[i][strlen(ptr->d_name)] = '\0';
		#ifdef DEBUG
		printf("%3d,name:%-10s,leny:%d,len:%d,sizeof:%lu\n",i,name[i],(int)strlen(ptr->d_name),(int)strlen(name[i]),sizeof(name[i]));
		#endif
	}

	closedir(dir);
	#ifdef DEBUG
	for(i = 0;i < d_dirfile;i++)
	{
		printf("%d,name:%s\n",i+1,name[i]);
	}
	#endif

	for (i = 0; i < d_dirfile - 1; i++) 
	{
		for (j = 0; j < d_dirfile - 1- i; j++) 
		{
			if (strcmp(name[j],name[j+1])> 0) 
			{
				strcpy (tmp, name[j]);
				tmp[strlen (name[j])] = '\0';

				strcpy (name[j], name[j + 1]);
				name[j][strlen (name[j + 1])] = '\0';

				strcpy (name[j + 1], tmp);
				name[j + 1][strlen (tmp)] = '\0';
			}
		}
	}


	#ifdef DEBUG
	for(i = 0;i < d_dirfile;i++)
	{
		printf("%d,name:%s\n",i+1,name[i]);
	}
	#endif

	showdirfile(name,d_dirfile);

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
