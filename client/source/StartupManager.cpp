#include "../header/StartupManager.h"

#include <windows.h>
#include <iostream>

void StartupManager::addToStartup() {
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    HKEY hKey;
    RegOpenKeyA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", &hKey);
    RegSetValueExA(hKey, "MonitoringApp", 0, REG_SZ, (BYTE*)path, strlen(path) + 1);
    RegCloseKey(hKey);
}

bool StartupManager::IsRunningAsAdmin() {
    BOOL isAdmin = FALSE;
    PSID pAdminsGroup = NULL;
    SID_IDENTIFIER_AUTHORITY siaNtAuthority = SECURITY_NT_AUTHORITY;

    if (AllocateAndInitializeSid(&siaNtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &pAdminsGroup)) {
        if (!CheckTokenMembership(NULL, pAdminsGroup, &isAdmin)) {
            isAdmin = FALSE;
        }
        FreeSid(pAdminsGroup);
    }
    return isAdmin;
}

void StartupManager::RunAsAdmin() {
    WCHAR szPath[MAX_PATH];
    GetModuleFileName(NULL, szPath, MAX_PATH);

    SHELLEXECUTEINFOW sei = { 0 };
    sei.cbSize = sizeof(sei);
    sei.lpVerb = L"runas";
    sei.lpFile = szPath;
    sei.nShow = SW_SHOWNORMAL;

    if (!ShellExecuteExW(&sei)) {
        DWORD dwError = GetLastError();
        if (dwError != ERROR_CANCELLED) {
            std::cerr << "Failed to restart as administrator. Error: " << dwError << std::endl;
        }
    }
}
