// contains the driver code
#include "header.h"
//main
char welcome_mssg[] = "              _                            _   \n__      _____| | ___ ___  _ __ ___   ___  | |_ ___  \n\\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\\n \\ V  V /  __/ | (_| (_) | | | | | |  __/ | || (_) |\n  \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|  \\__\\___/ \n\n       _                                                       _  \n  ___ | |__        _ __ ___  _   _        __ _  __ _ _   _ ___| |__  \n / _ \\| '_ \\ _____| '_ ` _ \\| | | |_____ / _` |/ _` | | | / __| '_ \\ \n| (_) | | | |_____| | | | | | |_| |_____| (_| | (_| | |_| \\__ \\ | | |\n \\___/|_| |_|     |_| |_| |_|\\__, |      \\__, |\\__,_|\\__,_|___/_| |_|\n                             |___/       |___/                 \n      ";
int main()
{
    char prev_command[INPUT_SIZE] = " ";
    char input_str[INPUT_SIZE] = "";           // stores the input commands
    char command[INPUT_SIZE] = "";             // stores the command
    char home_dir[INPUT_SIZE] = "";            // stores the home directory
    char input[INPUT_SIZE][INPUT_SIZE] = {""}; // stores the input commands which are seperated by semicolon
    char argv[INPUT_SIZE][INPUT_SIZE] = {""};  // stores the arguments
    char **func_arg;
    getcwd(home_dir, INPUT_SIZE); // gets the current working directory
    printf("%s\n", welcome_mssg);
    char flags[INPUT_SIZE] = "";
    int flag = 0;
    int exit_code = 0;
    while (1)
    {
        print_shell_prompt(home_dir, prev_command);
        fgets(input_str, INPUT_SIZE, stdin);
        int num_commands = parse_semicolon(input_str, input);
        for (int i = 0; i < num_commands; i++)
        {
            // int num_flags=flags_parser(input_str, flags);
            int argc = parse_command(input[i], command, argv, flags);
            strcpy(prev_command, command);
            if (argc == 2 && strcmp(argv[1], "&") == 0)
                flag = 1;
            // printf("command: %s.\n", command);

            // printf("flags: %s\n", flags);
            // printf("command: %s\n", command);
            // printf("argc: %d\n", argc);
            for (int j = 0; j < argc; j++)
            {
                printf("argv[%d]: %s\n", j, argv[j]);
            }
            printf("flags : %s\n", flags);
            if (!argc)
            {
                continue;
            }
            // printf("%s\n%d\n", command,lol);
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
                echo_parser(input_str);
            }
            else if (strcmp(command, "cd") == 0) // implementation of cd
            {
                cd_parser(input_str, home_dir);
            }
            else if (strcmp(command, "figlet") == 0) // implementation of exit
            {
                system(input_str);
            }
            // implementation of ls
            else if (strcmp(command, "ls") == 0)
            {
                ls(flags, argv, argc, home_dir);
            }
            else if (strcmp(command, "exit") == 0 || strcmp(command, "quit") == 0) // implementation of exit
            {
                return 0;
            }
            else
            {
                run_process(func_arg,command,argv,argc,flag);
            }
        }
    }
    return 0;
}