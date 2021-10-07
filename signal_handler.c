#include "header.h"

void ctrl_C(int signum)
{
    if (running_pid != shell_pid)
    {
        int ret = kill(running_pid, SIGKILL);
        if (ret < 0)
        {
            printf("Error: %s", strerror(errno));
            exit(0);
        }
    }
    return;
}
void ctrl_Z(int signum)
{
    if (running_pid != shell_pid)
    {
        int ret = kill(running_pid, SIGSTOP);
        if (ret < 0)
        {
            printf("Error: %s", strerror(errno));
            exit(0);
        }
    }
    return;
}