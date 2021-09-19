#include "header.h"
void pwd(char *home)
{
    char dir[INPUT_SIZE];
    getcwd(dir, INPUT_SIZE);
    char relative[INPUT_SIZE];
    get_relative_dir(dir, home, relative);
    printf("%s\n", relative);
}
void echo_parser(char *input)
{
    // printf("%s", input);
    char *save;
    char buffer[INPUT_SIZE];
    strcpy(buffer, input);
    char *command = strtok_r(buffer, " \n\t", &save);
    // printf("%s\n", command);
    command = strtok_r(NULL, " \n\t", &save);
    while (command != NULL)
    {
        printf("%s ", command);
        command = strtok_r(NULL, " \n\t", &save);
    }
    printf("\n");
}
void cd_parser(char *input, char *home)
{
    char *save;
    char pwd[INPUT_SIZE];
    getcwd(pwd, INPUT_SIZE);
    char buffer[INPUT_SIZE];
    strcpy(buffer, input);
    char *command = strtok_r(buffer, " \n\t", &save);
    command = strtok_r(NULL, " \n\t", &save);
    char toprint[1] = "";
    int args = 0;
    char abs_path[INPUT_SIZE];
    while (command != NULL)
    {
        strcat(toprint, command);
        command = strtok_r(NULL, " \n\t", &save);
        args++;
    }
    if (args == 0)
    {
        chdir(home);
    }
    else if (args > 1)
    {
        printf("cd: too many arguments\n");
    }
    else
    {
        get_absolute_dir(toprint, home, abs_path);
        if (chdir(abs_path) == -1)
        {
            printf("cd: %s: %s\n", strerror(errno), toprint);
        }
    }
}
void get_relative_dir(char *dir, char *home, char *relative)
{
    if (strcmp(dir, home) == 0)
    {
        strcpy(relative, "~");
        return;
    }

    if (strlen(dir) < strlen(home))
        strcpy(relative, dir);
    else
    {
        for (ll i = 0; i < strlen(home); i++)
        {
            if (dir[i] != home[i])
            {
                strcpy(relative, "");
                strcat(relative, dir);
                return;
            }
        }
        strcpy(relative, "~");
        strcat(relative, dir + strlen(home));
    }
}
void get_absolute_dir(char *dir, char *home, char *absolute)
{
    if (strlen(dir) >= 1 && dir[0] == '~')
    {
        strcpy(absolute, home);
        if (strlen(dir) > 1)
            strcat(absolute, dir + 1);
    }
    else
        strcpy(absolute, dir);
}