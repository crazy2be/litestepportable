#include "Switcher.h"
#include "GlobalVars.h"
#include "GetSettings.h"
#include "Error.h"
#include "UpdateIcons.h"
#include "Splash.h"

int PromptAction() {  
    int PromptLevel = GetIntValue("PromptLevel");
	// If bolth shells are running...
	if (globalExplorerIsRunning && globalLitestepIsRunning) {
        if (PromptLevel > 1) {
		   if (MessageBox(NULL, "Bolth shells are active. Kill Litestep\nor Explorer?\n(Yes for Explorer, No for Litestep)", "Choose shell to kill", MB_YESNO) == IDYES) {
               KillExplorer();
           } else {
               KillLitestep();
           }
          } else {
             KillExplorer();
          }
          return 3;
    // If (only) explorer is running
	} else if (globalExplorerIsRunning) {
        if (PromptLevel > 2) {
		   if (MessageBox(NULL, "Explorer is active. Kill Explorer and start Litestep?", "Kill Explorer & start Litestep?", MB_YESNO) == IDYES) {
              KillExplorer();
              StartLitestep();
           } else {
              exit( EXIT_SUCCESS );
           }
        } else {
           KillExplorer();
           StartLitestep();
        }
        return 1;
    // If (only) Litestep is running
	} else if (globalLitestepIsRunning) {
        if (PromptLevel > 2) {
		    if (MessageBox(NULL, "Litestep is active. Kill Litestep and start Explorer?", "Kill Litestep & start Explorer?", MB_YESNO) == IDYES) {
                KillLitestep();
                StartExplorer();
            } else {
                exit( EXIT_SUCCESS );
            }
        } else {
           KillLitestep();
           StartExplorer();
        }
        return 2;
    // If nothing is running...
	} else {
        if (PromptLevel > 1) {
	    	if (MessageBox(NULL, "Neither Shell is Active. Start Litestep or Explorer?\n(Yes for Litestep, no for Explorer)", "Start Litestep or Explorer?", MB_YESNO) == IDYES) {
                StartLitestep();
            } else {
                StartExplorer();
            }
        } else {
            StartLitestep();
        }
        return 0;
	}
}

bool KillLitestep() {
     // Terminating Litestep
     if (GetBoolValue("Force Litestep Termination")) {
         HANDLE LitestepHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, globalLitestepPID);
         TerminateProcess(LitestepHandle, EXIT_SUCCESS);
     } else {
         ShellExecute( NULL, "open", GetValue("Litestep").c_str(), "!quit", NULL, SW_SHOW);
     }
    return false;
}

bool KillExplorer() {
     // Terminating Explorer
     HANDLE LitestepHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, globalExplorerPID);
     TerminateProcess(LitestepHandle, EXIT_FAILURE);
    return false;
}

bool StartLitestep() {
    // Starting Litestep
    
    // Show the splash
    SPLASH StartSplash;
    StartSplash.Init();
    StartSplash.Show();
    
    // Making the drive.rc file
    SaveDriveData();

    const bool DetectPA = GetBoolValue("DetectPortableApps");
    vector<string> AllApps;
     
    if (DetectPA)
        AllApps = UpdatePopup();
     
    ShellExecute( NULL, "open", GetValue("Litestep").c_str(), NULL, NULL, SW_SHOW);
     
    if (DetectPA)
        UpdateIcons(AllApps);
     
    return false;
}

bool StartExplorer() {
     // Starting Explorer
     ShellExecute( NULL, "open", "Explorer.exe", NULL, "C:\\", SW_SHOW);
    return false;
}

void SaveDriveData() {
     char disk = GetDriveLetter();
     ofstream DriveWriter;
     // Open the file for writing
     string LitestepPath = GetValue("Litestep");
     LitestepPath = LitestepPath.substr(
         0, LitestepPath.rfind("\\")+1);
     LitestepPath += "Drive.rc";
     //Info(LitestepPath);
     DriveWriter.open(LitestepPath.c_str());
     // If it was successfull...
     if (DriveWriter.is_open()) {
         // Write to the file...
         DriveWriter << "; AUTOMATICLY GENERATED FILE." << endl;
         DriveWriter << "; (any edits will be lost)" << endl;
         DriveWriter << "LSD  \"" << disk << ":\\\"" << endl;
     } else {
         // There was an error :(
         Error("ERROR WRITING TO DRIVE.RC\nThe application will now terminate");
         //system("PAUSE");
         exit( EXIT_FAILURE );
     }
     DriveWriter.close();
}

char GetDriveLetter() {
     /* Get the drive letter numerical representation
      * (1 = A, 2 = B, etc), and convert it to an ANSI
      * Character, like A, that we can use. 
      */
     return _getdrive() + 0x40;
}
