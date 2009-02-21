/* Reguired Libraries */
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <windef.h>

#include <psapi.h>
#include <string>

using namespace std;

/*Define Methods*/
//bool ExplorerRunning();
//bool LitestepRunning();
//string GetProcessName( DWORD processID );
//void NoPromptAction();
//string GetSettingValue(string SettingToFind);
//int GetSettingIntValue(string SettingToFind);
void SaveDriveData();
char GetDriveLetter();

/*Define Global Variables*/
bool ExplorerIsRunning;
bool LitestepIsRunning;
DWORD LitestepPID;
DWORD ExplorerPID;
//int PromptLevel;
