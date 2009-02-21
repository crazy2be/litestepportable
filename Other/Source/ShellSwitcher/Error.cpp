#include "Error.h"
#include "GlobalVars.h"

void Error(string ErrorMessage) {
    MessageBox(NULL, ErrorMessage.c_str(), "ERROR!", MB_OK | MB_ICONERROR);
}

void Warning(string WarningMessage) {
    MessageBox(NULL, WarningMessage.c_str(), "Warning!", MB_OK | MB_ICONWARNING);
}

void Info(string Information) {
    MessageBox(NULL, Information.c_str(), "Information:", MB_OK | MB_ICONINFORMATION);
}

void Status(string NewStatus) {
    //not in this program yet :P
    //Edit_SetText(GlobalStatushwnd, NewStatus.c_str());
    //_beginthread(ResetStatus, 0, NULL);
}

string GetErrorString(DWORD ErrorCode) {
    char ErrorMsgChar [1024];
    LPSTR ErrorMessage = ErrorMsgChar;
    FormatMessage(
        FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        ErrorCode,
        0,
        ErrorMessage,
        1024,
        NULL);
    string StrErrorMessage = ErrorMessage;
    return StrErrorMessage;
}

void ResetStatus( void* Nothing ) {
    //Sleep(1000);
    //Edit_SetText(GlobalStatushwnd, "Ready...");
}
