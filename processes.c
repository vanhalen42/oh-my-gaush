#include "header.h"
struct proc
{
    char proc_name[INPUT_SIZE];
    int pid;
};
int total_bg_proc = 0;
struct proc bg_processes[INPUT_SIZE];
void run_process(char *command, char argv[][INPUT_SIZE], int argc, int flag)
{
    int pid = fork();
    char **func_arg;
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
        if (total_bg_proc >= INPUT_SIZE)
        {
            printf("LIMIT REACHED:cant execute more processes\n");
            exit(0);
        }
        setpgid(0, 0);
        if (execvp(func_arg[0], func_arg) == -1)
        {
            printf(RED "oh-my-gaush: command not found: %s\n", command);
            exit(0);
        }
    }

    else
    {
        if (!flag)
        {
            wait(NULL);
        }
        else
        {
            printf("%d\n", pid);
            bg_processes[total_bg_proc].pid = pid;
            strcpy(bg_processes[total_bg_proc].proc_name, command);
            total_bg_proc++;
        }
    }
}
void process(int signum)
{
    int status;
    pid_t ret_pid = waitpid(-1, &status, WNOHANG | WUNTRACED);
    char process_name[INPUT_SIZE] = "unnamed process";
    int i;
    if (ret_pid > 0)
    {
        for (i = 0; i < total_bg_proc; i++)
        {
            if (bg_processes[i].pid == ret_pid)
            {
                strcpy(process_name, bg_processes[i].proc_name);
                break;
            }
        }
        printf("index: %d\n", i);
        if (WIFEXITED(status))
            fprintf(stderr, "\n%s with pid %d exited normally\n", process_name, ret_pid);
        else
            fprintf(stderr, "\n%s with pid %d exited abnormally\n", process_name, ret_pid);
        i++;
        for (; i < total_bg_proc; i++)
        {
            bg_processes[i - 1] = bg_processes[i];
        }
        total_bg_proc--;
    }
    return;
}
int execute_command(char *input, char *home_dir, char *command, char argv[][INPUT_SIZE], char *flags, int flag, int argc)
{
    int exit_code = 0;
    if (strcmp(command, "clear") == 0) // implementation of clear
    {
        printf("\033[H\033[J");
    }
    else if (strcmp(command, "pwd") == 0) // implementation of pwd
    {
        pwd(home_dir);
    }
    else if (strcmp(command, "echo") == 0) // implementation of echo
    {
        echo_parser(input);
    }
    else if (strcmp(command, "cd") == 0) // implementation of cd
    {
        cd_parser(input, home_dir);
    }
    else if (strcmp(command, "figlet") == 0) // implementation of exit
    {
        system(input);
    }
    // implementation of ls
    else if (strcmp(command, "ls") == 0)
    {
        ls(flags, argv, argc, home_dir);
    }
    else if (strcmp(command, "pinfo") == 0)
    {
        pinfo(command, argv, argc);
    }
    else if (strcmp(command, "repeat") == 0)
    {
        if (argc > 2)
        {
            int n = atoi(argv[1]);
            if (!n)
            {
                printf("Error: non-integer arguments\n");
                return exit_code;
            }
            int new_argc = argc - 2;
            char new_argv[INPUT_SIZE][INPUT_SIZE];
            char new_input[INPUT_SIZE] = "";
            for (int k = 2; k < argc; k++)
            {
                strcpy(new_argv[k - 2], argv[k]);
                strcat(new_input, new_argv[k - 2]);
                strcat(new_input, " ");
            }
            for (int k = 0; k < n; k++)
            {
                printf("inputtstr:%s\n", new_input);
                execute_command(new_input, home_dir, new_argv[0], new_argv, flags, flag, new_argc);
            }
        }
        else
        {
            printf("Error: no command to repeat\n");
        }
    }
    else if (strcmp(command, "exit") == 0 || strcmp(command, "quit") == 0) // implementation of exit
    {
        exit(exit_code);
    }
    else
    {
        run_process(command, argv, argc, flag);
    }
    return exit_code;
}