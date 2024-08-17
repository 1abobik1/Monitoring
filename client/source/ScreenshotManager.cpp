#include "../header/ScreenshotManager.h"

#include "string"

ScreenshotManager::ScreenshotManager() {
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

ScreenshotManager::~ScreenshotManager() {
    Gdiplus::GdiplusShutdown(gdiplusToken);
}

void ScreenshotManager::captureScreenshot(const std::string& filePath) {
    HWND desktopWnd = GetDesktopWindow();
    HDC desktopDC = GetWindowDC(desktopWnd);
    HDC captureDC = CreateCompatibleDC(desktopDC);

    RECT desktopParams;
    GetWindowRect(desktopWnd, &desktopParams);

    HBITMAP captureBitmap = CreateCompatibleBitmap(desktopDC, desktopParams.right, desktopParams.bottom);
    SelectObject(captureDC, captureBitmap);
    BitBlt(captureDC, 0, 0, desktopParams.right, desktopParams.bottom, desktopDC, 0, 0, SRCCOPY);

    Gdiplus::Bitmap bitmap(captureBitmap, NULL);
    CLSID clsid;
    if (CLSIDFromString(L"{557CF400-1A04-11D3-9A73-0000F81EF32E}", &clsid) == S_OK) {
        std::wstring wFilePath(filePath.begin(), filePath.end());
        bitmap.Save(wFilePath.c_str(), &clsid);
    }

    ReleaseDC(desktopWnd, desktopDC);
    DeleteDC(captureDC);
    DeleteObject(captureBitmap);
}
