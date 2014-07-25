#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <termio.h>

int getch(void)
{
     struct termios tm, tm_old;
     int fd = 0, ch;

     if (tcgetattr(fd, &tm) < 0) {
          return -1;
     }

     tm_old = tm;
     cfmakeraw(&tm);
     if (tcsetattr(fd, TCSANOW, &tm) < 0) {
          return -1;
     }

     ch = fgetc(stdin);
     if (tcsetattr(fd, TCSANOW, &tm_old) < 0) {
          return -1;
     }

     return ch;
}

/*
 * 密码输入函数，参数 passwd 为密码缓冲区，buff_len 为缓冲区长度
 */
char *passwd_input(char *passwd, int buff_len)
{
     char str;
     int i = 0;
     int enter_num = 13;
     int backspace_num;

     backspace_num = 8;

     if (passwd == NULL || buff_len <= 0)
     {
          return passwd;
     }
     while (1)
     {
          // 如果没有按下退格键
          if ((str = getch()) != 8)
	  {
               if (i < buff_len - 1)
	       {
                    passwd[i++] = str;
                    printf("*");
               }
          }
	  else
	  {
               if (i != 0)
	       {
                    i--;
                    printf("\b \b");
               }
          }
          // 如果按下了回车键
          if (str == 13)
	  {
		passwd[--i] = '\0';


               if (i != buff_len - 1)
	       {
			printf("\b \b");
               }
               break;
          } else if (str == -1)
	  {
               fprintf(stderr, "Error to set termio noecho.n");
          }
     }
     return passwd;
}


// 测试示例（请自行添加头文件）

int main(int argc,char **argv)
{
      char pass[7];

      printf("亲，试试输入密码（长度限制 6）：");
      passwd_input(pass, 7);
      printf("\npasswd:%s\n", pass);

     return 0;
}


