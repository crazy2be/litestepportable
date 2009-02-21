#include <windows.h>
#include <psapi.h>
#include <string>

using namespace std;

/* Functions... */
string GetProcessName( DWORD processID );
bool ProcessRunning( string ProcessName );
