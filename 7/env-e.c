#include <stdio.h>
#include <malloc.h>


int  main(int argc,char **argv,char **envp)
{
	int i;

	printf("Argument:\n");
	for(i=0;i<argc;i++)
	{
		printf("argv[%d] is %s\n",i,argv[i]);
	}

	printf("Environnment:\n");

	for(i=0;envp[i]!=NULL;i++)
	{
		printf("%s\n",envp[i]);
	}

	return 0;
}
