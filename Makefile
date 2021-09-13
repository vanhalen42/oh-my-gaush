HEADER_FILE=header.h
OBJECT_FILES=main.o shell_prompt.o ls.o built_in.o parser.o
SOURCE_FILES=main.c shell_prompt.c ls.c built_in.c parser.c
CC=gcc
# CFLAGS=
object: $(OBJECT_FILES)
	$(CC) $(OBJECT_FILES) -g -o oh-my-gaush
OBJECT_FILES: $(SOURCE_FILES)
	$(CC) -g -c $(SOURCE_FILES)
clean:
	rm *.o