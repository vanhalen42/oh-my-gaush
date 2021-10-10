#include "header.h"
int replay(char command[], int *ret_interval)
{
    int len = strlen(command);
    char tokens[INPUT_SIZE][INPUT_SIZE] = {""};
    char *save, *c, buffer[INPUT_SIZE];
    strcpy(buffer, command);
    c = strtok_r(buffer, " \t\n", &save);
    if (strcmp(c, "replay") != 0)
        return -1;
    int interval = -1, period = -1;
    while (c != NULL)
    {
        if (strcmp(c, "-period") == 0)
        {
            c = strtok_r(NULL, " \t\n", &save);
            period = atoi(c);
        }
        if (strcmp(c, "-interval") == 0)
        {
            c = strtok_r(NULL, " \t\n", &save);
            interval = atoi(c);
        }
        if (c == NULL)
            break;
        c = strtok_r(NULL, " \t\n", &save);
    }
    if (interval < 0 || period < 0)
    {
        printf(RED "flags not specified properly!\n" INPUT_COLOR);
        return 0;
    }
    *ret_interval = interval;
    strcpy(buffer, command);
    c = strtok_r(buffer, " \t\n", &save);
    while (c != NULL)
    {
        if (strcmp(c, "-command") == 0)
        {
            c = strtok_r(NULL, " \t\n", &save);
            strcpy(command, "");
            while (c != NULL && strcmp(c, "-interval") != 0 && strcmp(c, "-period") != 0)
            {
                strcat(command, c);
                strcat(command, " ");
                c = strtok_r(NULL, " \t\n", &save);
            }
        }
        if (c == NULL)
            break;
        c = strtok_r(NULL, " \t\n", &save);
    }
    return period / interval;
}