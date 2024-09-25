#include <iostream>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <sys/types.h>
#include <vector>
#include "header.h"
#include <grp.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <cstdio>
#include <csignal>
#include <map>
#include <iomanip>
#include <ctime>
using namespace std;

void list_dir(char *path)
{
    struct dirent *entry;
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 and entry->d_name[0] != '.')
            cout << entry->d_name << endl;
    }

    closedir(dir);
}
void printFilesRecursively(char *basePath)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        {
            cout << dp->d_name << endl;
        }
    }

    closedir(dir);
}

// FOR LS -l
string getPermissions(mode_t mode)
{
    string perms;

    perms += ((mode & S_IRUSR) ? 'r' : '-');
    perms += ((mode & S_IWUSR) ? 'w' : '-');
    perms += ((mode & S_IXUSR) ? 'x' : '-');
    perms += ((mode & S_IRGRP) ? 'r' : '-');
    perms += ((mode & S_IWGRP) ? 'w' : '-');
    perms += ((mode & S_IXGRP) ? 'x' : '-');
    perms += ((mode & S_IROTH) ? 'r' : '-');
    perms += ((mode & S_IWOTH) ? 'w' : '-');
    perms += ((mode & S_IXOTH) ? 'x' : '-');

    return perms;
}

// Function to get the username from user ID
string getUserName(uid_t uid)
{
    struct passwd *pw = getpwuid(uid);
    return (pw) ? pw->pw_name : "unknown";
}

// Function to get the group name from group ID
string getGroupName(gid_t gid)
{
    struct group *gr = getgrgid(gid);
    return (gr) ? gr->gr_name : "unknown";
}

// Function to format the modification time
string formatTime(const time_t &time)
{
    char buffer[80];
    struct tm *tm_info = localtime(&time);
    strftime(buffer, sizeof(buffer), "%b %d %Y %H:%M:%S", tm_info);
    return string(buffer);
}

int printfileLong()
{
    // const char *dirPath = (argc > 1) ? argv[1] : ".";
    char path[128];
    getcwd(path, 128);
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    dir = opendir(path);
    if (dir == nullptr)
    {
        cout << "Error: Unable to open directory " << path << '\n';
        return 1;
    }

    while ((entry = readdir(dir)) != nullptr)
    {
        if (entry->d_name[0] != '.')
        {
            string filePath = string(path) + "/" + entry->d_name;

            if (stat(filePath.c_str(), &fileStat) == -1)
            {
                cerr << "Error: Unable to stat file " << entry->d_name << '\n';
                continue;
            }

            cout << (S_ISDIR(fileStat.st_mode) ? 'd' : '-') << ' ';
            cout << getPermissions(fileStat.st_mode) << ' ';
            cout << setw(5) << fileStat.st_nlink << ' ';
            cout << setw(8) << getUserName(fileStat.st_uid) << ' ';
            cout << setw(8) << getGroupName(fileStat.st_gid) << ' ';
            cout << setw(10) << fileStat.st_size << ' ';
            cout << formatTime(fileStat.st_mtime) << ' ';
            cout << entry->d_name << '\n';
        }
    }

    closedir(dir);
    return 0;
}
int printfileLonghidden()
{
    // const char *dirPath = (argc > 1) ? argv[1] : ".";
    char path[128];
    getcwd(path, 128);
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    dir = opendir(path);
    if (dir == nullptr)
    {
        cout << "Error: Unable to open directory " << path << '\n';
        return 1;
    }

    while ((entry = readdir(dir)) != nullptr)
    {
        // if (entry->d_name[0] != '.')
        {
            string filePath = string(path) + "/" + entry->d_name;

            if (stat(filePath.c_str(), &fileStat) == -1)
            {
                cerr << "Error: Unable to stat file " << entry->d_name << '\n';
                continue;
            }

            cout << (S_ISDIR(fileStat.st_mode) ? 'd' : '-') << ' ';
            cout << getPermissions(fileStat.st_mode) << ' ';
            cout << setw(5) << fileStat.st_nlink << ' ';
            cout << setw(8) << getUserName(fileStat.st_uid) << ' ';
            cout << setw(8) << getGroupName(fileStat.st_gid) << ' ';
            cout << setw(10) << fileStat.st_size << ' ';
            cout << formatTime(fileStat.st_mtime) << ' ';
            cout << entry->d_name << '\n';
        }
    }

    closedir(dir);
    return 0;
}

int callLs(vector<string> arr)
{
    char path[1024];

    getcwd(path, sizeof(path));
    if (arr.size() == 1)
        list_dir(path);
    else if (arr.size() == 2)
    {
        if (arr[1] == "-a")
            printFilesRecursively(path);
        else if (arr[1] == "-l")
            printfileLong();
        else if (arr[1] == "." or arr[1] == "~")
            list_dir(path);
        else if (arr[1] == "..")
        {
        }
        else if (arr[1] == "-la" or arr[1] == "-al")
            printfileLonghidden();
    }
    else if (arr.size() == 3)
    {
        if ((arr[1] == "-a" and arr[2] == "-l") or (arr[1] == "-l" and arr[2] == "-a"))
            printfileLonghidden();
    }

    return 0;
}
