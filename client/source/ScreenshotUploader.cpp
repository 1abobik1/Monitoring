#include "../header/ScreenshotUploader.h"

#include "../header/HttpClient.h"
#include "../header/FileManager.h"

#include <sstream>

void ScreenshotUploader::uploadScreenshot(const std::string& filePath, const std::string& userName) {
    std::string boundary = "-----WebKitFormBoundary7MA4YWxkTrZu0gW";
    std::string headers = "Content-Type: multipart/form-data; boundary=" + boundary;
    std::string fileContent = FileManager::readFileToBinary(filePath);

    std::stringstream postData;
    postData << "--" << boundary << "\r\n";
    postData << "Content-Disposition: form-data; name=\"file\"; filename=\"" << userName << "-screenshot.png\"\r\n";
    postData << "Content-Type: application/octet-stream\r\n\r\n";
    postData << fileContent << "\r\n";
    postData << "--" << boundary << "\r\n";
    postData << "Content-Disposition: form-data; name=\"userName\"\r\n\r\n" << userName << "\r\n";
    postData << "--" << boundary << "--\r\n";

    httpClient.sendData("/upload_screenshot", postData.str(), headers);
}
