#include <iostream>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <vector>
#include "header.h"
#include <string.h>

void listFilesRecursively(char *basePath, string str, bool &flag)
{
    char path[128];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {

            if (dp->d_name == str)
            {
                // cout << true;
                flag = true;
                return;
            }

            // Construct new path from our base path
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            listFilesRecursively(path, str, flag);
        }
    }

    closedir(dir);
}