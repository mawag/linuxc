/*=============================================================================
#   >>   文件名: userid.c
#   >> 	   描述: 获取user信息
#   >>     作者: wangbo
#   >>    Email: mawag@live.cn
#   >>	   主页: http://www.cnblogs.com/wangbo2008/
#   >>   Github: github.com/mawag
#   >> 程序版本: 0.0.1
#   >> 创建时间: 2014-07-25 15:13:42
#   >> 修改时间: 2014-07-25 15:13:42
#  Copyright (c) wangbo  All rights reserved.
=============================================================================*/
#include <grp.h>
#include <pwd.h>
#include <unistd.h>
#include <stdio.h>

int main (void)
{
	uid_t uid;
	struct passwd *pw;
	struct group *grp;
	char **members;

	uid = getuid ();
	pw = getpwuid (uid);

	if (!pw)
	{
		printf ("Couldn't find out about user %d.\n", (int)uid);
		return 1;
	}

	printf ("I am %s.\n", pw->pw_gecos);
	printf ("User login name is %s.\n", pw->pw_name);
	printf ("User uid is %d.\n", (int) (pw->pw_uid));
	printf ("User home is directory is %s.\n", pw->pw_dir);
	printf ("User default shell is %s.\n", pw->pw_shell);
	grp = getgrgid (pw->pw_gid);
	if (!grp)
	{
		printf ("Couldn't find out about group %d.\n",(int)pw->pw_gid);
		return 1;
	}

	printf ("User default group is %s (%d).\n",grp->gr_name, (int) (pw->pw_gid));

	printf ("The members of this group are:\n");
        members = grp->gr_mem;
        while (*members)
        {
        	printf ("\t%s\n", *(members));
        	members++;
        }

        return 0;
}
