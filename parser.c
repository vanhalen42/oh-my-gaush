#include "header.h"
int parse_command(char *input, char *command, char argv[][INPUT_SIZE], char *flags)
{
    char *save, *c, buffer[INPUT_SIZE];
    strcpy(buffer, input);
    c = strtok_r(buffer, " \t\n", &save);
    if (c == NULL)
        return -1;
    else
    {
        strcpy(command, c);
    }
    strcpy(flags, "");
    int len = 0;
    while (c != NULL)
    {
        if (c[0] == '-' && strlen(c) > 1)
        {
            if (!(strlen(c) > 2 && c[1] == '-'))
                strcat(flags, c + 1);
            strcpy(argv[len], c);
            len++;
        }
        else
        {
            strcpy(argv[len], c);
            len++;
        }
        c = strtok_r(NULL, " \t\n", &save);
    }
    return len;
}
int parse_semicolon(char a[], char b[][INPUT_SIZE])
{
    char *save, *c, buffer[INPUT_SIZE];
    strcpy(buffer, a);
    c = strtok_r(buffer, ";\n", &save);
    int len = 0;
    while (c != NULL)
    {
        strcpy(b[len], c);
        c = strtok_r(NULL, ";\n", &save);
        len++;
    }
    return len;
}
int flags_parser(char *input, char *flags)
{
    char *save, *c, buffer[INPUT_SIZE];
    strcpy(buffer, input);
    c = strtok_r(buffer, " \n", &save);
    strcpy(flags, "");
    while (c != NULL)
    {
        if (c[0] == '-' && strlen(c) > 1)
        {
            strcat(flags, c + 1);
        }
        c = strtok_r(NULL, " \n", &save);
    }
    return strlen(flags);
}
int flag_in(char flag, char *flags)
{
    for (int i = 0; i < strlen(flags); i++)
    {
        if (flag == flags[i])
            return 1;
    }
    return 0;
}