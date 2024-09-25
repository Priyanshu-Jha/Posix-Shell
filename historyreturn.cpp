#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "header.h"
using namespace std;
vector<string> historyreturn(int n)
{

    fstream data_file;
    string data, prev;
    data_file.open("history.txt", ios::in);
    vector<string> ans;
    int len = 0;
    if (data_file.is_open())
    {
        string data;
        while (getline(data_file, data))
        {

            if (data == prev)
            {
                continue;
                len++;
            }
            ans.push_back(data);

            prev = data;
        }
        data_file.close();
    }
    if (len > n)
        len = n;
    if (len > 20)
        len = 20;
    reverse(ans.begin(), ans.end());
    reverse(ans.begin(), ans.begin() + len);

    return ans;
}