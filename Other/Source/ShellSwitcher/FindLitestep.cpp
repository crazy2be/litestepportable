#include "FindLitestep.h"
#include "Error.h"
#include "GetSettings.h"
//#include "SettingsDialog.h"

void ValidatePaths() {
    string Returned;
    bool ErrorHappened;
    string FilesToFind[1];
    FilesToFind[0] = "Data\\Settings.ini";
    if (FindFile(FilesToFind, 1) == 1) {
        CreateSettingsini();
    }
    FilesToFind[0] = GetValue("Litestep");
	if (FindFile(FilesToFind, 1) == 1) {
        Returned = FindLiteStepExe();
        if (Returned != "ERROR_NOT_FOUND")
            SetValue("Litestep", Returned);
        else
            ErrorHappened = true;
	}
	if (GetBoolValue("DetectPortableApps")) {
	    FilesToFind[0] = GetValue("DesktopFolderPath");
	    FilesToFind[0] = FilesToFind[0].substr(0, (FilesToFind[0].length()-1));
	        if (FindFile(FilesToFind, 1) == 1) {
            Returned = FindDesktopPath();
            if (Returned != "ERROR_NOT_FOUND")
                SetValue("DesktopFolderPath", Returned);
            else
                ErrorHappened = true;
	    }
	    FilesToFind[0] = GetValue("PortableAppsDir");
	    FilesToFind[0] = FilesToFind[0].substr(0, (FilesToFind[0].length()-1));
	    if (FindFile(FilesToFind, 1) == 1) {
            Returned = FindPortableAppsDirPath();
            if (Returned != "ERROR_NOT_FOUND")
                SetValue("PortableAppsDir", Returned);
            else
                ErrorHappened = true;
	    }
	    FilesToFind[0] = GetValue("PortableApps popup file");
	    //FilesToFind[0] += GetValue("DefaultTheme");
	    if (FindFile(FilesToFind, 1) == 1) {
            Returned = FindPortableAppsPopupFilePath();
            if (Returned != "ERROR_NOT_FOUND")
                SetValue("PortableApps popup file", Returned);
            else
                ErrorHappened = true;
	    }
	    FilesToFind[0] = GetValue("PortableApps LSX File");
	    if (FindFile(FilesToFind, 1) == 1) {
            Returned = FindPortableAppsLSXFilePath();
            if (Returned != "ERROR_NOT_FOUND")
                SetValue("PortableApps LSX file", Returned);
            else
                ErrorHappened = true;
        }
    }
	//if (ErrorHappened == true)
	    //DisplaySettingsDialog();
    //int FileFindInt = FindFile(FilesToFind
}

string FindLiteStepExe() {
    string LiteStepExe;
    LiteStepExe = FindLiteStepExePath();
    if (LiteStepExe == "ERROR_NOT_FOUND") {
        return LiteStepExe;
    } else {
        LiteStepExe += "Litestep.exe";
        return LiteStepExe;
    }
}

string FindLiteStepExePath() {
    char Path [MAX_PATH];
    /* The array of places to search for Litestep */
    string FilesToFind[3];
    FilesToFind[0] = "App\\Litestep\\Litestep.exe";
    FilesToFind[1] = "..\\Litestep.exe";
    FilesToFind[2] = "Litestep.exe";
    int FindFileInt = FindFile(FilesToFind, 3);
    if (FindFileInt == 0) {
        _getcwd(Path, MAX_PATH);
        FilesToFind[0] = Path;
        FilesToFind[0] += "\\App\\Litestep\\";
        return FilesToFind[0];
    } else if (FindFileInt == 1) {
        _getcwd(Path, MAX_PATH);
        FilesToFind[1] = Path;
        FilesToFind[1] = FilesToFind[0].substr(0, FilesToFind[0].rfind("\\"));
        FilesToFind[1] += "\\";
        return FilesToFind[1];
    } else if (FindFileInt == 2) {
        _getcwd(Path, MAX_PATH);
        FilesToFind[2] = Path;
        FilesToFind[2] += "\\";
        return FilesToFind[2];
    } else {
        Error("Unable to find Litestep.exe!\n"
            "Please make sure it is in either:\n"
            + FilesToFind[0] + "\n"
            + FilesToFind[1] + "\n"
            + FilesToFind[2] + "\n"
            "(all paths are relitive)");
        return "ERROR_NOT_FOUND";
    }
}

string FindPortableAppsDirPath() {
    char Path [MAX_PATH];
    /* The array of places to search for the portableapps folder */
    string FilesToFind[3];
    FilesToFind[0] = "..\\..\\PortableApps";
    FilesToFind[1] = "..\\PortableApps";
    FilesToFind[2] = "..\\..\\..\\PortableApps";
    int FindFileInt = FindFile(FilesToFind, 3);
    if (FindFileInt == 0) {
        _getcwd(Path, MAX_PATH);
        FilesToFind[0] = Path;
        FilesToFind[0] = FilesToFind[0].substr(0, FilesToFind[0].rfind("\\"));
        FilesToFind[0] = FilesToFind[0].substr(0, FilesToFind[0].rfind("\\"));
        FilesToFind[0] += "\\PortableApps";
        return FilesToFind[0];
    } else if (FindFileInt == 1) {
        _getcwd(Path, MAX_PATH);
        FilesToFind[1] = Path;
        FilesToFind[1] = FilesToFind[0].substr(0, FilesToFind[0].rfind("\\"));
        FilesToFind[1] += "\\PortableApps";
        return FilesToFind[1];
    } else if (FindFileInt == 2) {
        _getcwd(Path, MAX_PATH);
        FilesToFind[2] = Path;
        FilesToFind[2] = FilesToFind[2].substr(0, FilesToFind[2].rfind("\\"));
        FilesToFind[2] = FilesToFind[2].substr(0, FilesToFind[2].rfind("\\"));
        FilesToFind[2] = FilesToFind[2].substr(0, FilesToFind[2].rfind("\\"));
        FilesToFind[2] += "\\PortableApps";
        return FilesToFind[2];
    } else {
        Error("Unable to find The Portableapps directory!\n"
            "Please make sure it is in either:\n"
            + FilesToFind[0] + "\n"
            + FilesToFind[1] + "\n"
            + FilesToFind[2] + "\n"
            "(all paths are relitive)");
        return "ERROR_NOT_FOUND";
    }
}

string FindDesktopPath() {
    char Path [MAX_PATH];
    /* The array of places to search for the portableapps folder */
    string FilesToFind[3];
    FilesToFind[0] = "..\\Desktop";
    FilesToFind[1] = "App\\Litestep\\Personal\\Desktop";
    FilesToFind[2] = "App\\Litestep\\Desktop";
    int FindFileInt = FindFile(FilesToFind, 3);
    if (FindFileInt == 0) {
        _getcwd(Path, MAX_PATH);
        FilesToFind[0] = Path;
        FilesToFind[0] = FilesToFind[0].substr(0, FilesToFind[0].rfind("\\"));
        //FilesToFind[0] = FilesToFind[0].substr(0, FilesToFind[0].rfind("\\"));
        FilesToFind[0] += "\\Desktop\\";
        return FilesToFind[0];
    } else if (FindFileInt == 1) {
        _getcwd(Path, MAX_PATH);
        FilesToFind[1] = Path;
        //FilesToFind[1] = FilesToFind[0].substr(0, FilesToFind[0].rfind("\\"));
        FilesToFind[1] += "\\App\\Litestep\\Personal\\Desktop\\";
        return FilesToFind[1];
    } else if (FindFileInt == 2) {
        _getcwd(Path, MAX_PATH);
        FilesToFind[2] = Path;
        //FilesToFind[2] = FilesToFind[2].substr(0, FilesToFind[2].rfind("\\"));
        //FilesToFind[2] = FilesToFind[2].substr(0, FilesToFind[2].rfind("\\"));
        //FilesToFind[2] = FilesToFind[2].substr(0, FilesToFind[2].rfind("\\"));
        FilesToFind[2] += "\\App\\Litestep\\Desktop\\";
        return FilesToFind[2];
    } else {
        Error("Unable to find The Desktop directory!\n"
            "Please make sure it is in either:\n"
            + FilesToFind[0] + "\n"
            + FilesToFind[1] + "\n"
            + FilesToFind[2] + "\n"
            "(all paths are relitive)");
        return "ERROR_NOT_FOUND";
    }
}

string FindPortableAppsPopupFilePath() {
    char Path [MAX_PATH];
    /* The array of places to search for the portableapps folder */
    string FilesToFind[3];
    FilesToFind[0] = "..\\Personal\\PortableApps.rc";
    FilesToFind[1] = "App\\Litestep\\Personal\\PortableApps.rc";
    FilesToFind[2] = "Personal\\PortableApps.rc";
    int FindFileInt = FindFile(FilesToFind, 3);
    if (FindFileInt == 0) {
        _getcwd(Path, MAX_PATH);
        FilesToFind[0] = Path;
        FilesToFind[0] = FilesToFind[0].substr(0, FilesToFind[0].rfind("\\"));
        //FilesToFind[0] = FilesToFind[0].substr(0, FilesToFind[0].rfind("\\"));
        FilesToFind[0] += "\\Personal\\PortableApps.rc";
        return FilesToFind[0];
    } else if (FindFileInt == 1) {
        _getcwd(Path, MAX_PATH);
        FilesToFind[1] = Path;
        //FilesToFind[1] = FilesToFind[0].substr(0, FilesToFind[0].rfind("\\"));
        FilesToFind[1] += "\\App\\Litestep\\Personal\\PortableApps.rc";
        return FilesToFind[1];
    } else if (FindFileInt == 2) {
        _getcwd(Path, MAX_PATH);
        FilesToFind[2] = Path;
        //FilesToFind[2] = FilesToFind[2].substr(0, FilesToFind[2].rfind("\\"));
        //FilesToFind[2] = FilesToFind[2].substr(0, FilesToFind[2].rfind("\\"));
        //FilesToFind[2] = FilesToFind[2].substr(0, FilesToFind[2].rfind("\\"));
        FilesToFind[2] += "\\Personal\\PortableApps.rc";
        return FilesToFind[2];
    } else {
        Error("Unable to find The Portableapps.rc file!\n"
            "Please make sure it is in either:\n"
            + FilesToFind[0] + "\n"
            + FilesToFind[1] + "\n"
            + FilesToFind[2] + "\n"
            "(all paths are relitive)");
        return "ERROR_NOT_FOUND";
    }
}

string FindPortableAppsLSXFilePath() {
    char Path [MAX_PATH];
    /* The array of places to search for the portableapps folder */
    string FilesToFind[3];
    FilesToFind[0] = "..\\Personal\\LSXCommand\\PortableApps.rc";
    FilesToFind[1] = "App\\Litestep\\Personal\\LSXCommand\\PortableApps.rc";
    FilesToFind[2] = "Personal\\LSXCommand\\PortableApps.rc";
    int FindFileInt = FindFile(FilesToFind, 3);
    if (FindFileInt == 0) {
        _getcwd(Path, MAX_PATH);
        FilesToFind[0] = Path;
        FilesToFind[0] = FilesToFind[0].substr(0, FilesToFind[0].rfind("\\"));
        //FilesToFind[0] = FilesToFind[0].substr(0, FilesToFind[0].rfind("\\"));
        FilesToFind[0] += "\\Personal\\LSXCommand\\PortableApps.rc";
        return FilesToFind[0];
    } else if (FindFileInt == 1) {
        _getcwd(Path, MAX_PATH);
        FilesToFind[1] = Path;
        //FilesToFind[1] = FilesToFind[0].substr(0, FilesToFind[0].rfind("\\"));
        FilesToFind[1] += "\\App\\Litestep\\Personal\\LSXCommand\\PortableApps.rc";
        return FilesToFind[1];
    } else if (FindFileInt == 2) {
        _getcwd(Path, MAX_PATH);
        FilesToFind[2] = Path;
        //FilesToFind[2] = FilesToFind[2].substr(0, FilesToFind[2].rfind("\\"));
        //FilesToFind[2] = FilesToFind[2].substr(0, FilesToFind[2].rfind("\\"));
        //FilesToFind[2] = FilesToFind[2].substr(0, FilesToFind[2].rfind("\\"));
        FilesToFind[2] += "\\Personal\\LSXCommand\\PortableApps.rc";
        return FilesToFind[2];
    } else {
        Error("Unable to find The Portableapps.rc file!\n"
            "Please make sure it is in either:\n"
            + FilesToFind[0] + "\n"
            + FilesToFind[1] + "\n"
            + FilesToFind[2] + "\n"
            "(all paths are relitive)");
        return "ERROR_NOT_FOUND";
    }
}

int FindFile(string FilesToFind[], unsigned int Length) {
    /* Define Variables */
    WIN32_FIND_DATA CurFileData;
    HANDLE FindFileHandle;
    /* Searches for the file in each of the specified search paths */
    for (int i = 0; i < Length; i++) {
        FindFileHandle = FindFirstFile(FilesToFind[i].c_str(), &CurFileData);
        if (FindFileHandle == INVALID_HANDLE_VALUE) {
        } else {
            // Returns the number that matched
            return i;
        }
    }
    return Length;
}

void CreateSettingsini() {
    string ToWrite =
    "; Set \"PromptLevel\" to:\n"
    "; 1 for no prompts\n"
    "; 2 for selective prompts\n"
    "; 3 for all prompts\n"
    ";  (in the form of \"PromptLevel=#\")\n"
    "PromptLevel=3\n"
    "; The portableapps directory\n"
    "PortableAppsDir=G:\\PortableApps\\\n"
    "; the path to the popup file to write the portableapps info to\n"
    "PortableApps popup file=G:\\LiteStep\\Personal\\PortableApps.rc\n"
    "; The path to the lsxcommand alias file\n"
    "PortableApps LSX file=G:\\LiteStep\\Personal\\LSXCommand\\PortableApps.rc\n"
    "; The path to the desktop folder\n"
    "DesktopFolderPath=G:\\Litestep\\Personal\\Desktop\\\n"
    "; Should the app create desktop shortcuts on each load?\n"
    "; this insures that your portableapps are allways up to date,\n"
    "; but it will make the loading time significantly longer.\n"
    "; (it will still update the popup list, just not the desktop)\n"
    "CreateDesktopShortcuts=true\n"
    "; The path to litestep.exe\n"
    "Litestep=G:\\Litestep\\Litestep.exe\n"
    "; Detect installed portable apps? set to false if you don't use Portableapps\n"
    "DetectPortableApps=true\n"
    "; Forcibly termiate litestep? Set to true if you are experiencing\n"
    "; troubles with litestep closing properly.\n"
    "Force Litestep Termination=false\n";
    try {
        ofstream iniWrite ("Data\\Settings.ini");
        if (iniWrite.is_open()) {
            iniWrite << ToWrite;
        } else {
            Error("Unable to create Data\\Settings.ini!");
        }
        iniWrite.close();
    } catch (...) {
        Error("Unexpected error occured while trying to create Data\\Settings.ini");
    }
}
