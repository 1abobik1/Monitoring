#pragma once

#include <windows.h>
#include <wininet.h>
#include <iostream>
#include <string>
#include <fstream>

class HttpClient {
public:
    HttpClient(const std::string& server, int port)
        : server(server), port(port), hSession(NULL), hConnect(NULL) {}

    ~HttpClient();

    bool init();
    bool sendData(const std::string& endpoint, const std::string& postData, const std::string& header);

private:
    std::string server;
    int port;
    HINTERNET hSession;
    HINTERNET hConnect;
};
