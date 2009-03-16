#include "RefreshThemes.h"
#include "Error.h"
#include "GetSettings.h"

void RefreshList(HWND ThemeListHWND, string ThemeNames[]) {
    Status("Loading themes...");
    /* Clear Current List & File */
    ClearThemeList(ThemeListHWND, ThemeNames);
    ClearThemeListFile();
    /* Define Variables */
    WIN32_FIND_DATA CurFileData;
    LPCTSTR ThemesDir;
    HANDLE FindFileHandle;
    string FileName;
    bool FindNextReturn = true;
    ThemesDir = (GetValue("ThemesDir") + "*").c_str();
    FindFileHandle = FindFirstFile(ThemesDir, &CurFileData);
    /* Process each file in the themes direcory, 
       add the directories to the list */
    while (FindNextReturn) {
        if (CurFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
            FileName = CurFileData.cFileName;
            if (FileName != "." && FileName != "..") {
                AddThemeToThemeListFile(FileName);
                AddThemeToThemeList(FileName, ThemeListHWND, ThemeNames);
            }
        }
        FindNextReturn = FindNextFile(FindFileHandle, &CurFileData);
    }
}

/* Same as above, but used if invoked from the command-line */
void RefreshListCMD() {
    /* Clear Current File */
    ClearThemeListFile();
    /* Define Variables */
    WIN32_FIND_DATA CurFileData;
    LPCTSTR ThemesDir;
    HANDLE FindFileHandle;
    string FileName;
    bool FindNextReturn = true;
    ThemesDir = (GetValue("ThemesDir") + "*").c_str();
    FindFileHandle = FindFirstFile(ThemesDir, &CurFileData);
    /* Process each file in the themes direcory, 
       add the directories to the list */
    while (FindNextReturn) {
        if (CurFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
            FileName = CurFileData.cFileName;
            if (FileName != "." && FileName != "..") {
                AddThemeToThemeListFile(FileName);
            }
        }
        FindNextReturn = FindNextFile(FindFileHandle, &CurFileData);
    }
}
/* Adds a theme to the visual theme list */
void AddThemeToThemeList(string ThemeName, HWND ThemeListHWND, string ThemeNames[]) {
    ThemeNames[
        SendMessage(
            ThemeListHWND,
            LB_ADDSTRING,
            0,
            (LPARAM) ThemeName.c_str())
        ] = ThemeName;
}

/* Clears the visual theme list */
void ClearThemeList(HWND ThemeListHWND, string ThemeNames[]) {
    SendMessage(
        ThemeListHWND,
        LB_RESETCONTENT,
        0,
        0);
    for (int i=0; i < 50; i++) {
        ThemeNames[i].clear();
    }
}

/* Adds a theme to themelist.rc */
void AddThemeToThemeListFile(string ThemeName) {
    try {
        ofstream AddTheme ((GetValue("ThemesDir") + "Themeslist.rc").c_str(), ios::app);
        if (AddTheme.is_open()) {
            AddTheme << "*Popup \"" << ThemeName 
                << "\" !Execute [\"LitestepDir$utilities\\ThemeSwitcher.exe\" /switch \"" 
                << ThemeName << "\"]\n";
        } else {
            Error("An error accured trying to access Themeslist.rc.\nPlease check your configuration.");
        }
        AddTheme.close();
    } catch (...) {
        Error("An error accured trying to access Themeslist.rc.\nPlease check your configuration.");
    }
}

/* Clears everything in themelist.rc */
void ClearThemeListFile() {
    try {
        ofstream AddTheme ((GetValue("ThemesDir") + "Themeslist.rc").c_str(), ios::trunc);
        if (AddTheme.is_open()) {
            AddTheme 
                << ";------------------------------------------------------------------------------\n"
                << "; Here is a list of all the currently installed themes,\n"
                << "; As they are shown in the popup.\n"
                << ";------------------------------------------------------------------------------\n";
        } else {
            Error("An error accured trying to access Themeslist.rc.\nPlease check your configuration.");
        }
        AddTheme.close();
    } catch (...) {
        Error("An error accured trying to access Themeslist.rc.\nPlease check your configuration.");
    }
}
