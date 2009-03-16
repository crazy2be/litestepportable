#include "FindLitestep.h"
#include "Error.h"
#include "GetSettings.h"
#include "SettingsDialog.h"

void ValidatePaths() {
    string Returned;
    bool ErrorHappened;
    string FilesToFind[1];
    FilesToFind[0] = GetValue("Litestep");
	if (FindFile(FilesToFind, 1) == 1) {
        Returned = FindLiteStepExe();
        if (Returned != "ERROR_NOT_FOUND")
            SetValue("Litestep", Returned);
        else
            ErrorHappened = true;
	}
	FilesToFind[0] = GetValue("LitestepDir");
	FilesToFind[0] = FilesToFind[0].substr(0, (FilesToFind[0].length()-1));
	if (FindFile(FilesToFind, 1) == 1) {
        Returned = FindLiteStepExePath();
        if (Returned != "ERROR_NOT_FOUND")
            SetValue("LitestepDir", Returned);
        else
            ErrorHappened = true;
	}
	FilesToFind[0] = GetValue("ThemesDir");
	FilesToFind[0] = FilesToFind[0].substr(0, (FilesToFind[0].length()-1));
	if (FindFile(FilesToFind, 1) == 1) {
        Returned = FindThemesDirPath();
        if (Returned != "ERROR_NOT_FOUND")
            SetValue("ThemesDir", Returned);
        else
            ErrorHappened = true;
	}
	FilesToFind[0] = GetValue("ThemesDir");
	FilesToFind[0] += GetValue("DefaultTheme");
	FilesToFind[0] += "\\Theme.rc";
	if (FindFile(FilesToFind, 1) == 1) {
	    Error("Default Theme was not found!\n"
		    "Change this setting in Settings.ini before\n"
			"attempting to switch to another theme.");
	}
	if (ErrorHappened == true)
	    DisplaySettingsDialog();
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
    string FilesToFind[2];
    FilesToFind[0] = "..\\Litestep.exe";
    FilesToFind[1] = "Litestep.exe";
    int FindFileInt = FindFile(FilesToFind, 2);
    if (FindFileInt == 0) {
        _getcwd(Path, MAX_PATH);
        FilesToFind[0] = Path;
        FilesToFind[0] = FilesToFind[0].substr(0, FilesToFind[0].rfind("\\"));
        FilesToFind[0] += "\\";
        return FilesToFind[0];
    } else if (FindFileInt == 1) {
        _getcwd(Path, MAX_PATH);
        FilesToFind[1] = Path;
        FilesToFind[1] += "\\";
        return FilesToFind[1];
    } else {
        Error("Unable to find Litestep.exe!\n"
            "Please make sure it is in either:\n"
            " - ..\\LiteStep.exe\n"
            " - LiteStep.exe\n"
            "(all paths are relitive)");
        return "ERROR_NOT_FOUND";
    }
}

string FindThemesDirPath() {
    char Path [MAX_PATH];
    /* The array of places to search for ThemesList.rc */
    string FilesToFind[3];
    FilesToFind[0] = "..\\ThemesList.rc";
    FilesToFind[1] = "ThemesList.rc";
    FilesToFind[2] = "..\\Themes\\ThemesList.rc";
    int FindFileInt = FindFile(FilesToFind, 3);
    if (FindFileInt == 0) {
        _getcwd(Path, MAX_PATH);
        FilesToFind[0] = Path;
        FilesToFind[0] = FilesToFind[0].substr(0, FilesToFind[0].rfind("\\"));
        //FilesToFind[0] += "\\ThemesList.rc";
        return FilesToFind[0];
    } else if (FindFileInt == 1) {
        _getcwd(Path, MAX_PATH);
        FilesToFind[1] = Path;
        //FilesToFind[1] += "\\ThemesList.rc";
        return FilesToFind[1];
    } else if (FindFileInt == 2) {
        _getcwd(Path, MAX_PATH);
        FilesToFind[2] = Path;
        FilesToFind[2] = FilesToFind[2].substr(0, FilesToFind[2].rfind("\\"));
        FilesToFind[2] += "\\Themes\\";
        return FilesToFind[2];
    } else {
        Error("Unable to find ThemesList.rc!\n"
            "Please make sure it is in either:\n"
            " - ..\\ThemeList.rc\n"
            " - ThemeList.rc\n"
            " - ..\\Themes\\ThemeList.rc\n"
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
