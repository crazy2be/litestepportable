// SPLASH.cpp: implementation of the SPLASH class.
//
//////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "SPLASH.h"
#include "Error.h"
//#include <sstream>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SPLASH::SPLASH()
{

}

SPLASH::~SPLASH()
{
 DestroyWindow(hSplashWnd);
}

void SPLASH::Init()
{
    hParentWindow=HWND_DESKTOP;
    hSplashWnd=CreateWindowEx(WS_EX_CLIENTEDGE,"STATIC","",
        WS_POPUP|WS_DLGFRAME|SS_BITMAP,
        300,300,300,300,
        HWND_DESKTOP,NULL,GetModuleHandle(NULL),NULL);
    HBITMAP Bitmap = LoadBitmap(GetModuleHandle(NULL),"RES_SPLASH");
    if (Bitmap == NULL) {
        Error("Could not load bitmap!");
    } else {
        SendMessage( hSplashWnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)Bitmap );
    }
    this->SHOWING = FALSE;
}

void SPLASH::Show()
{
    // Get size of hSplashWnd (width and height)
    int x,y;
    int pwidth,pheight;
    int tx,ty;
    HDWP windefer;
    RECT rect,prect;
    GetClientRect(hSplashWnd,&rect);
    x=rect.right;y=rect.bottom;

    // Center splash window on screen
    pwidth = GetSystemMetrics(SM_CYSCREEN);
    pheight = GetSystemMetrics(SM_CXSCREEN);

    ty=(pwidth/2) - (y/2);
    tx=(pheight/2) - (x/2);

    // Move the splash
    windefer=BeginDeferWindowPos(1);
    DeferWindowPos(windefer,hSplashWnd,HWND_NOTOPMOST,tx,ty,50,50,SWP_NOSIZE|SWP_SHOWWINDOW|SWP_NOZORDER);
    EndDeferWindowPos(windefer);

    // Show the splash
    ShowWindow(hSplashWnd,SW_SHOWNORMAL);
    UpdateWindow(hSplashWnd);
    this->SHOWING = TRUE;
}

void SPLASH::Hide()
{
    ShowWindow(hSplashWnd,SW_HIDE);
    this->SHOWING = FALSE;
}

