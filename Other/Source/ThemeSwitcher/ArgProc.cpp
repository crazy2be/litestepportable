#include "ArgProc.h"
#include "SwitchTheme.h"
#include "RefreshThemes.h"
#include "InstallTheme.h"
#include "Error.h"

void ArgProcessing(string Args) {
    std::transform(Args.begin(), Args.end(), Args.begin(), lower_case);
    //MessageBox(NULL, Args.c_str(), "Command-line Aurguments:", MB_OK);
    if (Args.substr(0,7) == "/switch") {
        int FirstQuote = Args.find("\"")+1;
        string AfterFirstQuote = Args.substr(FirstQuote, Args.length());
        int SecondQuote = AfterFirstQuote.find("\"");
        SwitchTheme(Args.substr(FirstQuote, SecondQuote), false);
        //exit( EXIT_SUCCESS );
    } else if (Args.substr(0, 8) == "/refresh") {
        RefreshListCMD();
        //exit( EXIT_SUCCESS );
    } else if (Args.substr(0, 8) == "/install") {
        if (Args.find("\"") == -1) {
            InstallTheme(PromptForThemeFile());
        } else {
            int FirstQuote = Args.find("\"")+1;
            string AfterFirstQuote = Args.substr(FirstQuote, Args.length());
            int SecondQuote = AfterFirstQuote.find("\"");
            InstallThemeCMD(Args.substr(FirstQuote, SecondQuote));
        }
        //exit( EXIT_SUCCESS );
    } else if (Args == "") {
        return;
    } else {
        Error("Invalid Command Line!\n"
            "Possible switches are:\n"
            "/switch \"Theme Name\"\n"
            "/refresh\n"
            "/install \"Path to zip/lsz file\"\n"
            "/install\n"
            "(The last one prompts the user to select a theme file)\n");
    }
    exit( EXIT_SUCCESS );
}

int lower_case ( int c )
{
  return tolower ( c );
}
