#include "header.h"
void pwd()
{
    char dir[INPUT_SIZE];
    getcwd(dir, INPUT_SIZE);
    printf("%s\n", dir);
}
void echo_parser(char *input)
{
    // printf("%s", input);
    char *save;
    char *command = strtok_r(input, " \n\t", &save);
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
    char *command = strtok_r(input, " \n\t", &save);
    command = strtok_r(NULL, " \n\t", &save);
    char toprint[1] = "";
    int args = 0;
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
    else if (chdir(toprint) != 0)
    {
        // printf("%s\n", toprint);
        printf("%s: No such file or directory\n", toprint);
    }
}