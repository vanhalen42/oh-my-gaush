#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#include <pwd.h>
// colours

#define GREY "\033[0;38;5;239m"

#define BLACK "\033[0;30;48;5;239m"
#define BLACK_BOLD "\033[1;30;48;5;239m"

#define GREEN "\033[0;38;5;40;48;5;239m"
#define GREEN_BOLD "\033[1;38;5;40;48;5;239m"

#define RED "\033[0;31m"
#define RED_BOLD "\033[1;31m"

#define YELLOW "\033[0;33;48;5;239m"
#define YELLOW_BOLD "\033[1;33;48;5;239m"

#define BLUE "\033[0;34;48;5;239m"
#define BLUE_BOLD "\033[1;34;48;5;239m"

#define PURPLE "\033[0;38;5;147;48;5;239m"
#define PURPLE_BOLD "\033[1;38;5;147;48;5;239m"

#define CYAN "\033[0;38;5;51;48;5;239m"
#define CYAN_BOLD "\033[1;38;5;51;48;5;239m"

#define INPUT_COLOR "\033[0;37m"
#define INPUT_WITH_BG "\033[0;37;48;5;239m"

#define ll long long
#define INPUT_SIZE 1000
extern int errno;
void print_shell_prompt(char home[], char *prev_command);
void pwd(char *home);
void ls(char *flags, char argv[][INPUT_SIZE], int argc, char *home);
int count_total(char *flags, char *input, char *home);
void echo_parser(char *input);
int parse_command(char *input, char *command, char argv[][INPUT_SIZE], char *flags);
void cd_parser(char *input, char *home);
void get_relative_dir(char *dir, char *home, char *relative);
void get_absolute_dir(char *dir, char *home, char *absolute);
void foreground(char *input_str, char *command);
int parse_semicolon(char a[], char b[][INPUT_SIZE]);
int pipe_parser(char input[], char output[][INPUT_SIZE]);
int flags_parser(char *input, char *flags);
int flag_in(char flag, char *flags);
void run_process(char *command, char argv[][INPUT_SIZE], int argc, int flag, char *flags);
void process(int signum);
void ctrl_C(int signum);
void ctrl_Z(int signum);

int execute_command(char *input, char *home_dir, char *command, char argv[][INPUT_SIZE], char *flags, int flag, int argc, char io_in[], char io_out[]);
int exec_pipe(char *input, char *home_dir, char *command, char argv[][INPUT_SIZE], char *flags, int flag, int argc, char io_in[], char io_out[]);

void pinfo(char *command, char argv[][INPUT_SIZE], int argc, char *home);
char get_pinfo(int pid);
int parse_io(char a[], char command[], char input[], char output[]);
extern int shell_pid;
extern int running_pid;
typedef struct proc
{
    int jpb_no;
    char proc_name[INPUT_SIZE];
    int pid;
} proc;
extern proc bg_processes[INPUT_SIZE];
extern int total_bg_proc, job_number, zflag, cflag;
extern int original_input, original_output;

#endif