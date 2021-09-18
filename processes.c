#include "header.h"
void run_process(char **func_arg, char *command, char argv[][INPUT_SIZE], int argc, int flag)
{
    int pid = fork();

    if (pid < 0)
    {
        perror("command");
    }
    else if (pid == 0)
    {
        func_arg = (char **)malloc((argc + 1) * sizeof(char *));
        for (int j = 0; j < argc; j++)
        {
            func_arg[j] = argv[j];
            printf("arg %d : %s\n", j, func_arg[j]);
        }
        func_arg[argc] = NULL;
        if (execvp(func_arg[0], func_arg) == -1)
        {
            perror("command");
            exit(0);
        }
    }

    else
    {
        if (!flag)
        {
            wait(NULL);
        }
    }
}