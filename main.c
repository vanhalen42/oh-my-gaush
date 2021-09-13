// contains the driver code
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include<time.h>
#define ll long long

//main
int main()
{
    char name[] = "gaurav";
    char dir[] = "~";
    char input_str[100]=" ";
    while (strcmp(input_str, "exit\n") != 0)
    {
        printf("<%s@oh-my-gaush:%s> ", name, dir);
        fgets(input_str, 100, stdin);
        if (strcmp(input_str, "clear\n") == 0) // implementation of clear
        {
            printf("\033[H\033[J");
        }
    }
    return 0;
}