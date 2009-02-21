#include <windows.h>
#include <string>
#include <fstream>

using namespace std;

/* Functions */
void RefreshList(HWND ThemeListHWND, string ThemeNames[]);
void RefreshListCMD();
void AddThemeToThemeList(string ThemeName, HWND ThemeListHWND, string ThemeNames[]);
void ClearThemeList(HWND ThemeListHWND, string ThemeNames[]);
void AddThemeToThemeListFile(string ThemeName);
void ClearThemeListFile();
