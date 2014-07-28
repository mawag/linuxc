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
	int i;
	pid_t pid;

	for(i = 0;i < 2; i++)
	{
		printf("%c",'-');
		pid = fork();
		printf("%c",'~');
		if(pid == -1)
		{
			perror("fork");
			exit(-1);
		}
	}


	return 0;
}


