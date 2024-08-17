#include "../header/SystemClientInfo.h"

#include <windows.h>
#include <wininet.h>
#include <Lmcons.h>
#include <lm.h>

std::string SystemInfo::getComputerName() {
    char hostname[100];
    DWORD hostnameSize = sizeof(hostname);
    if (GetComputerNameA(hostname, &hostnameSize)) {
        return std::string(hostname);
    }
    return "ComputerNameNotFound";
}

std::string SystemInfo::getUserName(){
    TCHAR name[UNLEN + 1];
    DWORD size = UNLEN + 1;
    if (GetUserName(name, &size)) {
        std::wstring nameWstr = name;
        return std::string(nameWstr.begin(), nameWstr.end());
    }
    return "UserNameNotFound";
}

std::string SystemInfo::getDomainName() {
    WKSTA_INFO_100* pInfo = nullptr;
    DWORD dwLevel = 100;
    DWORD dwErr = NetWkstaGetInfo(nullptr, dwLevel, (LPBYTE*)&pInfo);
    if (dwErr == NERR_Success) {
        std::wstring domainNameWstr = std::wstring(pInfo->wki100_langroup);
        NetApiBufferFree(pInfo);
        return std::string(domainNameWstr.begin(), domainNameWstr.end());
    }
    return "domainNameNotFound";
}