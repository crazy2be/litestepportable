#include <windows.h>
#include <string>
using namespace std;

void Error(string Message);

int main(int argc, char *argv[]) {
    string WD;
	WD = argv[0];
	WD = WD.substr(0, WD.rfind("\\"));
	SetCurrentDirectory(WD.c_str());
	
    int ErrorCode = (int) ShellExecute(
        NULL,
        "open",
        "html\\Tutorial.hta",
        NULL,
        NULL,
        SW_SHOW);
    if (ErrorCode > 32) {
        exit(EXIT_SUCCESS);
    }
    switch (ErrorCode) {
        case 0:
            Error("Out of memory");
            break;
        case ERROR_FILE_NOT_FOUND:
            Error("html\\Tutorial.hta not found");
            break;
        case ERROR_PATH_NOT_FOUND:
            Error("folder \\html was not found");
            break;
        default:
            Error("An unknown error occured");
            break;
    }
}

void Error(string Message) {
    MessageBox(NULL, Message.c_str(), "Fatal Error", MB_ICONERROR);
}
