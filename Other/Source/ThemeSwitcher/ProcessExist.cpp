#include "ProcessExist.h"

bool ProcessRunning(string ProcessName) {
    DWORD aProcesses[1024], cbNeeded, cProcesses;
    
    unsigned int i;
    // Gets a list of running processes by PID
    EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded );
    
    cProcesses = cbNeeded / sizeof(DWORD);
    // does a for loop for each process
    for ( i = 0; i < cProcesses; i++ ) {
        // Mackes sure the array is valid
        if( aProcesses[i] != 0 ) {
            // Match found!
            if (GetProcessName(aProcesses[i]) == ProcessName) {
                return true;
            }
        }
    }
    return false;
}

string GetProcessName( DWORD processID )
{
	CHAR szProcessName[MAX_PATH] = "<unknown>";

	// Get a handle to the process.
	HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID );

	// Get the process name.
	if (NULL != hProcess )
	{
		HMODULE hMod;
		DWORD cbNeeded;

		if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod), &cbNeeded) )
			GetModuleBaseNameA( hProcess, hMod, szProcessName, sizeof(szProcessName)/sizeof(TCHAR) );
	}

	// Convert the process name to lowercase
	for (size_t i = 0; i <= strlen(szProcessName); i++)
		szProcessName[i] = tolower(szProcessName[i]);

    // Close the handle to the process
	CloseHandle( hProcess );

    // Return the process name
	return string(szProcessName);
}
