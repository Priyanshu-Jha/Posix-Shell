#include <iostream>
#include <unistd.h>
#include "header.h"
using namespace std;
void printUserName(string &str)
{
    char user[32];
    char host[64];

    // Get the username
    // getlogin() returns a pointer to a string containing the name of the
    //  user logged in on the controlling terminal of the process, or a NULL
    //   pointer if this information cannot be determined
    if (getlogin_r(user, sizeof(user)) == 0)
    {
        cout << user << "@";
    }
    else
    {
        cout << "Error getting username" << endl;
    }

    // Get the hostname
    if (gethostname(host, sizeof(host)) == 0)
    {
        cout << host << " : ";
    }
    else
    {
        cout << "Error getting hostname" << endl;
    }
    if (str.length() == 0)
    {
        cout << "~$ ";
    }
    else
    {
        cout << "~" << str << "$ ";
    }
}