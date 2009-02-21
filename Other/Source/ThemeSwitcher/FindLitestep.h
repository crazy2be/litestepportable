#include <windows.h>
#include <direct.h>
#include <string>
#include <iostream>
#include "GlobalVars.h"

using namespace std;

/* Function declarations */
void ValidatePaths();
string FindLiteStepExe();
string FindLiteStepExePath();
string FindThemesDirPath();
int FindFile(string FilesToFind[], unsigned int Length);
