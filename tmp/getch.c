#include<stdio.h>
#include<termios.h>
#include<unistd.h>
#include<assert.h>
#include<string.h>

int getch(void)
{
	int c=0;
	struct termios org_opts, new_opts;
	int res=0;
	res=tcgetattr(STDIN_FILENO, &org_opts);
	assert(res==0);
	memcpy(&new_opts, &org_opts, sizeof(new_opts));
	new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
	c=getchar();
	res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
	assert(res==0);
	return c;
}

int main(void)
{
	int i,j;
	char t;
	char buf[50];

	for(i = 0,j = 0;j<50;i++)
	{
		t=getch();
		if(t == '\n')
		{
			buf[j] = '\0';
			break;
		}
		else if (t == 127)
		{
			printf("\b \b");
			j--;
			if(j<0)
				j=0;
		}
		else if(t>32&&t<127)
		{
			printf("*");
			buf[j++] = t;
		}
		else
			continue;

	}

	printf("\n%s\n",buf);
	return 0;
}
