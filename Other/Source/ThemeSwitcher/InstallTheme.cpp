#include "Error.h"
#include "InstallTheme.h"
#include "GetSettings.h"

/* Global Variables */
PROCESS_INFORMATION SevenZipProcInfo;
DWORD SevenZipWaitReturn;
HWND InstallThemeProgressWindow;

void InstallTheme(string ThemePath) {
    /*InstallThemeProgressWindow = CreateWindow(
        "static",
        "Extracting Archive...",
        WS_VISIBLE | WS_POPUP, // Styles
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        150,
        20,
        HWND_DESKTOP,
        NULL,
        NULL,
        NULL);*/
    //Edit_SetText(EditWindow, ThemePath.c_str());
    if (ExtractTheme(ThemePath)) {
        /*Edit_SetText(EditWindow, "Adding theme to list...");
        /* Wait a maximum of 15 minutes for 7z to exit */
        _beginthread(WaitForSevenZipExit, 0, NULL);
        //DWORD SevenZipWaitReturn = WaitForSingleObject(SevenZipProcInfo.hProcess, 900000);
    }
    
}

void InstallThemeCMD(string ThemePath) {
    ExtractTheme(ThemePath);
}

bool ExtractTheme(string ThemePath) {
    if (ThemePath != "") {
        ostringstream CommandLine;
        CommandLine << "7z.exe x -o\"" << GetValue("ThemesDir").c_str();
        CommandLine << "\" -t\"zip\" \"" << ThemePath.c_str() << "\" *\0";
        
        /* Seven Zip Startup Structure */
        _STARTUPINFOA SZSS; 
        /* To (help) prevent unexplainable segfaults */
        ZeroMemory(&SZSS, sizeof(SZSS)); 
        SZSS.cb = sizeof(SZSS);
        SZSS.lpTitle = "Extracting Archive...";
        if (GetValue("Show Extracting Console") != "true") {
            SZSS.dwFlags = STARTF_USESHOWWINDOW;
            SZSS.wShowWindow = SW_HIDE;
        }
        //char* CommandLineCharP = const_cast<char*>(CommandLine.c_str()); // Converts the std::string into a char*
        
        LPTSTR CommandLineLp;
        CommandLineLp = const_cast<char*>(CommandLine.str().c_str());
        LPCTSTR SevenZipExeName = "7z.exe";
        if (!CreateProcess(
            SevenZipExeName,
            CommandLineLp,
            NULL,
            NULL,
            true,
            NORMAL_PRIORITY_CLASS,
            NULL,
            NULL,
            &SZSS,
            &SevenZipProcInfo)) {
                DWORD LastError = GetLastError();
                char ErrorMsgChar [1024];
                LPSTR ErrorMessage = ErrorMsgChar;
                FormatMessage(
                    FORMAT_MESSAGE_FROM_SYSTEM,
                    NULL,
                    LastError,
                    0,
                    ErrorMessage,
                    1024,
                    NULL);
                    string StrErrorMessage = ErrorMessage;
                    Error("Error occured while attempting to extract theme:\n"
                        + StrErrorMessage
                        + "\n"
                        + "Make sure 7z.exe and 7z.dll are in the same directory as\n"
                        + "This program.");
                    return 0;
        } else {
            return 1;
        }
    }
    return 0;
}

string PromptForThemeFile() {
    char CurrentWD [MAX_PATH];
    _getcwd(CurrentWD, MAX_PATH);
    CHAR FileName[512] = "";
    OPENFILENAME ThemeOpen;
    ZeroMemory(&ThemeOpen, sizeof(ThemeOpen));
    ThemeOpen.lStructSize = sizeof(ThemeOpen);
    ThemeOpen.lpstrTitle = "Select a Theme To install...";
    ThemeOpen.lpstrFilter = "Litestep Themes (*.lsz)\0*.lsz\0Zip Archives (*.zip)\0*.zip\0";
    ThemeOpen.nFilterIndex = 1;
    ThemeOpen.Flags = OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    ThemeOpen.lpstrFile = FileName;
    ThemeOpen.nMaxFile = sizeof(FileName);
    ThemeOpen.lpstrInitialDir = NULL;
    
    
    if (GetOpenFileName(&ThemeOpen)) {
        string FileNameStr = FileName;
        SetCurrentDirectory(CurrentWD);
        return FileNameStr;
    }
    DWORD LastError = CommDlgExtendedError();
    if (LastError != 0) {
        Error("Something went wrong while attemping to display the\n"
            "theme selection dialog. This is probobly bad. Error:\n"
            + GetErrorString(CommDlgExtendedError()));
    }
    return "";
}

/*void UpdateInfoLoop(void* nothing) {
    LPTSTR ConsoleText;
    DWORD MaxLength = 64000;
    COORD ConsoleStartPoint;
    ConsoleStartPoint.X = 0;
    ConsoleStartPoint.Y = 0;
    LPDWORD CharsRead;
    while (true) {
        ReadConsoleOutputCharacter(
            SevenZipConsoleHandle,
            ConsoleText,
            MaxLength,
            ConsoleStartPoint,
            CharsRead);
        //Error("Right before setting the text...");
        Edit_SetText(EditWindow, ConsoleText);
        Sleep(10);
    }
}*/

void WaitForSevenZipExit( void* Nothing ) {
    Status("Extracting theme...");
    WaitForSingleObject(SevenZipProcInfo.hProcess, 900000);
        if (SevenZipWaitReturn == WAIT_TIMEOUT) {
            Error("7z Did not exit within 15 minutes, the operation timed out.\n"
                "It is reccomended that you change the \"Show Extracting Console\"\n"
                "setting to \"true\" in order to view the console output\n"
                "(And possible errors).");
        } else if (SevenZipWaitReturn == WAIT_FAILED) {
            Error("Something when wrong while attempting to wait for 7z to exit\n"
                + GetErrorString(GetLastError()));
        } else {
            Status("Extraction successfull.");
            SendMessage(
                GlobalThemeMgrMainWindowHWND,
                0x8888,
                0,
                0);
            Status("Done!");
        }
        Sleep(1000);
        Status("Ready...");
        /*SetWindowLongPtr(
            InstallThemeProgressWindow,
            GWL_STYLE,
            WS_POPUP
            );*/
        //DestroyWindow(InstallThemeProgressWindow);
}
