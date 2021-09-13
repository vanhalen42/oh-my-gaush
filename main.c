// contains the driver code
#include "header.h"
extern int errno;
//main
int main()
{
    char input_str[INPUT_SIZE] = " "; // stores the input commands
    char command[INPUT_SIZE] = " ";   // stores the command
    char home_dir[INPUT_SIZE] = " ";  // stores the home directory
    getcwd(home_dir, INPUT_SIZE);     // gets the current working directory
    while (strcmp(command, "exit") != 0)
    {
        print_shell_prompt(home_dir);
        fgets(input_str, INPUT_SIZE, stdin);
        int lol = parse_command(input_str, command);
        if (!lol)
        {
            perror("Interrupt, Aborting:");
            continue;
        }
        // printf("%s\n%d\n", command,lol);
        if (strcmp(command, "clear") == 0) // implementation of clear
        {
            printf("\033[H\033[J");
        }
        else if (strcmp(command, "pwd") == 0) // implementation of pwd
        {
            pwd();
        }
        else if (strcmp(command, "echo") == 0) // implementation of echo
        {
            echo_parser(input_str);
        }
        else if (strcmp(command, "cd") == 0)// implementation of cd
        {
            cd_parser(input_str,home_dir);
        }
    }
    return 0;
}