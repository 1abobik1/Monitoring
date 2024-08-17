#pragma once

#include <windows.h>
#include <wininet.h>
#include <Lmcons.h>
#include <lm.h>
#include <string>
#include <gdiplus.h>


class ScreenshotManager {
public:
    ScreenshotManager();
    ~ScreenshotManager();

    void captureScreenshot(const std::string& filePath);

private:
    ULONG_PTR gdiplusToken;
};