#include <windows.h>
#include <string>
#include <shlwapi.h>
#include <objbase.h>
#include <vector>
#include <shellapi.h>
#include <shlobj.h>
#include <sstream>

using namespace std;

/* functions... */
vector<string> UpdatePopup();
void UpdateIcons(const vector<string>& AllPortableApps);
HRESULT CreateLink(LPCSTR lpszPathObj, LPCSTR lpszPathLink, LPCSTR lpszDesc);
