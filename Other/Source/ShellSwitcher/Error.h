#include <windows.h>
#include <windowsx.h>
#include <process.h>
#include <string>

using namespace std;

void Error(string ErrorMessage);
void Warning(string WarningMessage);
void Info(string Information);
void Status(string NewStatus);
void ResetStatus( void* Nothing );

string GetErrorString(DWORD ErrorCode);
