/*=============================================================================
#   >>   文件名: stat.c
#   >> 	   描述: 获取文件属性
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://hi.baidu.com/wangbo2008
#   >>   Github: hithub.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-16 11:44:52
#   >> 修改时间: 2014-07-16 15:27:55
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
#include <time.h>


//#define DEBUG

//显示错误
void seerror(const char *error_string,int line)
{
	#ifdef DEBUG
	printf("line:%d\n",line);
	#endif
	perror(error_string);
}

//显示文件属性
void print(struct stat* buf)
{
	printf("device is: %d\n", buf->st_dev);
	printf("inode is: %d\n", buf->st_ino);
	printf("mode is: %o\n", buf->st_mode);
	printf("number of hard links  is: %d\n", buf->st_nlink);
	printf("user ID of owner is: %d\n", buf->st_uid);
	printf("group ID of owner is: %d\n", buf->st_gid);
	printf("device type (if inode device) is: %d\n", buf->st_rdev);
	printf("total size, in bytes is: %d\n", buf->st_size);
	printf(" blocksize for filesystem I/O is: %d\n", buf->st_blksize);
	printf("number of blocks allocated is: %d\n", buf->st_blocks);
	printf("time of last access is: %s", ctime(&buf->st_atime));
	printf("time of last modification is: %s", ctime(&buf->st_mtime));
	printf("time of last change is: %s", ctime(&buf->st_ctime));
	printf("\n");
}


int main(int argc,char ** argv)
{
	int fd;			//文件描述符
	int i;			//循环变量
	char* filename;		//文件名
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

	//参数有效性检查
	if(argc == 1)
	{
		printf("input file name:");
		filename = malloc (50);
		gets(filename);
	}
	else if(argc == 2)
	{
		filename = argv[1];
	}

	//使用stat
	if(stat(filename,buf) == -1)
	{
		seerror("stat",__LINE__);
	}
	else 
	{
		printf("use stat:\n");
		print(buf);
	}

	//使用fstat
	if((fd = open(filename,O_RDONLY)) == -1)
	{
		seerror("open",__LINE__);
	}
	else
	{
		if(fstat(fd,buf) == -1)
		{
			seerror("stat",__LINE__);
		}
		else 
		{
			printf("use fstat:\n");
			print(buf);
		}
	}

	//使用lstat
	if(lstat(filename,buf) == -1)
	       seerror("stat",__LINE__);
	else 
	{
		printf("use lstat:\n");
	 	print(buf);
	}
	return 0;
}

