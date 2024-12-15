#include<iostream>
#include<dirent.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string>
#include<sys/stat.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include<unistd.h>
using namespace std;


const char* mode_to_str(int mode)
{
    static char str[11];
    switch (mode & S_IFMT)
    {
        case S_IFSOCK:
            str[0] = 's';
            break;
        case S_IFLNK:
            str[0] = 'l';
            break;
        case S_IFREG:
            str[0] = '-';
            break;
        case S_IFBLK:
            str[0] = 'b';
            break;
        case S_IFDIR:
            str[0] = 'd';
            break;
        case S_IFCHR:
            str[0] = 'c';
            break;
        case S_IFIFO:
            str[0] = 'p';
            break;
        default:
            str[0] = '?';
            break;
    }

    str[1] = mode & S_IRUSR ? 'r' : '-';
    str[2] = mode & S_IWUSR ? 'w' : '-';
    str[3] = mode & S_IXUSR ? 'x' : '-';
    str[4] = mode & S_IRGRP ? 'r' : '-';
    str[5] = mode & S_IWGRP ? 'w' : '-';
    str[6] = mode & S_IXGRP ? 'x' : '-';
    str[7] = mode & S_IROTH ? 'r' : '-';
    str[8] = mode & S_IWOTH ? 'w' : '-';
    str[9] = mode & S_IXOTH ? 'x' : '-';
    str[10] = '\0';
    return str;
}

const char* uid_to_str(uid_t uid)
{
    static char usr_name[64];
    struct passwd* pwd = getpwuid(uid);
    if(pwd)
    {
        snprintf(usr_name, sizeof(usr_name), "%s", pwd->pw_name);
    }
    else
    {
        snprintf(usr_name, sizeof(usr_name), "Unknown");
    }
    return usr_name;
}


const char* gid_to_str(gid_t gid)
{
    static char gid_name[64];
    struct group* grp = getgrgid(gid);
    if(grp)
    {
        snprintf(gid_name, sizeof(gid_name), "%s", grp->gr_name);
    }
    else
    {
        snprintf(gid_name, sizeof(gid_name), "Unknown");
    }

    return gid_name;
}

const char* date_to_str(time_t time)
{
    static char date[64];
    struct tm* time_info = localtime(&time);
    if(time_info)
    {
        strftime(date, sizeof(date), "%h %d %H:%M", time_info);
    }
    else
    {
        snprintf(date, sizeof(date), "Invalid time");
    }
    return date;
}
int main(int argc, char* argv[])
{
    char* path = (char*)(argc > 1 ? argv[1] : ".");
    char full_path[256];
    DIR* dir = opendir(path);
    if(!dir)
    {
        perror("opendir:");
        exit(1);
    }
    struct dirent* entry;
    struct stat file_stat;
    while((entry = readdir(dir)) != NULL)
    {
        if(entry->d_name[0] != '.')
        {
            snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
            if(lstat(full_path, &file_stat) != 0)
            {
                perror("stat:");
                continue;
            }
            printf("%s  %ld %s %s %6ld %s %10s\n", mode_to_str(file_stat.st_mode), file_stat.st_nlink, 
            uid_to_str(file_stat.st_uid), gid_to_str(file_stat.st_gid), file_stat.st_size, 
                    date_to_str(file_stat.st_mtim.tv_sec), entry->d_name);

        }
    }
    return 0;
}