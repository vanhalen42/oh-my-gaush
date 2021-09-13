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
    char *command = strtok_r(input, " \n", &save);
    // printf("%s\n", command);
    command = strtok_r(NULL, " \n", &save);
    while (command != NULL)
    {
        printf("%s ", command);
        command = strtok_r(NULL, " \n", &save);
    }
    printf("\n");
}