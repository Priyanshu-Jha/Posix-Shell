#include <iostream>
#include <vector>
#include <unordered_set>
#include <cstdlib>
#include <string.h>
#include <algorithm>

#include "header.h"
#include <fcntl.h>
#include <unistd.h>
using namespace std;
string trim(string str)
{
    string ans = "";
    int i = 0;
    for (; i < str.size(); i++)
    {
        if (str[i] != ' ')
            break;
    }
    for (; i < str.size(); i++)
    {
        ans += str[i];
    }
    return ans;
}
int main()
{
    char path2[128];

    getcwd(path2, sizeof(path2));
    long long fo = open("history.txt", O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
    // cout << fo << endl;
    vector<string> historyStore;
    string prevdirectory = "", currdirectory = "";
    // cout << fo << endl;
    int i = 0;
    while (path2[i] != '\0')
    {
        prevdirectory += path2[i];
        i++;
    }
    // cout << fo << endl;
    vector<string>
        directoryHistory;
    string rootAddress = prevdirectory;
    string currAddress = "";
    string prevAddress = "";

    directoryHistory.push_back("");

    int cnt = 0;

    string ans = "";

    int index = 0;
    // cout << fo << endl;
    while (1)
    {
        char input1[128], input3[128];
        char input[128];
        string taken;
        string input2;
        // cout << fo << endl;
        printUserName(currAddress);
        // cout << fo << endl;
        char ch;
        // DONE UPKEY

        input2 = upkeyHandlerjkbk();
        if (input2.size() == 0)
        {
            cout << endl;
            continue;
        }
        input2 = trim(input2);
        // cout << fo << endl;
        cout << endl;

        char path3[128];
        // cout << fo << endl;
        getcwd(path3, sizeof(path3));

        strcpy(input, input2.c_str());

        for (int i = 0; i < 128; i++)
            input1[i] = input[i];
        string inputstr = "";

        int i = 0;
        string temp = "";
        while (input[i] != '\0')
        {
            temp += input[i];
            i++;
        }

        string historyinput = temp + '\n';

        write(fo, historyinput.c_str(), historyinput.size());
        historyStore.push_back(temp);

        char *splitInput = strtok(input, " ");
        vector<string> inputs;
        while (splitInput != NULL)
        {
            inputs.push_back((string)splitInput); // print the string token
            inputstr += (string)splitInput;
            splitInput = strtok(NULL, " ");
        }

        // COMPLETE
        if (inputs[0] == "pinfo")
        {
            processinfo(inputs.size(), inputs);
        }
        else if (find(inputs.begin(), inputs.end(), "|") != inputs.end())
        {
            vector<string> commands;
            string current_command;
            for (const string &token : inputs)
            {
                if (token == "|")
                {
                    commands.push_back(current_command);
                    current_command.clear();
                }
                else
                {
                    if (!current_command.empty())
                        current_command += " ";
                    current_command += token;
                }
            }
            if (!current_command.empty())
                commands.push_back(current_command);

            call_pip(commands);
        }
        // COMPLETE
        // else if (inputs[1] == ">" or inputs[1] == "<" or inputs[1] == ">>")
        else if (find(inputs.begin(),
                      inputs.end(), "<") != inputs.end() or
                 find(inputs.begin(),
                      inputs.end(), ">") != inputs.end() or
                 find(inputs.begin(),
                      inputs.end(), ">>") != inputs.end())
        {
            // cout << "incom" << endl;
            executecommand(input1);
        }
        else if (inputs[0] == "history")
        {
            if (inputs.size() > 2)
            {
                cout << "bash: history: too many arguments\n";
                continue;
            }
            // cout << "e" << endl;
            if (inputs.size() > 1 and !all_of(inputs[1].begin(), inputs[1].end(), ::isdigit))
            {
                cout << "bash:" << inputs[1] << ": valid argument required\n";
                continue;
            }
            // cout << "e";
            if (inputs.size() > 1)
                historystore(stoi(inputs[1]));
            else
                historystore(10);
        }
        // DONE
        else if (inputs[0] == "exit")
            return 0;

        // DONE
        else if (inputs[0] == "cd")
            changeDirectory(inputs, cnt, prevAddress, currAddress, rootAddress);

        // Partial
        else if (inputs[0] == "ls")
            callLs(inputs);

        // ECHO DONE
        else if (inputs[0] == "echo")
        {
            echoExecute(input1);
            cout << endl;
        }

        // PWD  DONE
        else if (inputs[0] == "pwd")
            printpwd();

        // SEARCH DONE
        else if (inputs[0] == "search")
        {
            bool flag = false;
            listFilesRecursively(path3, inputs[1], flag);
            if (flag)
                cout << "True\n";
            else
                cout << "No\n";
        }

        else if (inputs[0] == "printHis")
        {
            for (auto it : directoryHistory)
                cout << it << endl;
        }

        else if (inputs[0] == "clear")
        {
            // The escape sequence for clearing the screen is "\033[2J",
            // and to move the cursor to the home position is "\033[H".
            cout << "\033[2J\033[H";
        }
        else
        {
            backgroundAndForeground(inputs[0], inputs);
            // cout << "Command " << inputs[0] << " not found\n";
        }
    }
}