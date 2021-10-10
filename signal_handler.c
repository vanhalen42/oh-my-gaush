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
        else
        {
            printf("hahahaha\n");
            char process_name[INPUT_SIZE] = "unnamed process";
            int i;

            for (i = 0; i < total_bg_proc; i++)
            {
                if (bg_processes[i].pid == running_pid)
                    goto goto_else;
            }
            return;
        goto_else:
            i++;
            for (; i < total_bg_proc; i++)
            {
                bg_processes[i - 1] = bg_processes[i];
            }
            total_bg_proc--;
            running_pid = shell_pid;
        }
    }
    return;
}
void ctrl_Z(int signum)
{
    printf("running pid: %d\n shell pid: %d\n", running_pid, shell_pid);
    if (running_pid != shell_pid)
    {
        int ret = kill(running_pid, SIGSTOP);
        if (ret < 0)
        {
            printf("Error: %s", strerror(errno));
            exit(0);
        }
        else
        {
            for (int i = 0; i < total_bg_proc; i++)
            {
                if (bg_processes[i].pid == running_pid)
                {
                    printf("\n1[%d] Stopped %s with pid [%d]\n", bg_processes[i].jpb_no, bg_processes[i].proc_name, bg_processes[i].pid);
                    running_pid = shell_pid;
                    return;
                }
            }
            if (total_bg_proc >= INPUT_SIZE)
            {
                printf("LIMIT REACHED:can't execute more processes\n");
                int ret = kill(running_pid, SIGKILL);
                if (ret < 0)
                {
                    printf("Error: %s", strerror(errno));
                    exit(0);
                }
                running_pid = shell_pid;
                return;
            }
            char input[INPUT_SIZE] = "";
            get_pinfo(running_pid, 1, input);
            printf("\n%d\n", running_pid);
            bg_processes[total_bg_proc].pid = running_pid;
            strcpy(bg_processes[total_bg_proc].proc_name, input);
            bg_processes[total_bg_proc].jpb_no = job_number;
            job_number++;
            total_bg_proc++;
            running_pid = shell_pid;
            printf("\n2[%d] Stopped %s with pid [%d]\n", bg_processes[total_bg_proc - 1].jpb_no, bg_processes[total_bg_proc - 1].proc_name, bg_processes[total_bg_proc - 1].pid);
        }
    }
    return;
}