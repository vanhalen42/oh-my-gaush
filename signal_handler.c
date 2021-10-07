#include "header.h"

void ctrl_C(int signum)
{
    if (running_pid != shell_pid)
        kill(running_pid, SIGKILL);
}
void ctrl_Z(int signum)
{
    if (running_pid != shell_pid)
    {
        kill(running_pid, SIGSTOP);
    }
}