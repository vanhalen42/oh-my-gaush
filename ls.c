#include "header.h"
void ls(char *flags, char argv[][INPUT_SIZE], int argc, char *home)
{
    char current_dir[INPUT_SIZE];
    int flag_arg = 0;
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
            flag_arg++;
    }
    if (argc - flag_arg == 1)
    {
        strcpy(argv[1], ".");
        if (argc == 1)
            argc++;
    }
    for (int i = 1; i < argc; i++)
    {
        strcpy(current_dir, "");
        if (argv[i][0] == '-')
            continue;
        get_absolute_dir(argv[i], home, current_dir);
        DIR *dir = opendir(current_dir);
        if (dir == NULL)
        {
            if (print_ls_file(current_dir, flags, argv[i]) < 0)
            {
                printf("Error: %s\n", strerror(errno));
            }
            continue;
        }
        // list all files in the directory
        char last_modified[INPUT_SIZE];
        struct tm lt;
        struct dirent *entry;
        printf("%s:\n", current_dir);
        // int count = 0;
        if (flag_in('a', flags))
        {
            if (flag_in('l', flags))
            {
                printf("total %d\n", count_total(flags, current_dir, home));
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
                    struct tm time_present;
                    time_t present_time = time(NULL);
                    localtime_r(&present_time, &time_present);
                    int YEAR = lt.tm_year;
                    int MONTH1 = lt.tm_mon;
                    int present_year = time_present.tm_year;
                    int present_month = time_present.tm_mon;
                    int months_to_subtract = present_month - MONTH1;
                    if (YEAR != present_year || (YEAR == present_year && ((months_to_subtract >= 0 && months_to_subtract > 6) || (months_to_subtract < 0 && months_to_subtract < -6))))
                    {
                        strftime(last_modified, INPUT_SIZE, "%b %d %Y", localtime(&t));
                    }
                    else
                    {

                        strftime(last_modified, INPUT_SIZE, "%b %d %H:%M", localtime(&t));
                    }
                    // strftime(last_modified, INPUT_SIZE, "%c", &lt);
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
                printf("total %d\n", count_total(flags, current_dir, home));

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
                        struct tm time_present;
                        time_t present_time = time(NULL);
                        localtime_r(&present_time, &time_present);
                        int YEAR = lt.tm_year;
                        int MONTH1 = lt.tm_mon;
                        int present_year = time_present.tm_year;
                        int present_month = time_present.tm_mon;
                        int months_to_subtract = present_month - MONTH1;
                        if (YEAR != present_year || (YEAR == present_year && ((months_to_subtract >= 0 && months_to_subtract > 6) || (months_to_subtract < 0 && months_to_subtract < -6))))
                        {
                            strftime(last_modified, INPUT_SIZE, "%b %d %Y", localtime(&t));
                        }
                        else
                        {

                            strftime(last_modified, INPUT_SIZE, "%b %d %H:%M", localtime(&t));
                        }
                        // strftime(last_modified, INPUT_SIZE, "%c", &lt);
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
int print_ls_file(char *current_dir, char *flags, char *name)
{
    char last_modified[INPUT_SIZE];
    struct tm lt;
    struct dirent *entry;
    struct stat statbuf;
    char curr_file[INPUT_SIZE];
    strcpy(curr_file, current_dir);
    if (stat(curr_file, &statbuf) < 0)
        return -1;

    if (flag_in('l', flags))
    {
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
        struct tm time_present;
        time_t present_time = time(NULL);
        localtime_r(&present_time, &time_present);
        int YEAR = lt.tm_year;
        int MONTH1 = lt.tm_mon;
        int present_year = time_present.tm_year;
        int present_month = time_present.tm_mon;
        int months_to_subtract = present_month - MONTH1;
        if (YEAR != present_year || (YEAR == present_year && ((months_to_subtract >= 0 && months_to_subtract > 6) || (months_to_subtract < 0 && months_to_subtract < -6))))
        {
            strftime(last_modified, INPUT_SIZE, "%b %d %Y", localtime(&t));
        }
        else
        {

            strftime(last_modified, INPUT_SIZE, "%b %d %H:%M", localtime(&t));
        }
        // strftime(last_modified, INPUT_SIZE, "%c", &lt);
        printf("%s ", last_modified);
        printf("%s\n", name);
        // count += statbuf.st_blocks;
    }
    else
    {

        printf("%s\n", name);
    }
    return 0;
}
int count_total(char *flags, char *input, char *home)
{
    char current_dir[INPUT_SIZE];
    int count = 0;
    struct dirent *entry;
    get_relative_dir(input, home, current_dir);
    DIR *dir = opendir(current_dir);
    if (dir == NULL)
    {
        printf("Error: %s\n", strerror(errno));
        return 0;
    }
    if (flag_in('a', flags))
    {
        while ((entry = readdir(dir)) != NULL)
        {
            struct stat statbuf;
            char curr_file[INPUT_SIZE];
            strcpy(curr_file, current_dir);
            if (curr_file[strlen(curr_file) - 1] != '/')
            {
                strcat(curr_file, "/");
            }
            strcat(curr_file, entry->d_name);
            stat(curr_file, &statbuf);
            count += statbuf.st_blocks;
        }
    }
    else
    {
        while ((entry = readdir(dir)) != NULL)
        {
            if (entry->d_name[0] == '.')
                continue;
            struct stat statbuf;
            char curr_file[INPUT_SIZE];
            strcpy(curr_file, current_dir);
            if (curr_file[strlen(curr_file) - 1] != '/')
            {
                strcat(curr_file, "/");
            }
            strcat(curr_file, entry->d_name);
            stat(curr_file, &statbuf);
            count += statbuf.st_blocks;
        }
    }
    closedir(dir);
    return count / 2;
}
