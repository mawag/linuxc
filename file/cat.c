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
	int fd;//文件描述符
	char *filename;//文件名
	char s;

	if( argc == 1)
	{
		printf("cat <file name>\n");
		exit(1);
	}

	filename = argv[1];
	if (fd = open(filename,O_RDWR) == -1)
	{
		perror("open");
		exit(1);
	}

	//lseek(fd,5,SEEK_SET);
	//len = lseek(fd,0,SEEK_CUR);
	printf("%s\n",filename);

	if (read(fd,&s,1) == -1 )
	{
		perror("read");
		exit(1);
	}

	printf("%c",s);

	if(close(fd) == -1)
	{
		perror("close");
		exit(1);
	}


	return 0;
}
