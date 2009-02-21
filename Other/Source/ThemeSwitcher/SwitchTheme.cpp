#include "SwitchTheme.h"
#include "GetSettings.h"
#include "Error.h"
#include "ProcessExist.h"

void SwitchTheme(string ThemeName, bool Prompt) {
    int SwitchResult;
    if (Prompt) {
        SwitchResult = MessageBox(NULL, ThemeName.c_str(), "Switch Theme?", MB_YESNO);
    } else {
        SwitchResult = IDYES;
    }
    if (SwitchResult == IDYES) { //The user clicked yes
        ifstream GetTheme;
        string line;
        string EndText;
        GetTheme.open((GetValue("ThemesDir") + "Themeselect.rc").c_str());
        if (GetTheme.is_open()) {
            while (!GetTheme.eof()) {
                getline ( GetTheme, line );
                if (line.substr(0, 8) == "ThemeDir") {
                    line = "ThemeDir \"$ThemesDir$";
                    line += ThemeName;
                    line += "\\\"";
                }
                EndText += line;
                EndText += "\n";
            }
            GetTheme.close();
        } else {
            Error("Unable to open Themeselect.rc for reading!");
        }
        ofstream SetTheme;
        SetTheme.open((GetValue("ThemesDir") + "Themeselect.rc").c_str());
        if (SetTheme.is_open()) {
            SetTheme << EndText.substr(0, EndText.length()-1);
            SetTheme.close();
        } else {
            Error("Unable to open Themeselect.rc for writing!");
        }
        if (!ProcessRunning("litestep.exe"))
            ShellExecute(NULL, "open", GetValue("Litestep").c_str(), NULL, NULL, SW_SHOWNORMAL);
        else
            ShellExecute(NULL, "open", GetValue("Litestep").c_str(), "!recycle", NULL, SW_SHOWNORMAL);
        
        if (ThemeName != GetValue("DefaultTheme")) {
            Sleep(GetIntValue("DefaultThemePromptTimeout"));
            string ThemeMsg = "Switch back to the default theme? (";
            ThemeMsg += GetValue("DefaultTheme");
            ThemeMsg += ")\n";
            ThemeMsg += "[You may want to do this if the theme has loading errors]";
            if (MessageBox(NULL, ThemeMsg.c_str(),
                "Switch to the default?",
                MB_YESNO) == IDYES) {
                    SwitchTheme(GetValue("DefaultTheme"), false);
                }
        }
    }
}
