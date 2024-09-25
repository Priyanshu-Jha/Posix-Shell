#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <cstring>
#include <vector>
#include <string>
#include "header.h"
using namespace std;

void runForeground(const char *cmd, char *argv[])
{
    int pid = fork();
    if (pid < 0)
    {
        cout << "Fork failed";
        return;
    }

    if (pid == 0)
    {                      // Child process
        execvp(cmd, argv); // Execute the command
        cout << "Command not found";
        exit(1);
    }
    else
    {                             // Parent process
        waitpid(pid, nullptr, 0); // Wait for the child process to complete
    }
    // cout << endl;
}

// Function to run a command in the background
void runBackground(const char *cmd, char *const argv[])
{
    int pid = fork();
    if (pid < 0)
    {
        cout << "Fork failed";
        return;
    }

    if (pid == 0)
    {                      // Child process
        execvp(cmd, argv); // Execute the command
        cout << "Command not found";
        exit(1);
    }
    else
    { // Parent process
        cout << "Background process PID: " << pid << endl;
    }
    // cout << endl;
}

void backgroundAndForeground(string cmd, vector<string> args)
{

    vector<char *> foreg;

    for (const auto &arg : args)
    {
        foreg.push_back(const_cast<char *>(arg.c_str()));
    }
    foreg.push_back(NULL); // Null-terminate the argument list

    // Example of running a command in the foreground

    if (args[args.size() - 1] == "&")
    {
        cout << "Running `" << cmd << "` in the background:" << endl;
        runBackground(cmd.c_str(), foreg.data());
    }
    else
    {
        cout << "Running `" << cmd << "` in the foreground:" << endl;
        runForeground(cmd.c_str(), foreg.data());
    }

    return;
}
