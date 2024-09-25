#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>
#include <sstream>
#include <string>
#include "header.h"

using namespace std;
vector<string> toke(string str)
{
    vector<string> tokens;

    // stringstream class check1
    stringstream check1(str);

    string intermediate;

    // Tokenizing w.r.t. space ' '
    while (getline(check1, intermediate, ' '))
    {
        tokens.push_back(intermediate);
    }
    return tokens;
}

void call_pip(const vector<string> &commands)
{
    // for (auto it : commands)
    //     cout << it << " ";
    int nums = commands.size() - 1;
    vector<int[2]> pip(nums);

    // Create pip
    for (int i = 0; i < nums; ++i)
    {
        if (pipe(pip[i]) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < commands.size(); ++i)
    {
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            // Child process

            if (i > 0)
            {
                dup2(pip[i - 1][0], STDIN_FILENO);
            }

            if (i < nums)
            {                                   // Not the last command
                dup2(pip[i][1], STDOUT_FILENO); // Set stdout to write end of current pipe
            }

            // Close all pipe file descriptors
            for (int j = 0; j < nums; ++j)
            {
                close(pip[j][0]);
                close(pip[j][1]);
            }

            // Convert command to char* array
            vector<char *> args;
            vector<string> tokens = toke(commands[i]);
            for (const string &token : tokens)
            {
                args.push_back(const_cast<char *>(token.c_str()));
            }
            args.push_back(nullptr);

            // Execute the command
            execvp(args[0], args.data());
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }

    // Parent process closes all pipe file descriptors
    for (int i = 0; i < nums; ++i)
    {
        close(pip[i][0]);
        close(pip[i][1]);
    }

    // Wait for all child processes
    for (int i = 0; i < commands.size(); ++i)
    {
        wait(NULL);
    }
}