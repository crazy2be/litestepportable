#include "GetSettings.h"
#include "Error.h"

bool GetBoolValue(string ValueToGet) {
    string ReturnString = GetValue(ValueToGet);
    if (ReturnString == "true" 
        || ReturnString == "yes"
        || ReturnString == "1") {
            return true;
    } else if (ReturnString == "false"
        || ReturnString == "no"
        || ReturnString == "0") {
            return false;
    } else {
        Warning("Attempted retreval of bool value,\n" 
            + ValueToGet + 
            "\nresulted in the retreival of a non-bool\n"
            "value. Returning false to the caller function,\n"
            "and attempting to set it to false to avoid this\n"
            "error in the future.\n"
            "\n"
            "In other words, you should either change the\n"
            "setting's value in Data\\Settings.ini, or\n"
            "maybe you need to define it :P Like this:\n"
            + ValueToGet + "=true");
        SetBoolValue(ValueToGet, false);
        return false;
    }
}

int GetIntValue(string ValueToGet) {
    return atoi(GetValue(ValueToGet).c_str());
}

string GetValue(string ValueToGet) {
    string line;
    //string value;
    string setting;
    int equalsign;
    try {
        ifstream SetRead ("Data\\Settings.ini");
        if (SetRead.is_open()) {
            while (! SetRead.eof()) {
                getline (SetRead, line);
                //cout << line << endl;
                if (line[0] == ';') {
                    
                } else {
                    equalsign = line.find('=');
                    setting = line.substr(0, equalsign);
                    //value = line.substr((equalsign+1), line.length());
                    if (setting == ValueToGet) {
                        return line.substr((equalsign+1), line.length());
                    }
                }
            }
        } else {
            Error("Unable to open Data\\Settings.ini for reading!");
        }
        SetRead.close();
        return GetDefaultValue(ValueToGet);
    } catch (...) {
        return "ERROR_OCCURED_WHILE_PARSING";
    }
}

string GetDefaultValue(string ValueToGet) {
    if (ValueToGet == "foo")
        return "bar";
    if (ValueToGet == "ThemesDir")
        return "E:\\Litestep\\Themes\\";
    if (ValueToGet == "Show Extracting Console")
        return "true";
    return "DEFAULT_VALUE_NOT_FOUND";
}

void SetValue(string Setting, string Value) {
    string line;
    string ToWrite;
    string setting;
    bool Written = false;
    int equalsign;
    try {
        ifstream SetRead ("Data\\Settings.ini");
        if (SetRead.is_open()) {
            while (! SetRead.eof()) {
                getline (SetRead, line);
                equalsign = line.find('=');
                setting = line.substr(0, equalsign);
                //value = line.substr((equalsign+1), line.length());
                if (setting == Setting) {
                    line = setting;
                    line += "=";
                    line += Value;
                    Written = true;
                    //return line.substr((equalsign+1), line.length());
                }
                ToWrite += line;
                ToWrite += "\n";
            }
            if (!Written) {
                ToWrite += Setting;
                ToWrite += "=";
                ToWrite += Value;
                ToWrite += "\n";
            }
            ToWrite = ToWrite.substr(0, (ToWrite.length()-1));
            SetRead.close();
            ofstream SetWrite ("Data\\Settings.ini", ios::trunc);
            if (SetWrite.is_open()) {
                SetWrite << ToWrite;
            } else {
                 Error("Unable to open Data\\Settings.ini for writing!");
            }
            SetWrite.close();
        } else {
            Error("Unable to open Data\\Settings.ini for reading!\n"
                "Attemping to open for writing...");
            ofstream SetWrite ("Data\\Settings.ini");
            if (SetWrite.is_open()) {
                SetWrite << Setting << "=" << Value << "\n";
            } else {
                 Error("Unable to open Data\\Settings.ini for writing!");
            }
            SetWrite.close();  
        }

    } catch (...) {
        Error("Error occured while reading or writing file Data\\Settings.ini");
    }
}

void SetIntValue(string Setting, int Value) {
    ostringstream ValueStr;
    ValueStr << Value;
    SetValue(Setting, ValueStr.str());
}

void SetBoolValue(string Setting, bool Value) {
    if (Value) {
        SetValue(Setting, "true");
    } else {
        SetValue(Setting, "false");
    }
}
