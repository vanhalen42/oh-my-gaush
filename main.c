// contains the driver code
#include "header.h"
//main
char welcome_mssg[] = "              _                            _   \n__      _____| | ___ ___  _ __ ___   ___  | |_ ___  \n\\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\\n \\ V  V /  __/ | (_| (_) | | | | | |  __/ | || (_) |\n  \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|  \\__\\___/ \n\n       _                                                       _  \n  ___ | |__        _ __ ___  _   _        __ _  __ _ _   _ ___| |__  \n / _ \\| '_ \\ _____| '_ ` _ \\| | | |_____ / _` |/ _` | | | / __| '_ \\ \n| (_) | | | |_____| | | | | | |_| |_____| (_| | (_| | |_| \\__ \\ | | |\n \\___/|_| |_|     |_| |_| |_|\\__, |      \\__, |\\__,_|\\__,_|___/_| |_|\n                             |___/       |___/                 \n      ";
int shell_pid = 0;
int running_pid = 0;
int zflag = 0;
int cflag = 0;
int original_input = 4, original_output = 5;

int main()
{
    shell_pid = getpid();
    dup2(STDIN_FILENO, original_input);
    dup2(STDOUT_FILENO, original_output);
    running_pid = shell_pid;
    signal(SIGCHLD, process);
    signal(SIGINT, ctrl_C);
    signal(SIGTSTP, ctrl_Z);
    // signal(SIGINT, ctrl_Z);
    char prev_command[INPUT_SIZE] = " ";
    char input_str[INPUT_SIZE] = "";           // stores the input commands
    char command[INPUT_SIZE] = "";             // stores the command
    char home_dir[INPUT_SIZE] = "";            // stores the home directory
    char input[INPUT_SIZE][INPUT_SIZE] = {""}; // stores the input commands which are seperated by semicolon
    char argv[INPUT_SIZE][INPUT_SIZE] = {""};  // stores the arguments
    char pipes[INPUT_SIZE][INPUT_SIZE] = {""};
    char **func_arg;
    getcwd(home_dir, INPUT_SIZE); // gets the current working directory
    printf("\033[H\033[J");
    printf("%s\n", welcome_mssg);
    printf("%d\n", shell_pid);
    char flags[INPUT_SIZE] = "";
    int flag = 0;
    int exit_code = 0;
    int append_flag = 0;
    while (1)
    {
        print_shell_prompt(home_dir, prev_command);
        if (fgets(input_str, INPUT_SIZE, stdin) == NULL)
            exit(0);
        int num_commands = parse_semicolon(input_str, input);
        for (int i = 0; i < num_commands; i++)
        {
            // int num_flags=flags_parser(input_str, flags);
            int total_pipes = pipe_parser(input[i], pipes);
            int pipe_fd[2], pipe_in, pipe_out;
            for (int k = 0; k < total_pipes; k++)
            {
                char actual_command[INPUT_SIZE] = "";
                strcpy(actual_command, pipes[k]);
                if (strtok(actual_command, " \t") == NULL)
                    continue;
                if (pipe(pipe_fd) < 0)
                {
                    printf("Erorr: %s\n", strerror(errno));
                    exit(1);
                }
                else
                {
                    pipe_out = pipe_fd[1];
                }
                if (k < total_pipes - 1)
                {
                    dup2(pipe_out, STDOUT_FILENO);
                }
                append_flag = 0;
                strcpy(flags, "");
                strcpy(actual_command, "");
                char io_input[INPUT_SIZE] = "";
                char io_output[INPUT_SIZE] = "";
                int io_args = parse_io(pipes[k], actual_command, io_input, io_output, &append_flag);
                int argc = parse_command(actual_command, command, argv, flags);
                strcpy(prev_command, command);
                if (strcmp(argv[argc - 1], "&") == 0)
                {
                    flag = 1;
                    argc--;
                    strcpy(argv[argc], "");
                }
                else
                {
                    flag = 0;
                }
                // printf("command: %s.\n", command);
                // printf("flags: %s\n", flags);
                // printf("command: %s\n", command);
                // printf("argc: %d\n", argc);
                // for (int j = 0; j < argc; j++)
                // {
                //     printf("argv[%d]: %s\n", j, argv[j]);
                // }
                // printf("flags : %s\n", flags);
                if (!argc)
                {
                    continue;
                }
                // printf("%s\n%d\n", command,lol);
                execute_command(actual_command, home_dir, command, argv, flags, flag, argc, io_input, io_output, &append_flag);
                close(pipe_out);
                dup2(original_input, STDIN_FILENO);
                dup2(original_output, STDOUT_FILENO);
                if (k != 0)
                    close(pipe_in);
                if (k < total_pipes - 1)
                {
                    pipe_in = pipe_fd[0];
                    dup2(pipe_in, STDIN_FILENO);
                }
            }
        }
    }
    return 0;
}