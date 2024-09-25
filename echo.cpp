#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include "header.h"
using namespace std;

void echoExecute(string str)
{

    queue<char> q;
    string temp = "";
    for (int i = 5; i < str.size(); i++)
        temp += str[i];
    string temp1 = "";
    // cout << temp << endl;
    bool flag = false;
    for (auto it : temp)
    {

        if (!q.empty() and q.front() != it)
        {

            temp1 += (it);
            continue;
        }
        else if (!q.empty() and q.front() == it)
        {

            cout << temp1 << " ";
            q.pop();
            temp1.clear();
            continue;
        }
        if (!q.empty() and q.front() != it)
        {

            temp1 += (it);
            continue;
        }
        else if (!q.empty() and q.front() == it)
        {

            cout << temp1 << " ";
            q.pop();
            temp1.clear();
            continue;
        }
        if (it == '\'' or it == '\"')
        {

            cout << temp1;
            if (!q.empty())
                cout << " ";
            temp1.clear();
            q.push(it);
            continue;
        }
        if (it != 32)
        {
            if (flag)
            {
                cout << temp1;
                temp1 = " ";
            }
            flag = false;
            temp1 += it;
        }
        else
            flag = true;
    }
    cout << temp1 << " ";
}