#include <windows.h>
#include <windowsx.h>
#include <process.h>
#include <string.h>
#include <sstream>
#include <direct.h>
#include "GlobalVars.h"

using namespace std;

/* Function Declarations */
void InstallTheme(string ThemePath);
void InstallThemeCMD(string ThemePath);
void UpdateInfoLoop(void* nothing);

string PromptForThemeFile();
bool ExtractTheme(string ThemePath);
void WaitForSevenZipExit( void* Nothing );
