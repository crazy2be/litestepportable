#include <windows.h>
#include <string>
#include <fstream>
#include <direct.h>
#include <vector>

using namespace std;

/* methods... */
int PromptAction();
bool KillExplorer();
bool KillLitestep();
bool StartExplorer();
bool StartLitestep();
void SaveDriveData();
char GetDriveLetter();
