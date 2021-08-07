#include <iostream>
#include <Windows.h>
#include <comutil.h>
#include <string>


std::string getHWID()
{
    std::string hwid;
    TCHAR volumeName[MAX_PATH + 1] = { 0 };
    TCHAR fileSystemName[MAX_PATH + 1] = { 0 };
    DWORD serialNumber = 0;
    DWORD maxComponentLen = 0;
    DWORD fileSystemFlags = 0;
    if (GetVolumeInformation(
        TEXT("C:\\"),
        volumeName,
        ARRAYSIZE(volumeName),
        &serialNumber,
        &maxComponentLen,
        &fileSystemFlags,
        fileSystemName,
        ARRAYSIZE(fileSystemName)))
    {
        hwid = std::to_string(serialNumber);
        if (hwid.empty()) {
            MessageBox(nullptr, L"Unable to retreive your HWID.", L"Retrieval Error", MB_OK);
            ExitProcess(0);
        }
        hwid = "H" + hwid.substr(0, 2) + hwid.substr(5, 2) + hwid.substr(2, 2) + hwid.at(6);
    }
    return hwid;
}

void set_clipboard(const char* value)
{
    auto glob = GlobalAlloc(GMEM_FIXED, std::strlen(value) + 1);
    memcpy(glob, value, std::strlen(value) + 1);
    OpenClipboard(nullptr);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, glob);
    CloseClipboard();
}

// void main()
INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
    std::string hwid = getHWID();
    set_clipboard(hwid.c_str());
    MessageBox(nullptr, L"HWID copied to clipboard.", L"Copied HWID", MB_OK);
}