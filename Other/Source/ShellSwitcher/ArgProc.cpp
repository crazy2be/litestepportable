#include "ArgProc.h"
#include "Error.h"
#include "GetSettings.h"
#include "UpdateIcons.h"

void ArgProcessing(string Args) {
    std::transform(Args.begin(), Args.end(), Args.begin(), lower_case);
    //MessageBox(NULL, Args.c_str(), "Command-line Aurguments:", MB_OK);
    /*if (Args.substr(0,7) == "/switch") {
        int FirstQuote = Args.find("\"")+1;
        string AfterFirstQuote = Args.substr(FirstQuote, Args.length());
        int SecondQuote = AfterFirstQuote.find("\"");
        SwitchTheme(Args.substr(FirstQuote, SecondQuote), false);
        //exit( EXIT_SUCCESS );
    } else */if (Args.substr(0, 8) == "/refresh") {
        vector<string> AllApps = UpdatePopup();
        UpdateIcons(AllApps);
        ShellExecute( NULL, "open", GetValue("Litestep").c_str(), "!Recycle", NULL, SW_SHOW);
        //exit( EXIT_SUCCESS );
    }/* else if (Args.substr(0, 8) == "/install") {
        if (Args.find("\"") == -1) {
            InstallTheme(PromptForThemeFile());
        } else {
            int FirstQuote = Args.find("\"")+1;
            string AfterFirstQuote = Args.substr(FirstQuote, Args.length());
            int SecondQuote = AfterFirstQuote.find("\"");
            InstallThemeCMD(Args.substr(FirstQuote, SecondQuote));
        }
        //exit( EXIT_SUCCESS );
    } */else if (Args == "") {
        return;
    } else {
        Error("Invalid Command Line!\n"
            "Possible switches are:\n"
            "/refresh\n"
            " - Refreshes the list of installed apps and the desktop icons\n");
    }
    exit( EXIT_SUCCESS );
}

int lower_case ( int c )
{
  return tolower ( c );
}
