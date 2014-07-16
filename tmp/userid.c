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
