#include <unistd.h>
#include <iostream>
#include "header.h"
using namespace std;
void printpwd()
{
    char path[128];
    getcwd(path, sizeof(path));
    cout << path << endl;
}