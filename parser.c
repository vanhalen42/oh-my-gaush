#include "header.h"
int parse_command(char a[], char b[])
{
    char *save, *c, buffer[INPUT_SIZE];
    strcpy(buffer, a);
    c = strtok_r(buffer, " \n", &save);
    if (c == NULL)
        return 0;
    else
    {
        strcpy(b, c);
        return 1;
    }
}