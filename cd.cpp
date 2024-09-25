#include <iostream>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <sys/stat.h>
#include <sys/types.h>
#include <string>
#include "header.h"
using namespace std;

void changeDirectory(vector<string> str, int &cnt, string &prev, string &curr, string &root)
{

    char path[128], path1[128];

    getcwd(path, sizeof(path));
    getcwd(path1, sizeof(path1));

    if (str[0] == "cd" and (str.size() == 1))
    {

        return;
    }
    // Check if the path is relative
    else if (str[0] == "cd" and str.size() == 2)
    {
        if (str[1] == ".")
        {

            return;
        }
        else if (str[1] == "..")
        {
            // Use the previous working directory
            if (path == root)
                return;
            chdir("..");
            char path2[128];
            getcwd(path2, sizeof(path2));
            prev = curr;
            curr = "";
            int n = sizeof(path2) / sizeof(char);

            string path3 = path2;

            int i = root.size();
            while (path3[i] != '\0')
            {
                curr += path3[i];
                i++;
            }
        }
        else if (str[1] == "~")
        {

            chdir(root.c_str());
            prev = curr;
            curr = "";
        }
        else if (str[1] == "-")
        {
            if (prev.empty())
            {

                prev = curr;
                curr = "";
                chdir(curr.c_str());
                return;
            }
            chdir(prev.c_str());
            swap(prev, curr);
        }
        else
        {
            char ch[128];

            string temp = str[1];
            int open = chdir(temp.c_str());
            if (open == -1)
            {
                perror("cd");
                return;
            }
            for (int j = 0; j < str[1].length(); j++)
            {

                ch[j] = str[1][j];
            }
            prev = curr;
            char path2[128];
            getcwd(path2, sizeof(path2));
            string path3 = path2;
            int i = root.size();

            curr = "";
            while (path3[i] != '\0')
            {
                curr += path3[i];
                i++;
            }
        }
    }
    else
        perror("cd");
}