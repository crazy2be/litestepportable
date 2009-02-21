string FindThemeDirPath() {
    string FilesToFind[2];
    FilesToFind[0] = "..\\Litestep.exe";
    FilesToFind[1] = "Litestep.exe";
    FindFile(FilesToFind, 2);
}

string FindFile(string FilesToFind[], unsigned int Length) {
    /*const char* FileToFindChar = const_cast<char*>(FileToFind.c_str());
    LPCSTR SearchPathStr;
    string SearchPathString;
    /*if (AllocConsole()) {
        cout << "Input the SearchPath string!: ";
        cin >> SearchPathString;
        Info("FFKDSJFKSJDSLAD");
        FreeConsole();
    } else {
        Error(GetErrorString(GetLastError()));
    }*//*
    SearchPathStr = SearchPathString.c_str();
    //SearchPathStr = "\\..";
    LPCSTR FileName;
    FileName = FileToFindChar;
    CHAR FileNameAndPath [MAX_PATH];
    //LPCSTR FileNameAndPath;
    //FileNameAndPath = FileNameAndPathChar;
    if (SearchPath(
        SearchPathStr,
        FileName,
        NULL,
        MAX_PATH,
        FileNameAndPath,
        NULL) > 0) {
            string FileNameAndPathStr = FileNameAndPath;
            Error(FileNameAndPathStr);
    } else {
        Error(GetErrorString(GetLastError()));
    }
    return "Dsd";*/
    /* Define Variables */
    WIN32_FIND_DATA CurFileData;
    string SearchDir;
    LPCSTR SearchDirC;
    HANDLE FindFileHandle;
    string FileName;
    char Path [MAX_PATH];
    //const char* FileToFindC = new char[FileToFind.size()];
    //FileToFindC = FileToFind.c_str();
    bool FindNextReturn = true;
    /* Searches up one dir for the file */
    SearchDir = "..\\";
    SearchDir += FileToFind;
    //strcat(ThemesDir, FileToFindC);
    FindFileHandle = FindFirstFile(SearchDir.c_str(), &CurFileData);
    if (FindFileHandle == INVALID_HANDLE_VALUE) {
        /* If it's not there, search the current dir */
        SearchDir = FileToFind;
        FindFileHandle = FindFirstFile(SearchDir.c_str(), &CurFileData);
        if (FindFileHandle == INVALID_HANDLE_VALUE) {
            //int Timeout = [time] + 5;
            while(1/*Timeout < [time]*/) {
                if (CurFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
                    FileName = CurFileData.cFileName;
                    if (FileName != "." && FileName != "..") {
                        
                    }
                }
                FindNextReturn = FindNextFile(FindFileHandle, &CurFileData);
            }
        } else {
            _getcwd(Path, MAX_PATH);
            FileName = Path;
            FileName += "\\";
            FileName += CurFileData.cFileName;
            Info(FileName);
            return FileName;
        }
    } else {
        _getcwd(Path, MAX_PATH);
        FileName = Path;
        FileName = FileName.substr(0, FileName.rfind("\\"));
        FileName += "\\";
        FileName += CurFileData.cFileName;
        Info(FileName);
        return FileName;
    }
}
