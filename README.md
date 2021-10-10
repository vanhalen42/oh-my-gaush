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

---
## Assignment 3 (Extending the shell)
### Added files:
- `signal_handler.c`: is used to handle signals of Ctrl C(^C) and Ctrl Z(^Z).
- `replay.c`: implemented replay command (replays a command after intervals of t till period T is reached)

### Modified files: 
- `main.c`: for `replay`, pipelining.
- `processes.c`: for I/O redirection, implentation of `fg`,`bg`, `sig`, and `jobs`.
- `parser.c`: for parsing for `<`,`>`, `>>` and `|` symbols


### commands (features) implemented:
- I/O redirection: the `execute_command`(in `processes.c`) function does the io redirection based on the `io_in` and `io_out` variable passed to it.
- Command pipelines : the `pipe_parser`(in `paser.c`)command  parses a givne command into subsequent smaller ones and pipelining is implemented in `main.c`
- fg,bg, jobs and sig functions: implemented in the `execute_command`(in `processes.c`) 
- Signal_handling: the functions `ctrl_C` and `ctrl_Z` handle the flow of code when thre respectiv signals are given to the program.
- `replay`: done in `replay.c`