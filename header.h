#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <unistd.h>
// #include<time.h>
void ls(char *path);
#define ll long long
#define INPUT_SIZE 1000

void print_shell_prompt();
void pwd();
void echo_parser(char *input);
int parse_command(char a[], char b[]);
