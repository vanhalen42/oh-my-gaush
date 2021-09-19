#include "header.h"
void ls(char *flags, char argv[][INPUT_SIZE], int argc, char *home)
{
    char current_dir[INPUT_SIZE];
    if (argc == 1)
    {
        strcpy(argv[1], ".");
        argc++;
    }
    for (int i = 1; i < argc; i++)
    {
        strcpy(current_dir, "");
        get_absolute_dir(argv[i], home, current_dir);
        DIR *dir = opendir(current_dir);
        if (dir == NULL)
        {
            printf("Error: %s\n", strerror(errno));
            continue;
        }
        // list all files in the directory
        char last_modified[INPUT_SIZE];
        struct tm lt;
        struct dirent *entry;
        printf("%s\n--------------------------------------------------\n", current_dir);
        // int count = 0;
        if (flag_in('a', flags))
        {
            count_total(flags, argv, argc, home);
            if (flag_in('l', flags))
            {
                while ((entry = readdir(dir)) != NULL)
                {
                    struct stat statbuf;
                    char curr_file[INPUT_SIZE];
                    strcpy(curr_file, current_dir);
                    if (curr_file[strlen(curr_file) - 1] != '/')
                        strcat(curr_file, "/");
                    strcat(curr_file, entry->d_name);
                    stat(curr_file, &statbuf);
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
                    printf("%ld ", statbuf.st_nlink);
                    printf("%s %s ", getpwuid(statbuf.st_uid)->pw_name, getpwuid(statbuf.st_gid)->pw_name);
                    printf("%d\t", (int)statbuf.st_size);
                    time_t t = statbuf.st_mtime;
                    localtime_r(&t, &lt);
                    strftime(last_modified, INPUT_SIZE, "%c", &lt);
                    printf("%s ", last_modified);
                    printf("%s\n", entry->d_name);
                    // count += statbuf.st_blocks;
                }
            }
            else
            {
                while ((entry = readdir(dir)) != NULL)
                {
                    printf("%s\t", entry->d_name);
                }
            }
        }
        else
        {
            if (flag_in('l', flags))
            {
                count_total(flags, argv, argc, home);
                while ((entry = readdir(dir)) != NULL)
                {
                    if (entry->d_name[0] != '.')
                    {
                        struct stat statbuf;
                        char curr_file[INPUT_SIZE];
                        strcpy(curr_file, current_dir);
                        if (curr_file[strlen(curr_file) - 1] != '/')
                            strcat(curr_file, "/");
                        strcat(curr_file, entry->d_name);
                        stat(curr_file, &statbuf);
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
                        printf("%ld ", statbuf.st_nlink);
                        printf("%s %s ", getpwuid(statbuf.st_uid)->pw_name, getpwuid(statbuf.st_gid)->pw_name);
                        printf("%d\t", (int)statbuf.st_size);
                        time_t t = statbuf.st_mtime;
                        localtime_r(&t, &lt);
                        strftime(last_modified, INPUT_SIZE, "%c", &lt);
                        printf("%s ", last_modified);
                        printf("%s\n", entry->d_name);
                        // count += statbuf.st_blocks;
                    }
                }
            }
            else
            {
                while ((entry = readdir(dir)) != NULL)
                {
                    if (entry->d_name[0] != '.')
                        printf("%s\t", entry->d_name);
                }
            }
        }
        closedir(dir);
        // printf("total: %d\n", count);
        printf("\n");
    }
    return;
}
void count_total(char *flags, char argv[][INPUT_SIZE], int argc, char *home)
{
    if (argc == 1)
    {
        strcpy(argv[1], ".");
        argc++;
    }
    int count = 0;
    struct stat statbuf;
    char current_dir[INPUT_SIZE];
    for (int i = 1; i < argc; i++)
    {
        get_absolute_dir(argv[1], home, current_dir);
        // printf("currect dir: %s\n", current_dir);
        DIR *dir = opendir(current_dir);
        if (dir == NULL)
        {
            printf("Error: %s\n", strerror(errno));
            continue;
        }
        // list all files in the directory
        char last_modified[INPUT_SIZE];
        struct tm lt;
        struct dirent *entry;
        // int count = 0;
        if (flag_in('a', flags))
        {
            while ((entry = readdir(dir)) != NULL)
            {
                char curr_file[INPUT_SIZE];
                strcpy(curr_file, current_dir);
                if (curr_file[strlen(curr_file) - 1] != '/')
                    strcat(curr_file, "/");
                strcat(curr_file, entry->d_name);
                stat(curr_file, &statbuf);
                count += statbuf.st_blocks;
                // printf("count: %d\n", count);
            }
        }
        else
        {

            while ((entry = readdir(dir)) != NULL)
            {
                if (entry->d_name[0] != '.')
                {
                    char curr_file[INPUT_SIZE];
                    strcpy(curr_file, current_dir);
                    if (curr_file[strlen(curr_file) - 1] != '/')
                        strcat(curr_file, "/");
                    strcat(curr_file, entry->d_name);
                    stat(curr_file, &statbuf);
                    count += statbuf.st_blocks;
                    // printf("count: %d\n", count);
                }
            }
        }
        printf("total: %d\n", count / 2);
        closedir(dir);
        printf("\n");
    }
    return;
}
