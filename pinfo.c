#include "header.h"

void pinfo(char *command, char argv[][INPUT_SIZE], int argc, char *home)
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
    char buf[total_bytes];
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
    printf("pid -- %s\n", status[0]);
    printf("Process Status -- %s", status[2]);
    if (strcmp(status[0], status[7]) == 0)
    {
        printf("+");
    }
    printf("\n");

    printf("memory -- %s {Virtual Memory}\n", status[22]);
    strcpy(proc_file_path, "/proc/");
    strcat(proc_file_path, pid_str);
    strcat(proc_file_path, "/exe");
    strcpy(buf, "");
    int link_size = readlink(proc_file_path, buf, sizeof(buf));
    char relative[INPUT_SIZE];
    if (link_size < 0)
    {
        printf(RED "Executable Path -- %s\n", strerror(errno));
    }
    else
    {
        get_relative_dir(buf, home, relative);
        printf("Executable Path -- %s\n", relative);
    }
}
char  get_pinfo(int pid)
{

    char pid_str[50];
    sprintf(pid_str, "%d", pid);
    char proc_file_path[INPUT_SIZE] = "/proc/";
    strcat(proc_file_path, pid_str);
    strcat(proc_file_path, "/stat");
    // printf(proc_file_path);
    int f = open(proc_file_path, O_RDONLY);
    if (f < 0)
    {
        printf(RED "Such a process doesnt exist.\n");
        return 0;
    }
    int total_bytes = 10002;
    lseek(f, 0, SEEK_SET);
    char buf[total_bytes];
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
    return status[2][0];
}
