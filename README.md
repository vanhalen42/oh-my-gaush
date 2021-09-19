# oh-my-gaush
oh my gaush! (gaurav's shell).A shell implemented in C. 

you can run make which makes the executable **oh-my-gaush** which will run the shell
## files:
- header.h: contains all header files
- main.c : contains driver code
- Makefile : to compile the code
- parser.c : used for parsing the command into command and arguments 
- pinfo.c: to implement pinfo
- processes.c: to implement foreground and background processes
- shell_prompt.c: to diplay the shell prompt
- built_in.c: for built in fucntions i.e. cd, pwd and echo
- ls.c : to implement working of ls

## commands implemented
- cd, pwd, ls with flags, echo
- non-terminal commands