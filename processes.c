#include "header.h"

proc bg_processes[INPUT_SIZE];
int total_bg_proc = 0;
int job_number = 1;
int comparator(const void *a, const void *b)
{
    int diff = strcmp(((struct proc *)a)->proc_name, ((struct proc *)b)->proc_name);
    if (diff == 0)
        return -1;
    return diff;
}
void print_all_proc(char *flags)
{
    qsort(bg_processes, total_bg_proc, sizeof(struct proc), comparator);
    for (int k = 0; k < total_bg_proc; k++)
    {
        char status[INPUT_SIZE] = "";
        get_pinfo(bg_processes[k].pid, 2, status);
        if ((status[0] == 'R' || status[0] == 'S') && (flag_in('s', flags) && !(flag_in('r', flags))))
            continue;
        else if (status[0] == 'T' && (flag_in('r', flags) && !(flag_in('s', flags))))
            continue;
        printf("[%d] ", bg_processes[k].jpb_no);
        if (status[0] == 'R' || status[0] == 'S')
        {
            printf("Running ");
        }
        else if (status[0] == 'T')
        {
            printf("Stopped ");
        }
        else
            printf("%c ", status[0]);
        printf("%s [%d]\n", bg_processes[k].proc_name, bg_processes[k].pid);
    }
}
void run_process(char *command, char argv[][INPUT_SIZE], int argc, int flag, char *flags)
{
    signal(SIGINT, ctrl_C);
    signal(SIGTSTP, ctrl_Z);
    char input[INPUT_SIZE] = "";
    if (!argc)
        return;
    strcat(input, argv[0]);
    for (int i = 1; i < argc; i++)
    {
        strcat(input, " ");
        strcat(input, argv[i]);
    }

    int pid = fork();
    char **func_arg;
    if (pid < 0)
    {
        perror("command");
    }
    else if (pid == 0)
    {
        func_arg = (char **)malloc((argc + 2) * sizeof(char *));
        for (int j = 0; j < argc; j++)
        {
            func_arg[j] = argv[j];
            // printf("arg %d : %s\n", j, func_arg[j]);
        }
        // if (strlen(flags) != 0)
        // {
        //     char added_flags[INPUT_SIZE] = "-";
        //     strcat(added_flags, flags);
        //     func_arg[argc++] = added_flags;
        // }
        func_arg[argc] = NULL;
        // for (int j = 0; j < argc; j++)
        // {
        //     printf("arg %d : %s\n", j, func_arg[j]);
        // }
        if (total_bg_proc >= INPUT_SIZE)
        {
            printf("LIMIT REACHED:can't execute more processes\n");
            exit(0);
        }
        if (flag)
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
            int status;
            running_pid = pid;
            // wait(NULL)
            while (waitpid(pid, &status, WNOHANG | WUNTRACED) != pid)
                ;
            // tcsetpgrp(0, getpgrp());
        }
        else
        {
            printf("%d\n", pid);
            bg_processes[total_bg_proc].pid = pid;
            strcpy(bg_processes[total_bg_proc].proc_name, input);
            bg_processes[total_bg_proc].jpb_no = job_number;
            job_number++;
            total_bg_proc++;
        }
    }
    // print_all_proc();
}
void process(int signum)
{
    // printf("YELLOWWWW\n");
    int status;
    pid_t ret_pid = waitpid(-1, &status, WNOHANG);
    // printf("ret_pid : %d\n", ret_pid);
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
        running_pid = shell_pid;
    }
    // print_all_proc();
    return;
}

int execute_command(char *input, char *home_dir, char *command, char argv[][INPUT_SIZE], char *flags, int flag, int argc, char io_in[], char io_out[], int *append_flag)
{
    if (strcmp(io_in, "") != 0)
    {
        int f_open = open(io_in, O_RDONLY);
        if (f_open < 0)
        {
            fprintf(stdout, "Error: %s", strerror(errno));
        }
        dup2(f_open, STDIN_FILENO);
        close(f_open);
    }
    if (strcmp(io_out, "") != 0)
    {
        int f_open;
        if (*append_flag == 1)
            f_open = open(io_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            f_open = open(io_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (f_open < 0)
        {
            fprintf(stdout, "Error: %s", strerror(errno));
        }
        dup2(f_open, STDOUT_FILENO);
        close(f_open);
    }
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
        pinfo(command, argv, argc, home_dir);
    }
    else if (strcmp(command, "repeat") == 0)
    {
        if (argc > 2)
        {
            int n = atoi(argv[1]);
            if (!n)
            {
                printf("Error: non-integer arguments\n");
                goto exit;
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
                // printf("inputtstr:%s\n", new_input);
                execute_command(new_input, home_dir, new_argv[0], new_argv, flags, flag, new_argc, io_in, io_out, append_flag);
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
    else if (strcmp(command, "jobs") == 0) // implementation of exit
    {
        print_all_proc(flags);
    }
    else if (strcmp(command, "kill") == 0)
    {
        int pid = atoi(argv[1]);
        int ret = kill(pid, SIGKILL);
        if (ret < 0)
        {
            printf("Error: %s", strerror(errno));
        }
    }
    else if (strcmp(command, "sig") == 0)
    {
        if (argc != 3)
        {
            printf("3 arguments must be supplied for \"sig\": sig [job_no] [signal]\n");
            goto exit;
        }
        int job_no = atoi(argv[1]);
        if (job_no <= 0 || job_no > job_number)
        {
            printf("Incorrect Job number. Aborting!");
            goto exit;
        }
        int signal = atoi(argv[2]);
        if (!signal)
        {
            goto exit;
        }
        int pid = 0;
        for (int i = 0; i < total_bg_proc; i++)
        {
            if (bg_processes[i].jpb_no == job_no)
            {
                pid = bg_processes[i].pid;
                break;
            }
        }
        if (!pid)
        {
            printf(RED "job with job number [%d] not found \n" INPUT_COLOR, job_no);
            goto exit;
        }
        int ret = kill(pid, signal);
        if (ret < 0)
        {
            printf("Error: %s", strerror(errno));
        }
    }
    else if (strcmp(command, "bg") == 0)
    {
        if (argc != 2)
        {
            printf("2 arguments must be supplied for \"bg\": bg [job_no]\n");
            goto exit;
        }
        int job_no = atoi(argv[1]);
        if (job_no <= 0 || job_no > job_number)
        {
            printf("Incorrect Job number. Aborting!");
            goto exit;
        }
        int signal = SIGCONT;
        int pid = 0;
        for (int i = 0; i < total_bg_proc; i++)
        {
            if (bg_processes[i].jpb_no == job_no)
            {
                pid = bg_processes[i].pid;
                break;
            }
        }
        if (!pid)
        {
            printf(RED "job with job number [%d] not found \n" INPUT_COLOR, job_no);
            goto exit;
        }
        int ret = kill(pid, signal);
        if (ret < 0)
        {
            printf("Error: %s", strerror(errno));
        }
    }
    else if (strcmp(command, "fg") == 0)
    {
        int status;
        if (argc != 2)
        {
            printf("2 arguments must be supplied for \"fg\": fg [job_no]\n");
            goto exit;
        }
        int job_no = atoi(argv[1]);
        if (job_no <= 0 || job_no > job_number)
        {
            printf("Incorrect Job number. Aborting!");
            goto exit;
        }
        int signal_to_send = SIGCONT;
        int pid = 0;
        for (int i = 0; i < total_bg_proc; i++)
        {
            if (bg_processes[i].jpb_no == job_no)
            {
                pid = bg_processes[i].pid;
                break;
            }
        }
        if (!pid)
        {
            printf(RED "job with job number [%d] not found \n" INPUT_COLOR, job_no);
            goto exit;
        }
        printf("pid %d \n", pid);
        running_pid = pid;
        signal(SIGTTOU, SIG_IGN);
        signal(SIGTTIN, SIG_IGN);
        tcsetpgrp(0, getpgid(pid));
        int ret = kill(pid, signal_to_send);
        if (ret < 0)
        {
            printf("Error: %s", strerror(errno));
            running_pid = shell_pid;
            tcsetpgrp(0, shell_pid);
            signal(SIGTTOU, SIG_DFL);
            signal(SIGTTIN, SIG_DFL);
        }
        else
        {
            while (waitpid(pid, &status, WNOHANG | WUNTRACED) != pid)
                ;
            tcsetpgrp(0, shell_pid);
            signal(SIGTTOU, SIG_DFL);
            signal(SIGTTIN, SIG_DFL);
            int i;
            char process_name[INPUT_SIZE];
            for (i = 0; i < total_bg_proc; i++)
            {
                if (bg_processes[i].pid == pid)
                {
                    strcpy(process_name, bg_processes[i].proc_name);
                    break;
                }
            }
            printf("index: %d\n", i);
            if (WIFEXITED(status))
            {
                fprintf(stderr, "\n%s with pid %d exited normally\n", process_name, pid);

                i++;
                for (; i < total_bg_proc; i++)
                {
                    bg_processes[i - 1] = bg_processes[i];
                }
                total_bg_proc--;
                running_pid = shell_pid;
            }
            else if (WIFSIGNALED(status))
            {
                fprintf(stderr, "\n%s with pid %d exited abnormally\n", process_name, pid);

                i++;
                for (; i < total_bg_proc; i++)
                {
                    bg_processes[i - 1] = bg_processes[i];
                }
                total_bg_proc--;
                running_pid = shell_pid;
            }
        }
    }
    else
    {
        run_process(command, argv, argc, flag, flags);
    }
exit:
    dup2(original_input, STDIN_FILENO);
    dup2(original_output, STDOUT_FILENO);

    return exit_code;
}