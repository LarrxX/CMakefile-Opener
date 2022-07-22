#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include <windows.h>

//DON'T FORGET THE SPACE AT THE END!
//DON'T FORGET THE SPACE AT THE END!
#define CMAKE_PROGRAM L"\"C:/Users/Marwan/AppData/Local/Programs/Microsoft VS Code/Code.exe\" "
#define TXT_PROGRAM L"\"C:/Program Files/Notepad++/notepad++.exe\" "
//DON'T FORGET THE SPACE AT THE END!
//DON'T FORGET THE SPACE AT THE END!

using namespace std;

bool ends_with(const string& str, const string& suffix)
{
  return str.size() >= suffix.size() &&
    str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    cerr << "This program requires only one argument to run, the name of the file to open." << endl;
    system("pause");
    exit(1);
  }

  LPWSTR* wargv;
  int wargc;
  wargv = CommandLineToArgvW(GetCommandLineW(), &wargc);

  //Launch the other process
  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  ZeroMemory(&si, sizeof(si));
  si.cb = sizeof(si);
  ZeroMemory(&pi, sizeof(pi));

  wstring commandLine;
  string ARGV1(argv[1]);
  transform(ARGV1.begin(), ARGV1.end(), ARGV1.begin(), ::toupper);

  if (ends_with(ARGV1, "CMAKELISTS.TXT"))
  {
    commandLine = CMAKE_PROGRAM;
  }
  else
  {
    commandLine = TXT_PROGRAM;
  }
  commandLine += L"\"" + wstring(wargv[1]) + L"\"";

  CreateProcess(NULL,
                const_cast<wchar_t*>(commandLine.c_str()),
                NULL,
                NULL,
                FALSE,
                CREATE_NEW_CONSOLE,
                NULL,
                NULL,
                &si,
                &pi);


  LocalFree(wargv);
  return 0;
}
