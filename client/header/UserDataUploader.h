#pragma once

#include "HttpClient.h"

class UserDataUploader {
public:
    UserDataUploader(HttpClient& client) : httpClient(client) {}

    void uploadUserData(const std::string& userName, const std::string& computerName,
        const std::string& domainName);

private:
    HttpClient& httpClient;
};