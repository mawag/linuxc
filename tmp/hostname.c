#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	char hostname[32];

	if( gethostname(hostname,sizeof(hostname)) )
	{
		perror("gethostname");
		return 1;
	}
	printf("localhost name:%s\n",hostname);

	return 0;
}
