#include <windows.h>
#include <string>
#include <sstream>
#include <windowsx.h>

using namespace std;

/* Functions */
void DisplaySettingsDialog();
LRESULT CALLBACK SettingsWindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
