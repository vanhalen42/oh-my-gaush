#include "header.h"
void foreground(char *input_str, char *command)
{
    int pid = fork();
    if (pid < 0)
    {
        perror(command);
    }
    else if (pid == 0)
    {
        int argc = 0;
        char **argv = (char **)malloc(INPUT_SIZE * sizeof(char *));
        char *token = strtok(input_str, " \t\n");
        while (token != NULL)
        {
            argv[argc] = token;
            argc++;
            token = strtok(NULL, " \t\n");
        }
        // for (int i = 0; i < argc; i++)
        //     printf("%s ", argv[i]);
        if (execvp(argv[0], argv) < 0)
        {
            perror(argv[0]);
        }
    }
}