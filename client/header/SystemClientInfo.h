#pragma once

#include "string"

class SystemInfo {
public:
    static std::string getComputerName();

    static std::string getUserName();

    static std::string getDomainName();
};