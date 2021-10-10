HEADER_FILE=header.h
OBJECT_FILES=main.o shell_prompt.o ls.o built_in.o parser.o processes.o pinfo.o signal_handler.o replay.o
SOURCE_FILES=main.c shell_prompt.c ls.c built_in.c parser.c processes.c pinfo.c signal_handler.c replay.c
SHELL_NAME=oh-my-gaush
CC=gcc
# CFLAGS=
object: $(OBJECT_FILES) $(HEADER_FILE)
	$(CC) $(OBJECT_FILES) -g -o $(SHELL_NAME)
OBJECT_FILES: $(SOURCE_FILES) $(HEADER_FILE)
	$(CC) -g -c $(SOURCE_FILES)
clean:
	rm *.o