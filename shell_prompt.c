 #include "header.h"

void print_shell_prompt(char home[], char *prev_command)
{
    //obtain details of the user and the system
    struct utsname unameData;
    uname(&unameData);
    char user_name[INPUT_SIZE];
    getlogin_r(user_name, INPUT_SIZE);

    //get the current directory (here it is home i.e '~')
    char dir[INPUT_SIZE];
    if (getcwd(dir, INPUT_SIZE) == NULL)
    {
        printf("%s", strerror(errno));
    }
    char relative_dir[INPUT_SIZE];
    get_relative_dir(dir, home, relative_dir);

    //Enhanced promt : requires the font MesloLGS NF
    char file_char[] = "";
    if (strcmp(relative_dir, "~") == 0)
        strcpy(file_char, "");
    else if (strcmp(relative_dir, "/") == 0)
        strcpy(file_char, "");
    else
        strcpy(file_char, "");
    if (strcmp(prev_command, "clear") == 0)
        printf(INPUT_WITH_BG "  " CYAN " %s@" GREEN_BOLD "%s " INPUT_WITH_BG " " PURPLE "%s %s" GREY "" INPUT_COLOR " ", user_name, unameData.nodename, file_char, relative_dir);
    else
        printf(INPUT_WITH_BG "\n  " CYAN " %s@" GREEN_BOLD "%s " INPUT_WITH_BG " " PURPLE "%s %s" GREY "" INPUT_COLOR " ", user_name, unameData.nodename, file_char, relative_dir);

    //Normal prompt
    // printf(CYAN "<%s@" YELLOW_BOLD "%s:" PURPLE_BOLD "%s>" INPUT_COLOR " ", user_name, unameData.nodename, relative_dir);
}