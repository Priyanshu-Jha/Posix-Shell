#ifndef HEADER_H
#define HEADER_H
#include <vector>
#include <string>
using namespace std;

void executecommand(char *);
void echoExecute(string);
int callLs(vector<string>);
void changeDirectory(vector<string>, int &, string &, string &, string &);
void printUserName(string &);
void printpwd();
void historystore(int);
void listFilesRecursively(char *, string, bool &);
vector<string> historyreturn(int);
void processinfo(int num_of_args, vector<string> str);
string upkeyHandlerjkbk();
void backgroundAndForeground(string str, vector<string> ans);
void call_pip(const vector<string> &commands);

#endif