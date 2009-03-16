#include "main.h"
#include "GetSettings.h"
#include "ArgProc.h"
#include "SwitchTheme.h"
#include "Error.h"
#include "InstallTheme.h"
#include "RefreshThemes.h"
#include "FindLitestep.h"
#include "GlobalVars.h"
#include "SettingsDialog.h"

HWND GlobalThemeMgrMainWindowHWND;
HINSTANCE GlobalhThisInstance;
HWND GlobalStatushwnd;

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)

{
    ValidatePaths();         /* Makes sure that all paths are valid before doing anything */
    string Args = lpszArgument;
    ArgProcessing(Args); //Does the arg processing before creating the window
    //HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */
    WNDCLASSEX ButtonWindow;   /* For the window with all the buttons at the bottom */
    char ButtonWindowClassName[ ] = "ButtonSubWindow";
    GlobalhThisInstance = hThisInstance;

    /* The Window structure */
    ButtonWindow.hInstance = hThisInstance;
    ButtonWindow.lpszClassName = ButtonWindowClassName;
    ButtonWindow.lpfnWndProc = ButtonWindowProcedure;      /* This function is called by windows */
    ButtonWindow.style = CS_DBLCLKS;                 /* Catch double-clicks */
    ButtonWindow.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    ButtonWindow.hIcon = LoadIcon (hThisInstance, "APPLICATION_ICON");
    ButtonWindow.hIconSm = LoadIcon (hThisInstance, "APPLICATION_ICON");
    ButtonWindow.hCursor = LoadCursor (NULL, IDC_ARROW);
    ButtonWindow.lpszMenuName = NULL;                 /* No menu */
    ButtonWindow.cbClsExtra = 0;                      /* No extra bytes after the window class */
    ButtonWindow.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    ButtonWindow.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&ButtonWindow))
        return 0;
        
    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (hThisInstance, "APPLICATION_ICON");
    wincl.hIconSm = LoadIcon (hThisInstance, "APPLICATION_ICON");
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    GlobalThemeMgrMainWindowHWND = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "Theme Manager",     /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           210,                 /* The programs width */
           275,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );
    
    ThemeListhwnd = CreateWindow(
        "ListBox",
        "bahtest.",
        WS_VISIBLE | WS_CHILD | WS_VSCROLL |
        LBS_HASSTRINGS | LBS_NOTIFY |
        LBS_NOINTEGRALHEIGHT,
        1,
        1,
        200,
        180,
        GlobalThemeMgrMainWindowHWND,
        (HMENU)0,
        hThisInstance,
        NULL);
    
    BottomButtonshwnd = CreateWindow(
        ButtonWindowClassName,
        "er",
        WS_VISIBLE | WS_CHILD,
        1,
        178,
        203,
        70,
        GlobalThemeMgrMainWindowHWND,
        NULL,
        hThisInstance,
        NULL);
    
    GlobalStatushwnd = CreateWindow(
        "edit",
        "Ready",
        WS_VISIBLE | WS_CHILD | WS_BORDER |
        ES_READONLY,
        1,
        1,
        201,
        16,
        BottomButtonshwnd,
        NULL,
        hThisInstance,
        NULL);
        
    InstallThemehwnd = CreateWindow(
        "Button",
        "Install Theme",
        WS_VISIBLE | WS_CHILD,
        1,
        18,
        100,
        25,
        BottomButtonshwnd,
        (HMENU)20,
        hThisInstance,
        NULL);
             
    SwitchThemehwnd = CreateWindow(
        "Button",
        "Switch Theme",
        WS_VISIBLE | WS_CHILD,
        102,
        18,
        100,
        25,
        BottomButtonshwnd,
        (HMENU)21,
        hThisInstance,
        NULL);

    Settingshwnd = CreateWindow(
        "Button",
        "Settings",
        WS_VISIBLE | WS_CHILD,
        1,
        44,
        100,
        25,
        BottomButtonshwnd,
        (HMENU)30,
        hThisInstance,
        NULL);
        
    RefreshThemeListhwnd = CreateWindow(
        "Button",
        "Refresh List",
        WS_VISIBLE | WS_CHILD,
        102,
        44,
        100,
        25,
        BottomButtonshwnd,
        (HMENU)31,
        hThisInstance,
        NULL);
        
    /* Make the window visible on the screen */
    ShowWindow (GlobalThemeMgrMainWindowHWND, nFunsterStil);
    
    /* Populate the ListBox with the themes */
    GetInstalledThemes();
    
    /* For Testing... */
    //InstallTheme("G:\\Litestep\\Personal\\Desktop\\TEST.zip");
    
    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }
    

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    ostringstream XYCoords;
    switch (message)                  /* handle the messages */
    {
        case WM_DESTROY:
             PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
             break;
        case WM_COMMAND:
             //MessageBox(NULL, "DSDA", "SDADKSJ", MB_OK);
             switch (LOWORD(wParam)) {
                 XYCoords << LOWORD(wParam);
                 XYCoords << " ";
                 XYCoords << HIWORD(wParam);
                 XYCoords << "\n";
                 XYCoords << wParam;
                 Info(XYCoords.str());
                 //MessageBox(NULL, "JFKDH", "JEIOJSDOISJ", MB_OK);
                 case 0: //It was the listbox
                     switch (HIWORD(wParam)) {
                         case LBN_SELCHANGE:
                             // Maybe load some theme info here
                             //MessageBox(NULL, "WHAR", "HSJDHS", MB_OK);
                             //return true;
                             break;
                         case LBN_DBLCLK:
                             //MessageBox(NULL, "WHAR", "HSJDHS", MB_OK);
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
                             return true;
                             break;
                     }
                     break;
             }
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
                 Status(XYCoords.str());
                 SetWindowPos(ThemeListhwnd, 
                     HWND_BOTTOM,
                     0,
                     0,
                     WindowW,
                     WindowH-60,
                     SWP_NOACTIVATE);
                 SetWindowPos(BottomButtonshwnd,
                     HWND_BOTTOM,
                     1,
                     WindowH-59,
                     WindowW-2,
                     62,
                     SWP_NOACTIVATE);

             }
             break;
        case 0x8888: //0x8888 = custom message that refreshes the theme list
             RefreshList(ThemeListhwnd, ThemeNames);
             break;
        //case WM_GETICON:
            //return 
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

LRESULT CALLBACK ButtonWindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case 20: // The "install theme" button
                    switch (HIWORD(wParam)) {
                        case BN_CLICKED:
                            string InstallThemeString;// = "G:\\LiteStep\\Personal\\Desktop\\TEST.zip";
                            //InstallTheme(InstallThemeString);
                            InstallThemeString = PromptForThemeFile();
                            InstallTheme(InstallThemeString);
                            break;
                    }
                    break;
                case 21: // Then "Switch theme" button
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
                    break;
             case 30: // The "Settings" button
                 switch(HIWORD(wParam)) {
                     case BN_CLICKED:
                         DisplaySettingsDialog();
                         break;
                 }
                 break;
             case 31: // The "Refresh list" button
                 switch (HIWORD(wParam)) {
                     case BN_CLICKED:
                         RefreshList(ThemeListhwnd, ThemeNames);
                         break;
                 }
                 break;
             }
             break;
        case WM_SIZE:
            if (wParam == SIZE_RESTORED || wParam == SIZE_MAXIMIZED) {
                 int WindowW = LOWORD(lParam);
                 int WindowH = HIWORD(lParam);
                 SetWindowPos(GlobalStatushwnd,
                     HWND_BOTTOM,
                     0,
                     0,
                     WindowW,
                     16,
                     SWP_NOACTIVATE);
                 SetWindowPos(InstallThemehwnd,
                     HWND_BOTTOM,
                     0,
                     17,
                     (WindowW/2)-1,
                     20,
                     SWP_NOACTIVATE);
                 SetWindowPos(SwitchThemehwnd,
                     HWND_BOTTOM,
                     (WindowW/2),
                     17,
                     (WindowW/2),
                     20,
                     SWP_NOACTIVATE);
                 SetWindowPos(Settingshwnd,
                     HWND_BOTTOM,
                     0,
                     38,
                     (WindowW/2)-1,
                     20,
                     SWP_NOACTIVATE);
                 SetWindowPos(RefreshThemeListhwnd,
                     HWND_BOTTOM,
                     (WindowW/2),
                     38,
                     (WindowW/2),
                     20,
                     SWP_NOACTIVATE);
            }
            break;

        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
}

void GetInstalledThemes() {
    string line;
    string curtheme;
    int firstquote;
    int secondquote;
    int ThemeNumber;
    try {
        ifstream SetRead ((GetValue("ThemesDir") + "Themeslist.rc").c_str());
        if (SetRead.is_open()) {
            while (! SetRead.eof()) {
                getline (SetRead, line);
                if (line[0] == ';') {
                    
                } else {
                    try {
                    //ThemeNumber++;
                    firstquote = line.find('"'); //finds the first quote
                    secondquote =
                        ((line.substr((firstquote+1), line.length()))
                        .find('"') + (firstquote-6)); // ugly, but finds the second quote
                    curtheme = line.substr((firstquote+1), (secondquote-1)); //gets the theme name
                    ThemeNames[
                        SendMessage(
                            ThemeListhwnd,
                            LB_ADDSTRING,
                            0,
                            (LPARAM) curtheme.c_str())
                        ] = curtheme;
                    } catch (...) {}
                }
           }
        }
        SetRead.close();
        } catch (...) {
        }
}




