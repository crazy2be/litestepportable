#include <fstream>
#include <string>
#include <sstream>
#include "GlobalVars.h"

using namespace std;
/* Declare Functions */
bool GetBoolValue(string ValueToGet);
int GetIntValue(string ValueToGet);
string GetValue(string ValueToGet);
string GetDefaultValue(string ValueToGet);

void SetValue(string Setting, string Value);
void SetIntValue(string Setting, int Value);
void SetBoolValue(string Setting, bool Value);
