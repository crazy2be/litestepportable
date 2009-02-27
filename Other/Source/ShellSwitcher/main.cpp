#include "main.h"
#include "Switcher.h"
#include "Error.h"
#include "GetSettings.h"
#include "ProcessExist.h"
#include "GlobalVars.h"
#include "UpdateIcons.h"
#include "FindLitestep.h"
#include "ArgProc.h"

int main(int argc, char *argv[])
{
    
    //exit( EXIT_SUCCESS );
    // Set Global Variables
	string WD;
	WD = argv[0];
	WD = WD.substr(0, WD.rfind("\\"));
	SetCurrentDirectory(WD.c_str());
    ValidatePaths();
    string ArgsStr;
    for (int i=1; i<argc; i++) {
        ArgsStr += argv[i];
    }
    ArgProcessing(ArgsStr);
    globalExplorerPID = ProcessRunning("explorer.exe");
    globalLitestepPID = ProcessRunning("litestep.exe");
    globalExplorerIsRunning = globalExplorerPID > 0;
    globalLitestepIsRunning = globalLitestepPID > 0;
    // Check what the PromptLevel is set to and make sure it is valid
    int PromptLevel = GetIntValue("PromptLevel");
    if (PromptLevel > 0 && PromptLevel < 4) {
        //UpdateIcons();
        PromptAction();
    } else {
        Warning("\"PromptLevel\" is set to an invalid setting!\nDefaulting to allways prompting ( setting 2 )\nDefine it in Settings.ini, \"PromptLevel=[1-3]\"");
        SetIntValue("PromptLevel",3);
        //UpdateIcons();
        PromptAction();
    }
    return EXIT_SUCCESS;
}


