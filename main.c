// contains the driver code
#include "header.h"

//main
int main()
{
    char input_str[INPUT_SIZE] = " "; // stores the input commands
    char command[INPUT_SIZE] = " ";   // stores the command
    while (strcmp(command, "exit") != 0)
    {
        print_shell_prompt();
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
    }
    return 0;
}