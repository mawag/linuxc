#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

int main(int argc,char **argv)
{
	char *path;
	char buf[100];
	int e;

	if(argc > 1)
		path = argv[1];
	else
	{
		path = malloc(100);
		gets(path);
	}
	if((e=readlink(path,buf,sizeof(buf))) == -1)
	{
		perror("readlink");
		exit(1);
	}
	buf[e]='\0';
	printf("%d--%s\n",e,buf);

	return 0;
}

