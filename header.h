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
#include<time.h>
#define ll long long
#define INPUT_SIZE 1000

void print_shell_prompt(char home[]);
void pwd(char *home);
void ls(char *flags, char argv[][INPUT_SIZE], int argc);
void echo_parser(char *input);
int parse_command(char *input, char *command, char argv[][INPUT_SIZE], char *flags);
void cd_parser(char *input, char *home);
void get_relative_dir(char *dir, char *home, char *relative);
void get_absolute_dir(char *dir, char *home, char *absolute);
void foreground(char *input_str, char *command);
int parse_semicolon(char a[], char b[][INPUT_SIZE]);
int flags_parser(char *input, char *flags);
int flag_in(char flag, char *flags);
