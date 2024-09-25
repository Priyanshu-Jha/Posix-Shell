#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include "header.h"
using namespace std;

void executecommand(char *input)
{
    // cout << input << endl;
    char *args[100];
    char *infile = NULL;
    char *outfile = NULL;
    int append = 0;
    int i = 0;

    // Tokenize the input
    char *token = strtok(input, " ");
    // cout << "Checkinf" << endl;
    while (token != NULL)
    {
        if (strcmp(token, "<") == 0)
        {
            infile = strtok(NULL, " ");
        }
        else if (strcmp(token, ">") == 0)
        {
            outfile = strtok(NULL, " ");
        }
        else if (strcmp(token, ">>") == 0)
        {
            outfile = strtok(NULL, " ");
            append = 1;
        }
        else
        {
            args[i++] = token;
        }
        token = strtok(NULL, " ");
    }
    // string s= token;
    // trim(s);
    // trim(token[1].c_str());

    args[i] = NULL;

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    // cout << "Checkinf" << endl;
    if (pid == 0)
    {
        // cout << infile << endl;
        // cout << "Checkinf" << endl;
        if (infile)
        {
            // cout << "Checkinf" << endl;
            int fd_in = open(infile, O_RDONLY);
            if (fd_in < 0)
            {
                perror("open infile");
                exit(EXIT_FAILURE);
            }
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }
        // cout << outfile << endl;
        if (outfile)
        {
            // cout << "Checkinf" << endl;
            int fd_out;
            if (append)
            {
                fd_out = open(outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
                // cout << "Checkinf" << endl;
            }
            else
            {
                fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                // cout << "Checkinf" << endl;
            }
            if (fd_out < 0)
            {
                perror("open outfile");
                exit(EXIT_FAILURE);
            }
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }

        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    }
    else
    {
        wait(NULL);
    }
}
