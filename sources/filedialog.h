#ifndef _FILE_DIALOG
#define _FILE_DIALOG

#include <string>
using namespace std;

string getOpenFileName(const string &title="Open a file", const string &filter = "All files (*.*)", const string &initialDir = "");
string getSaveFileName(const string &title="Save file as", const string &filter = "All files (*.*)", const string &initialDir = "");
string browseFolder(const string &title = "Select a directory", const string &initialDir = "");

#endif