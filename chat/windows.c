#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//初始化
int s_init(void)
{
	static int passwd_init_flag=0;
	if(passwd_init_flag==0)
	{
		initscr(); //curses库函数，开启curses模式
		cbreak(); //关闭行缓存
		nl(); //把回车转换为换行符
		noecho(); //关闭输入显示
		intrflush(stdscr,FALSE);//关闭中断清空队列
		keypad(stdscr,TRUE); //开启kaypad模式，将可以使用一些特殊的键盘字元，例如方向按键
		start_color();//彩色模式
		init_pair(1, COLOR_BLACK, COLOR_WHITE);
		bkgd(COLOR_PAIR(1));
		refresh();//刷新屏幕
		init_pair(2, COLOR_YELLOW, COLOR_BLUE);
		refresh(); //刷新屏幕
	}
	else
	{
		/*二次调用*/
		wrefresh(stdscr); // doupdate();
	}
	passwd_init_flag++;
	return 0;
}

//获取密码
int s_getpasswd(char *passwd,char *user)
{
	int c;
	int n = 0;
	char npasswd[21];
	WINDOW *win;
	
//	move(LINES/2, COLS/2);
	//创建输入窗体
	win = newwin(7, 25, 2, 2);
	wbkgd(win, COLOR_PAIR(2));
	
	box(win, 0, 0);
	mvwprintw(win, 2, 2, "User:");
	mvwprintw(win, 4, 2, "Pass:");
	
	wbkgdset(win, COLOR_PAIR(1));
	mvwprintw(win, 2, 8, " ");
	mvwprintw(win, 4, 8, " ");
	wrefresh(win);
	echo();	
	wmv(win,2,8);
	wgetnstr(win, user,15);
	noecho();
	n=0;
	do
	{
		c = getch();
		
		if(c == KEY_BACKSPACE && n != 0) //检测按键是否为bs
		{
			echochar('\b');
			echochar('\x20');
			echochar('\b');
			n--;
		}
		else if( n== 0 && c ==KEY_BACKSPACE); //屏蔽掉因为密码输入长度为0，按下bs后出现的问题
		else if ( c != '\n')
		{
			echochar('*'); //密码字段显示为*
			passwd[n++] = c;
		}
	}while(c != '\n' && n < 21); //跳出条件，如果密码长度超出或者按下回车
	passwd[n] = '\0';
	
	overwrite(win, stdscr); 
	delwin(win);

	touchwin(stdscr);
	refresh(); //用于把屏幕清空或者刷新
	//endwin(); //退出curses模式
	/*密码加密字段,可用于整个密码字符串的加密*/
	return 0;
}


int main(void)
{
	char passwd[21];
	char user[15];
	s_init();

	s_getpasswd(passwd,user);
	mvprintw(11, 0, "user: %s, passwd: %s\n", user, passwd);
	endwin();
	return 0;
}
