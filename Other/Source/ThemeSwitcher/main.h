#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>
#include <sstream>

#include "GlobalVars.h"

using namespace std;
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ButtonWindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

/* Declare other functions */
void GetInstalledThemes();
void SwitchTheme(string ThemeName);
void Error(string ErrorMessage);

/*  Make the class name into a global variable  */
char szClassName[ ] = "LSTM";
HWND ThemeListhwnd;
HWND BottomButtonshwnd; /* contains all the buttons at the bottom */
HWND InstallThemehwnd;
HWND SwitchThemehwnd;
HWND RefreshThemeListhwnd;
HWND Settingshwnd;

/* The array of theme names */
string ThemeNames[50];
