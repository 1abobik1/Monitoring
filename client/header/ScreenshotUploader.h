#pragma once

#include "HttpClient.h"
#include "FileManager.h"

class ScreenshotUploader {
public:
    ScreenshotUploader(HttpClient& client) : httpClient(client) {}

    void uploadScreenshot(const std::string& filePath, const std::string& userName);

private:
    HttpClient& httpClient;
};