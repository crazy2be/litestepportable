#include "SettingsDialog.h"
#include "GlobalVars.h"
#include "GetSettings.h"
#include "Error.h"

/* Global Variables */
HWND ThemesDirStaticHWND;
HWND ThemesDirTextBoxHWND;
HWND ThemesDirButtonHWND;

void DisplaySettingsDialog() {
    // Until i have time to make a settings dialog...
    ShellExecute(NULL, "open", "Settings.ini", NULL, NULL, SW_SHOWNORMAL);
    /***************************************************************************
     * The below code is the start of a settings dialog. if you want to finish *
     * it, go ahead ;).                                                        *
     ***************************************************************************/
    /*HWND hwnd;               /* This is the handle for our window */
    /*MSG messages;            /* Here messages to the application are saved */
    /*WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    /*wincl.hInstance = GlobalhThisInstance;
    wincl.lpszClassName = "SettingsDialog";
    wincl.lpfnWndProc = SettingsWindowProcedure;      /* This function is called by windows */
    /*wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    /*wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    /*wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    /*wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    /*wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    /*wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    /*if (!RegisterClassEx (&wincl))
        return;

    /* The class is registered, let's create the program*/
    /*hwnd = CreateWindowEx (
    /*       0,                   /* Extended possibilites for variation */
    /*       "SettingsDialog",         /* Classname */
    /*       "Settings...",       /* Title Text */
    /*       WS_OVERLAPPEDWINDOW, /* default window */
    /*       CW_USEDEFAULT,       /* Windows decides the position */
    /*       CW_USEDEFAULT,       /* where the window ends up on the screen */
    /*       230,                 /* The programs width */
    /*       275,                 /* and height in pixels */
    /*       HWND_DESKTOP,        /* The window is a child-window to desktop */
    /*       NULL,                /* No menu */
    /*       GlobalhThisInstance, /* Program Instance handler */
    /*       NULL                 /* No Window Creation data */
    /*       );
    
    ThemesDirStaticHWND = CreateWindow(
        "static",
        "ThemesDir Path (MUST end in a \\)",
        WS_VISIBLE | WS_CHILD,
        1,
        1,
        200,
        15,
        hwnd,
        NULL,
        GlobalhThisInstance,
        NULL);
    
    ThemesDirTextBoxHWND = CreateWindow(
        "edit",
        GetValue("ThemesDir").c_str(),
        WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
        1,
        16,
        200,
        20,
        hwnd,
        NULL,
        GlobalhThisInstance,
        NULL);
    
    ThemesDirButtonHWND = CreateWindow(
        "Button",
        "...",
        WS_VISIBLE | WS_CHILD,
        202,
        1,
        19,
        20,
        hwnd,
        NULL,
        GlobalhThisInstance,
        NULL);
             
    /*SwitchThemehwnd = CreateWindow(
        "Button",
        "Switch Theme",
        WS_VISIBLE | WS_CHILD,
        102,
        195,
        100,
        25,
        ThemeMgrMainWindowHWND,
        NULL,
        hThisInstance,
        NULL);
    
    RefreshThemeListhwnd = CreateWindow(
        "Button",
        "Refresh List",
        WS_VISIBLE | WS_CHILD,
        102,
        221,
        100,
        25,
        ThemeMgrMainWindowHWND,
        NULL,
        hThisInstance,
        NULL);
        
    FindLitestephwnd = CreateWindow(
        "Button",
        "Find Litestep!",
        WS_VISIBLE | WS_CHILD,
        1,
        221,
        100,
        25,
        ThemeMgrMainWindowHWND,
        NULL,
        hThisInstance,
        NULL);*/
        
    /* Make the window visible on the screen */
    /*ShowWindow (hwnd, SW_SHOW);
    
    /* Run the message loop. It will run until GetMessage() returns 0 */
    /*while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        /*TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        /*DispatchMessage(&messages);
    }*/
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK SettingsWindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    ostringstream XYCoords;
    switch (message)                  /* handle the messages */
    {
        case WM_DESTROY:
             PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
             break;
        case WM_COMMAND:
             //MessageBox(NULL, "DSDA", "SDADKSJ", MB_OK);
             /*if ((HWND)lParam == ThemeListhwnd) {
                 //MessageBox(NULL, "JFKDH", "JEIOJSDOISJ", MB_OK);
                 switch (LOWORD(wParam)) {
                     case LBN_SELCHANGE:
                         MessageBox(NULL, "WHAR", "HSJDHS", MB_OK);
                         return true;
                     case LBN_DBLCLK:
                         //SwitchTheme();
                         return true;
                     default:
                         return false;
                 }
                 if (HIWORD(wParam) == LBN_SELCHANGE) {
                     MessageBox(NULL, "WHAR", (CHAR*)wParam, MB_OK);
                 }
             } else if ((HWND)lParam == InstallThemehwnd) {
                 switch (HIWORD(wParam)) {
                     case BN_CLICKED:
                         string InstallThemeString;// = "G:\\LiteStep\\Personal\\Desktop\\TEST.zip";
                         //InstallTheme(InstallThemeString);
                         InstallThemeString = PromptForThemeFile();
                         InstallTheme(InstallThemeString);
                         break;
                 }
             } else if ((HWND)lParam == SwitchThemehwnd) {
                 switch (HIWORD(wParam)) {
                     case BN_CLICKED:
                         LRESULT Selidx;
                         Selidx =
                             SendMessage(
                             ThemeListhwnd,
                             LB_GETCURSEL,
                             0,
                             0);
                         if (Selidx != LB_ERR) {
                             SwitchTheme(ThemeNames[Selidx], true);
                         }
                         break;
                 }
             } else if ((HWND)lParam == RefreshThemeListhwnd) {
                 switch (HIWORD(wParam)) {
                     case BN_CLICKED:
                         RefreshList(ThemeListhwnd, ThemeNames);
                         break;
                 }
             } else if ((HWND)lParam == FindLitestephwnd) {
                 switch(HIWORD(wParam)) {
                     case BN_CLICKED:
                         Info(FindLiteStepExe());
                         SetValue("WHAT", "LOL");
                         break;
                 }
             }*/
             break;
        case WM_SIZE:
             if (wParam == SIZE_RESTORED || wParam == SIZE_MAXIMIZED) {
                 int WindowW = LOWORD(lParam);
                 int WindowH = HIWORD(lParam);
                 XYCoords << WindowW;
                 //Info("wParam " + XYCoords.str());
                 XYCoords << " ";
                 XYCoords << WindowH;
                 //Info("lParam " + XYCoords.str());
                 Edit_SetText(ThemesDirStaticHWND, XYCoords.str().c_str());
             }
             break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
