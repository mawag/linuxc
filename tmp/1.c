#include <stdio.h>
int main(void)
{
	int i;
	for(i=0;i<90;i++)
		printf("%d",i%10 +1);

	system("ls -l");
	return 0;
}
