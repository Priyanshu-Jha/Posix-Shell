#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "header.h"
using namespace std;

void historystore(int x)
{
    // cout << "e";
    fstream data_file;
    string data, prev;
    data_file.open("history.txt", ios::in);
    vector<string> ans;
    int n = 0;
    if (data_file.is_open())
    {
        string data;
        while (getline(data_file, data))
        {
            // cout << "e";
            // if (data == prev)
            {
                // continue;
                n++;
            }
            ans.push_back(data);

            // prev = data;
        }
        data_file.close();
    }

    n = ans.size();
    if (n > x)
        n = x;
    if (n > 20)
        n = 20;
    // cout << ans.size() << endl;
    reverse(ans.begin(), ans.end());
    reverse(ans.begin(), ans.begin() + n);
    for (int i = 0; i < n; i++)
        cout << ans[i] << endl;
    // return ans;
}
