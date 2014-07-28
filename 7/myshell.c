/*=============================================================================
#   >>   文件名: myshell.c
#   >> 	   描述: shell简单实现
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://www.cnblogs.com/wangbo2008/
#   >>   Github: github.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-24 09:05:48
#   >> 修改时间: 2014-07-28 09:47:38
#  Copyright (c) wangbo  All rights reserved.
=============================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

//#define DEBUG


//显示错误信息
void seerror(const char *error_string, int line)
{
#ifdef DEBUG
	printf("line:%d\n", line);
#endif
	perror(error_string);
}

void print_prompt(void);						/* 打印提示符 */
void get_input(char *buf);						/* 得到输入的命令 */
void explain_input(char *buf, int *argcount, char arglist[100][256]);	/* 对输入命令进行解析 */
void do_cmd(int argcount, char arglist[100][256]);			/* 执行命令 */
int find_command(char *command);					/* 查找命令中的可执行程序 */

//打印提示符
void print_prompt(void)
{
	char *path;
	char hostname[32];
	char *loginname;
	char *ps;

	if (!(loginname = getenv("LOGNAME"))) {
		seerror("getenv", __LINE__);
		exit(1);
	}

	if (gethostname(hostname, sizeof(hostname))) {
		seerror("gethostname", __LINE__);
		exit(1);
	}

	if (!(path = getenv("PWD"))) {
		seerror("getenv", __LINE__);
		exit(1);
	}



	printf("%s@%s:%s #", loginname, hostname, path);
}

//得到输入的命令
void get_input(char *buf)
{
	int i = 0;
	char ch;

	ch = getchar();
	while (ch != '\n') {
		buf[i++] = ch;
		ch = getchar();
	}
	buf[i] = '\0';
}

//对输入命令进行解析
void explain_input(char *buf, int *argcount, char a[100][256])
{
	int i, j;
	int d;

	j = 0;
	d = 0;
	for (i = 0; *(buf + i) != '\0'; i++) {
		if (*(buf + i) != ' ') {
			a[d][j] = *(buf + i);
			j++;
			a[d][j] = '\0';
		} else {
			d++;
			j = 0;
		}
	}
	*argcount = d + 1;

	#ifdef DEBUG
	for (i = 0; i < d + 1; i++)
		printf("%s\n", a[i]);
	#endif

}

//执行命令
void do_cmd(int argcount, char arglist[100][256])
{
	int flag = 0;
	int how = 0;
	int background = 0;
	int status;
	int i;
	int fd;
	char *arg[argcount + 1];
	char *argnext[argcount + 1];
	char *file;
	pid_t pid;

	//取出命令
	for (i = 0; i < argcount; i++)
	{
		arg[i] = (char *) arglist[i];
	}
	arg[argcount] = NULL;

	//查看后台
	for (i = 0; i < argcount; i++)
	{
		if (strncmp(arg[i], "&", 1) == 0)
		{
			if (i == argcount - 1)
			{
				background = 1;
				arg[argcount - 1] = NULL;
				break;
			}else
			{
				printf("wrong command\n");
				return;
			}
		}
	}

	//查看管道
	for (i = 0; arg[i] != NULL; i++)
	{
		if (strcmp(arg[i], ">") == 0)
		{
			flag++;
			how = 1;
			if (arg[i + 1] == NULL)
				flag++;
		}
		if (strcmp(arg[i], "<") == 0)
		{
			flag++;
			how = 2;
			if (i == 0)
				flag++;
		}
		if (strcmp(arg[i], "|") == 0)
		{
			flag++;
			how = 3;
			if (arg[i + 1] == NULL)
				flag++;
			if (i == 0)
				flag++;
		}
	}
	if (flag > 1)
	{
		printf("命令不支持！\n");
		return;
	}
	if (how == 1)
	{
		for (i = 0; arg[i] != NULL; i++)
		{
			if (strcmp(arg[i], ">") == 0)
			{
				file = arg[i + 1];
				arg[i] = NULL;
			}
		}
	}
	if (how == 2)
	{
		for (i = 0; arg[i] != NULL; i++)
		{
			if (strcmp(arg[i], "<") == 0)
			{
				file = arg[i + 1];
				arg[i] = NULL;
			}
		}
	}
	if (how == 3)
	{
		for (i = 0; arg[i] != NULL; i++)
		{
			if (strcmp(arg[i], "|") == 0)
			{
				arg[i] = NULL;
				int j;
				for (j = i + 1; arg[j] != NULL; j++)
				{
					argnext[j - i - 1] = arg[j];
				}
				argnext[j - i - 1] = arg[j];
				break;
			}
		}
	}
	if ((pid = fork()) < 0)
	{
		seerror("fork",__LINE__);
		return;
	}
	switch (how)
	{
		case 0:
			if (pid == 0)
			{
				if (!(find_command(arg[0])))
				{
					printf("%s: command not found\n", arg[0]);
					exit(0);
				}
				execvp(arg[0], arg);
				exit(0);
			}
			break;
		case 1:
			if (pid == 0)
			{
				if (!(find_command(arg[0])))
				{
					printf("%s:command not found\n", arg[0]);
					exit(0);
				}
				fd = open(file, O_RDWR|O_CREAT|O_TRUNC, 0644);
				dup2(fd, 1);
				execvp(arg[0], arg);
				exit(0);
			}
			break;
		case 2:
			if (pid == 0)
			{
				if (!(find_command(arg[0])))
				{
					printf("%s:command not found\n", arg[0]);
					exit(0);
				}
				fd = open(file, O_RDONLY);
				dup2(fd, 0);
				execvp(arg[0], arg);
				exit(0);
			}
			break;
		case 3:
			if (pid == 0)
			{
				int pid2;
				int status2;
				int fd2;

				if ((pid2 = fork()) < 0)
				{
					printf("fork2 error\n");
					return;
				} else if (pid2 == 0)
				{
					if (!(find_command(arg[0])))
					{
						printf("%s:command not found\n",
						       arg[0]);
						exit(0);
					}
					fd2 =open("/tmp/youdonotknowfile",O_WRONLY | O_CREAT | O_TRUNC,0644);
					dup2(fd2, 1);
					execvp(arg[0], arg);
					exit(0);
				}
				if (waitpid(pid2, &status2, 0) == -2)
					printf("wait for child process error\n");

				if (!(find_command(argnext[0])))
				{
					printf("%s:command not found\n",
					       argnext[0]);
					exit(0);
				}
				fd2 = open("/tmp/youdonotknowfile", O_RDONLY);
				dup2(fd2, 0);
				execvp(argnext[0], argnext);

				if (remove("/tmp/youdonotknowfile"))
					printf("remove error \n");
				exit(0);
			}
			break;
		default:
			break;
	}

	if (background == 1)
	{
		printf("process id %d\n", pid);
		return;
	}
	if (waitpid(pid, &status, 0) == -1)
		printf("wait for child process error\n");
}

//查找命令中的可执行文件
int find_command(char *command)
{
	DIR *dp;
	struct dirent *dirp;
	char *t_path;
	char path[20][50];
	int i, j, k;

	t_path = getenv("PATH");
	for (i = 0, j = 0, k = 0; *(t_path + i) != '\0'; i++)
	{
		if (*(t_path + i) != ':')
		{
			path[j][k] = *(t_path + i);
			path[j][k + 1] = '\0';
			k++;
		}else
		{
			j++;
			k = 0;
		}
	}
	path[j + 1][0] = '\0';

	//本目录查找
	if (strncmp(command, "./", 2) == 0)
		command = command + 2;
	i = 0;
	while (path[i] != NULL)
	{
		if ((dp = opendir(path[i])) == NULL)
			printf("can not open /bin \n");
		while ((dirp = readdir(dp)) != NULL)
		{
			if (strcmp(dirp->d_name, command) == 0)
			{
				closedir(dp);
				return 1;
			}
		}
		closedir(dp);
		i++;
	}
	return 0;
}

int main(int argc, char **argv)
{
	char *buf;		//记录输入的命令
	int argcount;		//记录参数个数
	char arglist[100][256];	//解析出来的参数
	int i;			//循环变量

	printf("欢迎使用精简版shell\n");
	buf = malloc(256);
	if (buf == NULL)
	{
		seerror("malloc", __LINE__);
		exit(1);
	}
	do
	{
		print_prompt();
		memset(buf, 0, 256);
		get_input(buf);
		#ifdef DEBUG
		printf("buf = %s\n", buf);
		#endif
		if ((strcmp("exit", buf) == 0)|| (strcmp("logout", buf) == 0))
		{
			free(buf);
			exit(0);
		}
		argcount = 0;
		for (i = 0; i < 100; i++)
		{
			arglist[i][0] = '\0';
		}
		explain_input(buf, &argcount, arglist);
		do_cmd(argcount, arglist);
	} while (1);

	exit(1);
}
