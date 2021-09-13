#include "header.h"
extern int errno;
void print_shell_prompt(char home[])
{
    int errnum;
    //obtain details of the user and the system
    struct utsname unameData;
    uname(&unameData);
    char user_name[INPUT_SIZE];
    getlogin_r(user_name, INPUT_SIZE);

    //get the current directory (here it is home i.e '~')
    char dir[INPUT_SIZE];
    if (getcwd(dir, INPUT_SIZE) == NULL)
    {
        errnum = errno;
        printf("%s", strerror(errnum));
    }
    printf("<%s@%s:%s> ", user_name, unameData.nodename, dir);
}