#include <windows.h>
#include <psapi.h>
#include <string>

using namespace std;

/* Functions... */
string GetProcessName( DWORD processID );
DWORD ProcessRunning( string ProcessName );
