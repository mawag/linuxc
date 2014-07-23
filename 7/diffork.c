#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int globVar = 1;

int main(int argc, char *argv[])
{
	pid_t pid;
	int var = 1, i;
	printf("fork is diffirent with vfork \n");
	//pid = fork();
	pid = vfork();
	switch(pid) {
		case 0:
			i = 3;
			while (i-- > 0) {
				printf("Child process is running var = %d globVar = %d\n", var, globVar);
				globVar++;
				var++;
				sleep(1);
			}
			printf("Child`s globVar = %d, var = %d\n",globVar,var);
			//break; //wrong
			exit(0); //right
			//_exit(0);
		case -1:
			perror("Process creation failed\n");
			exit(0);
		default:
			i = 5;
			while (i-- > 0) 
			{
				printf("Parent process is running var = %d globVar = %d\n", var , globVar);
				globVar++;
				var++;
				sleep(1);
			}
			printf("Parent globVar = %d, var = %d\n", globVar, var);
			exit(0);
			break;
	}
	printf("var = %d\n",var);
	return 0;
	//exit(0);
}
