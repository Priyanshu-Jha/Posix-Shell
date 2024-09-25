#include <iostream>
#include <unistd.h>
#include <string.h>
#include <string>
#include <vector>
#include <termios.h>
#include <algorithm>
#include "header.h"
using namespace std;

struct termios oldt, newt;

void initTerminal()
{
    tcgetattr(STDIN_FILENO, &oldt);          // Get the current terminal settings
    newt = oldt;                             // Copy the settings to newt
    newt.c_lflag &= ~(ICANON | ECHO);        // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Set the new terminal settings
}

void resetTerminal()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore the old terminal settings
}

string handleInput()
{
    // cout << "checking" << endl;
    // char c;
    // string ans;
    int i = -1;
    char c;
    string x;
    // char ans[128];
    string ans = "";
    // cout << "checking" << endl;
    vector<string> histo = historyreturn(10);
    // cout << "checking" << endl;
    // reverse(histo.begin(), histo.begin() + histo.size());
    char length[128];
    getcwd(length, 128);
    int len = strlen(length);
    // cout << "checking" << endl;
    while (true)
    {
        char length[128];
        getcwd(length, 128);
        int len = strlen(length);
        // cout << len << endl;
        string escape_seq;
        c = getchar();
        if (c == '\n')
        {

            return ans;
            // break;
        }
        // cout << "checking" << endl;
        if (c == '\x1b')
        {              // Check if it's the escape character
            getchar(); // Skip the '['
            switch (getchar())
            {
            case 'A':
                escape_seq = "\033[" + to_string(len - 17) + "G";
                cout << escape_seq;
                // printf("\033[29G");
                // printf("\033[G");
                x = histo[++i % histo.size()];
                cout << x;
                ans = x;
                cout.flush();
                printf("\033[K");
                // printf("\033[K");
                break;
            default:
                break;
            }
        }

        else if (c == '\x7f' || c == 127) // Backspace key
        {
            if (!ans.empty())
            {
                ans.pop_back();
                cout << "\b";
                printf("\033[K");
                // cout.flush();
            }
        }
        else
        {
            ans += c;  // Add the character to the string
            cout << c; // Display the character
            cout.flush();
        }
    }
    // cout << ans << " ";
    return ans;
}

string upkeyHandlerjkbk()
{
    initTerminal();

    string ans = handleInput();
    resetTerminal();

    return ans;
}
