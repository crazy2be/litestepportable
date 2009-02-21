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
        Warning("Attempted retreval of a bool value resulted in\n"
            "the retreival of a non-bool value. Returning false\n"
            "to the caller function.");
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
            Error("Unable to open Settings.ini for reading!");
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
            Error("Unable to open Data\\Settings.ini for reading!");
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
