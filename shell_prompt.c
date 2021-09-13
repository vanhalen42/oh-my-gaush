#include"header.h"

void print_shell_prompt()
{
    //obtain details of the user and the system
    struct utsname unameData;
    uname(&unameData);
    char user_name[INPUT_SIZE];
    getlogin_r(user_name, INPUT_SIZE);

    //get the current directory (here it is home i.e '~')
    char dir[] = "~";
    printf("<%s@%s:%s> ", user_name, unameData.nodename, dir);
}