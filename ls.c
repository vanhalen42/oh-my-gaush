#include "header.h"
void ls(char *flags, char argv[][INPUT_SIZE], int argc)
{
    if (argc == 1)
    {
        strcpy(argv[1], ".");
        argc++;
    }
    for (int i = 1; i < argc; i++)
    {
        DIR *dir = opendir(argv[i]);
        if (dir == NULL)
        {
            perror("Directory");
            continue;
        }
        // list all files in the directory
        struct dirent *entry;
        printf("%s\n--------------------------------------------------\n", argv[i]);
        while ((entry = readdir(dir)) != NULL)
        {
            if (flag_in('l', flags) && entry->d_name[0] != '.')
            {
                struct stat statbuf;
                stat(entry->d_name, &statbuf);
                // rwx permissions
                printf((S_ISDIR(statbuf.st_mode)) ? "d" : "-");
                printf((statbuf.st_mode & S_IRUSR) ? "r" : "-");
                printf((statbuf.st_mode & S_IWUSR) ? "w" : "-");
                printf((statbuf.st_mode & S_IXUSR) ? "x" : "-");
                printf((statbuf.st_mode & S_IRGRP) ? "r" : "-");
                printf((statbuf.st_mode & S_IWGRP) ? "w" : "-");
                printf((statbuf.st_mode & S_IXGRP) ? "x" : "-");
                printf((statbuf.st_mode & S_IROTH) ? "r" : "-");
                printf((statbuf.st_mode & S_IWOTH) ? "w" : "-");
                printf((statbuf.st_mode & S_IXOTH) ? "x\t" : "-\t");
                printf("%s\t", entry->d_name);
                printf("%d\t", (int)statbuf.st_size);
                printf("%s", ctime(&statbuf.st_mtime));
            }

            else if (flag_in('a', flags))
            {
                printf("%s\n", entry->d_name);
            }
            else
            {
                if (entry->d_name[0] != '.')
                    printf("%s\n", entry->d_name);
            }
        }
        closedir(dir);
        printf("\n");
    }
    return;
}
