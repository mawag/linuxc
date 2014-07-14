#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc,char **argv)
{
	int i;//循环变量
	int fd;//文件描述符
	int len;//文件长度
	char *filename;//文件名
	off_t off;

	if( argc == 1)
	{
		printf("cat <file name>\n");
		exit(1);
	}

	filename = argv[1];
	printf("%s\n",filename);
	if (fd = open(filename,O_RDWR) == -1)
	{
		perror("open");
		exit(1);
	}

	off = lseek(fd,5,SEEK_CUR);
	//len = lseek(fd,0,SEEK_CUR);
	printf("%d\n",off);

	if(close(fd) == -1)
	{
		perror("close");
		exit(1);
	}


	return 0;
}
