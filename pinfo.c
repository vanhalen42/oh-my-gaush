#include "header.h"

void pinfo(char *command, char argv[][INPUT_SIZE], int argc)
{
    int pid;
    char pid_str[50];
    if (argc == 1)
    {
        pid = getpid();
        sprintf(pid_str, "%d", pid);
    }
    else if (argc > 2)
    {
        printf("Too many arguments\n");
        return;
    }
    else
    {
        strcpy(pid_str, argv[1]);
    }
    printf("pid -- %s\n", pid_str);
    char proc_file_path[INPUT_SIZE] = "/proc/";
    strcat(proc_file_path, pid_str);
    strcat(proc_file_path, "/stat");
    // printf(proc_file_path);
    int f = open(proc_file_path, O_RDONLY);
    if (f < 0)
    {
        printf(RED "Such a process doesnt exist.\n");
        return;
    }
    int total_bytes = 10002;
    lseek(f, 0, SEEK_SET);
    char *buf = (char *)malloc(total_bytes);
    int bytes = read(f, buf, total_bytes);
    buf[bytes] = '\0';
    close(f);
    char *status[100] = {0};
    int i = 0;
    status[i++] = strtok(buf, " ");
    while (status[i - 1] != NULL)
    {
        status[i++] = strtok(NULL, " ");
    }
    printf("Process Status -- %s", status[2]);
    if (strcmp(status[0], status[7]) == 0)
    {
        printf("+");
    }
    printf("\n");

    printf("memory -- %s {Virtual Memory}\n", status[22]);
}